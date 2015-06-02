#include "timer.h"
#include "svm.h"

//#include <vector>
//#include <assert.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
//#include <map>

#include "solve_qp.h"

//#ifdef QT_DEBUG
//#define BMRM_INFO
//#endif


using namespace std;


static double empRiskCP(const vector<Vec>& a, const vector<double>& b, const Vec& w);
static double Omega(const Vec& w);


static double SparseProduct(int rowIdx, const Data& samples, const Vec& vec);


static double empRiskBinary(const Data& samples,
                    const std::vector<int>& firstClassIdx,
                    const std::vector<int>& secondClassIdx,
                    const Vec& w);

static Vec empRiskSubgradientOneClass(const Data& samples,
                              const std::vector<int>& classSampleIdx,
                              double y,
                              const Vec& w);

static Vec empRiskSubgradientBinary(const Data& samples,
                              const std::vector<int>& firstClassIdx,
                              const std::vector<int>& secondClassIdx,
                              const Vec& w);

static Vec TrainBinarySVM( const Data& samples,
                            const int n_vars,
                            const std::vector<int>& firstClassIdx,
                            const std::vector<int>& secondClassIdx,
                            const double lambda,  const double epsilonAbs,
                            const double epsilonTol, const int tMax);

////--------------------------------------------------------------------------------

//SVM::SVM()
//{
//}


void SVM::Train(const double* data, const long* resp, int n_samples, int n_vars,
                 int row_step, int col_step,
                 double lambda, double epsilon_abs, double epsilon_tol, int tMax)
{
    //const Vec responses = data.Responses();

    n_classes = int(1 + *std::max_element(resp, resp+n_samples));

    vector<vector<int> > classIdxVectors(n_classes);
    for(int i = 0;i<n_samples;i++)
    {
        int classNumber = int(resp[i]);
        classIdxVectors[classNumber].push_back(i);
    }


    Data samples(data, row_step, col_step);
//    for(int i = 0;i < n_samples;i++)
//    {
//        for(int j = 0;j < n_vars;j++)
//        {
//            std::cout << d(i, j) << " ";
//        }
//        std::cout << std::endl;
//    }


    betta.clear();
    for(int i = 0;i<n_classes;i++)
    {
        for(int j = i+1;j<n_classes;j++)
        {
            #ifdef BMRM_INFO
            cout << "class " << i << " vs " << j << endl;
            #endif
            Vec w = TrainBinarySVM(samples,
                                   n_vars,
                                   classIdxVectors[i], classIdxVectors[j],
                                    lambda, epsilon_abs, epsilon_tol, tMax);
            betta.push_back(w);
        }
    }
}



//double SVM::Predict(const std::list<Pair>& sample) const

void SVM::Predict(const double* data, long *pred,
                  int n_samples, int n_vars,
                  int row_step, int col_step) const
{
    assert(!betta.empty());

    Data samples(data, row_step, col_step);

    for(int sample_idx = 0;sample_idx<n_samples;sample_idx++)
    {
        vector<int> classVote(n_classes);
        std::fill(classVote.begin(), classVote.end(), 0);
        int k = 0;
        for(int i = 0;i<n_classes;i++)
        {
            for(int j = i+1;j<n_classes;j++)
            {
                double result = 0;
                for(int s = 0;s<n_vars;s++)
                {
                    result += samples(sample_idx, s)*betta[k][s];
                }


                if(result < 0)
                {
                    classVote[j]++;
                }
                else
                {
                    classVote[i]++;
                }
                k++;
            }
        }

        int max_val = 0;
        int max_idx;
        for(unsigned i = 0;i<classVote.size();i++)
        {
            if(classVote[i] > max_val)
            {
                max_idx = i;
                max_val = classVote[i];
            }
        }
        pred[sample_idx] = long(max_idx);
    }
}


//double SVM::CalcError(const Data& data, int type) const
//{
//    const vector<int>& trainSampleIdx = data.TrainSampleIdx();
//    const vector<int>& testSampleIdx = data.TestSampleIdx();
//    const vector<int>* sampleIdxPtr;
//    if(type==TRAIN)
//    {
//        sampleIdxPtr = &trainSampleIdx;
//    }
//    else // type==TEST
//    {
//        sampleIdxPtr = &testSampleIdx;
//    }
//    const vector<int>& sampleIdx = *sampleIdxPtr;


//    assert( sampleIdx.size() != 0 );


//    int errorCount = 0;
//    for(unsigned i = 0;i<sampleIdx.size();i++)
//    {
//        int row = sampleIdx[i];

//        double pred = this->Predict(data.Samples()[row]);
//        double actual = data.Responses()[row];

//        #ifdef BMRM_INFO
//        cout << "row = " << row;
//        cout << " actual = " << actual << " pred = " << pred << endl;
//        #endif

//        if(pred != actual)
//        {
//            errorCount++;
//        }


//    }
//    return double(errorCount)/sampleIdx.size();
//}


////------------------------------------------------------------------------------------------

double Omega(const Vec& w)
{
    return double(0.5)*inner_prod(w, w);
}


double SparseProduct(int rowIdx, const Data& samples, const Vec& vec)
{
    double result = 0.;

    for(int i = 0;i<vec.size();i++)
    {
        result += samples(rowIdx, i)*vec(i);
    }

    return result;
}


double empRiskCP(const vector<Vec>& a, const vector<double>& b, const Vec& w)
{
    double val = inner_prod(w, a[0]) + b[0];
    for(unsigned i = 1;i<a.size();i++)
    {
        val = std::max (val, inner_prod(w, a[i]) + b[i]);
    }
    return val;
}



static Vec TrainBinarySVM( const Data& samples,
                            const int n_vars,
                            const std::vector<int>& firstClassIdx,
                            const std::vector<int>& secondClassIdx,
                            const double lambda,  const double epsilon_abs,
                            const double epsilon_tol, const int tMax)
{
    int d = n_vars; // размерность пространства признаков


    Vec w(d);
    std::fill(w.begin(), w.end(), 0);
    int t = 0;
    double currentEps = -1;
    vector<Vec> a;
    vector<double> b;



    do
    {
        t++;

        long long time_a = -gettimeus();
        a.push_back( empRiskSubgradientBinary(samples, firstClassIdx, secondClassIdx, w) );
        time_a += gettimeus();


        long long time_b = -gettimeus();
        b.push_back(
                    empRiskBinary(samples, firstClassIdx, secondClassIdx, w) - inner_prod(w, a.back())
                   );
        time_b += gettimeus();

#ifdef BMRM_INFO
        cout << endl << "Iteration " << t << endl;
//        cout << "empRisk(w) = " << empRisk(data, w) << endl;


        cout << "Subgradient calculating time: " << double(time_a)/1000000 << " seconds" << endl;
        cout << "Coef calculating time: " << double(time_b)/1000000 << " seconds" << endl;

//        cout << "w[" << t-1 << "] = " << w << endl;
//        cout << "a[" << t << "] = " << a.back() << endl;
//        cout << "b[" << t << "] = " << b.back() << endl;
#endif



        //==========================================
        // argmin begin
        //==========================================
        Vec alpha(t);

        long long time_qp = -gettimeus();
        SolveQP(a, b, lambda, epsilon_tol*0.5, alpha);
        time_qp += gettimeus();




        // Получение w из alpha
        Vec temp(d);
        std::fill(temp.begin(), temp.end(), 0);
        for(int i = 0;i<t;i++)
        {
            temp = temp + alpha[i]*a[i];
        }
        w = -temp/lambda;

#ifdef BMRM_INFO
        cout << "J(w) = " << lambda*Omega(w)+empRiskBinary(samples, firstClassIdx, secondClassIdx, w) << endl;
//        cout << "EmpRisk(w) = " << empRisk(data, w) << endl;
//        cout << "EmpRiskCP(w) = " << empRiskCP(a, b, w) << endl;
#endif
        //==========================================
        // argmin end
        //==========================================


        currentEps = empRiskBinary(samples, firstClassIdx, secondClassIdx, w) - empRiskCP(a, b, w);

#ifdef BMRM_INFO
        cout << "QP solving time: " << double(time_qp)/1000000 << " seconds" << endl;

        cout << "Current epsilon = " << currentEps << endl;
#endif

    }
    while(
          currentEps>epsilon_abs
          && currentEps>epsilon_tol*(lambda*Omega(w)+empRiskBinary(samples, firstClassIdx, secondClassIdx, w))
          && t<tMax
         );


#ifdef BMRM_INFO
    cout << endl << endl;
    cout << "BMRM => J(w) = " << lambda*Omega(w)+empRiskBinary(samples, firstClassIdx, secondClassIdx, w) << endl;
    printf("BMRM => Achieved epsilon: %e \n", currentEps);
    printf("BMRM => Required abs epsilon: %e \n", epsilon_abs);
    printf("BMRM => Required tol epsilon: %e \n", epsilon_tol);
    cout << "BMRM => Number of iterations: " << t << " (max - " << tMax << ")" << endl;

    cout << "w = " << w << endl;
#endif


    return w;
}


double empRiskBinary(const Data& samples,
                    const std::vector<int>& firstClassIdx,
                    const std::vector<int>& secondClassIdx,
                    const Vec& w)
{
    double sum = 0;
    for(unsigned i = 0;i<firstClassIdx.size();i++)
    {
        int idx = firstClassIdx[i];
        sum += max(  double(0), 1 - SparseProduct(idx, samples, w)  );
    }
    for(unsigned i = 0;i<secondClassIdx.size();i++)
    {
        int idx = secondClassIdx[i];
        sum += max(  double(0), 1 + SparseProduct(idx, samples, w)  );
    }

    sum /= firstClassIdx.size() + secondClassIdx.size();

    return sum;
}


Vec empRiskSubgradientBinary(const Data& samples,
                              const std::vector<int>& firstClassIdx,
                              const std::vector<int>& secondClassIdx,
                              const Vec& w)
{
    empRiskSubgradientOneClass(samples, firstClassIdx, 1.0, w);

    Vec subgr =
            empRiskSubgradientOneClass(samples, firstClassIdx, 1.0, w) +
            empRiskSubgradientOneClass(samples, secondClassIdx, -1.0, w);

    subgr /= firstClassIdx.size()+secondClassIdx.size();
    return subgr;
}


Vec empRiskSubgradientOneClass(const Data& samples,
                              const std::vector<int>& classSampleIdx,
                              double y,
                              const Vec& w)
{
    Vec subgr;
    subgr.resize(w.size());
    std::fill(subgr.begin(), subgr.end(), 0);

    for(unsigned i = 0;i<classSampleIdx.size();i++)
    {
        int idx = classSampleIdx[i];
        double maxVal = max(  double(0), 1-y*SparseProduct(idx, samples, w)  );
        if(maxVal > 0)
        {
            for(int i = 0;i<subgr.size();i++)
            {
                subgr(i) += -y*samples(idx, i);
            }
        }
    }

    return subgr;
}
