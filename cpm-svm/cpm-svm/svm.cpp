//#include "timer.h"
#include "svm.h"

//#include <vector>
//#include <assert.h>
#include <iostream>
//#include <stdio.h>
//#include <map>

//#include "solve_qp.h"

//#ifdef QT_DEBUG
//#define BMRM_INFO
//#endif


//using namespace std;


//static Real empRiskCP(const vector<Vec>& a, const vector<Real>& b, const Vec& w);
//static Real Omega(const Vec& w);


//static Real SparseProduct(int rowIdx, const SparseMat& mat, const Vec& vec);


//static Real empRiskBinary(const Data& data,
//                    const std::vector<int>& firstClassIdx,
//                    const std::vector<int>& secondClassIdx,
//                    const Vec& w);

//Vec empRiskSubgradientOneClass(const Data& data,
//                              const std::vector<int>& classSampleIdx,
//                              double y,
//                              const Vec& w);

//static Vec empRiskSubgradientBinary(const Data& data,
//                              const std::vector<int>& firstClassIdx,
//                              const std::vector<int>& secondClassIdx,
//                              const Vec& w);

//static Vec TrainBinarySVM( const Data& data,
//                            const std::vector<int>& firstClassIdx,
//                            const std::vector<int>& secondClassIdx,
//                            const Real lambda,  const Real epsilonAbs,
//                            const Real epsilonTol, const int tMax);

////--------------------------------------------------------------------------------

//SVM::SVM()
//{
//}


void SVM::Train(const double* data, const int* resp, int n_samples, int n_vars,
                 int row_step, int col_step,
                 double lambda, double epsilonAbs, double epsilonTol, int tMax)
{
    //const Vec responses = data.Responses();

//    map<Real, int> classMap;
//    int classCount = 0;
//    for(unsigned i = 0;i<responses.size();i++)
//    {
//        Real label = responses[i];
//        map<Real, int>::const_iterator iter = classMap.find(label);
//        if(iter == classMap.end())
//        {
//            classMap[label] = classCount;
//            classCount++;
//        }
//    }
//    vector<vector<int> > classIdxVectors(classCount);
//    const std::vector<int> train_sample_idx = data.TrainSampleIdx();
//    for(unsigned i = 0;i<train_sample_idx.size();i++)
//    {
//        int idx = train_sample_idx[i];
//        int classNumber = classMap.at(responses[idx]);
//        classIdxVectors[classNumber].push_back(idx);
//    }


    Data d(data, row_step, col_step);
    for(int i = 0;i < n_samples;i++)
    {
        for(int j = 0;j < n_vars;j++)
        {
            std::cout << d(i, j) << " ";
        }
        std::cout << std::endl;
    }


//    betta.clear();
//    for(int i = 0;i<classCount;i++)
//    {
//        for(int j = i+1;j<classCount;j++)
//        {
//            #ifdef BMRM_INFO
//            cout << "class " << i << " vs " << j << endl;
//            #endif
//            Vec w = TrainBinarySVM(data,
//                                   classIdxVectors[i], classIdxVectors[j],
//                                    lambda, epsilon_abs, epsilon_tol, tMax);
//            betta.push_back(w);
//        }
//    }


//    classLabels.clear();
//    classLabels.resize(classMap.size());
//    map<Real, int>::const_iterator iter;
//    for(iter = classMap.begin();iter!=classMap.end();iter++)
//    {
//        classLabels[iter->second] = iter->first;
//    }
}






//Real SVM::Predict(const std::list<Pair>& sample) const
//{
//    assert(!betta.empty());

//    int classCount = classLabels.size();
//    vector<int> classVote(classCount);
//    std::fill(classVote.begin(), classVote.end(), 0);
//    int k = 0;
//    for(int i = 0;i<classCount;i++)
//    {
//        for(int j = i+1;j<classCount;j++)
//        {
//            Real result = 0;
//            list<Pair>::const_iterator iter = sample.begin();
//            while(iter!=sample.end())
//            {
//                result += iter->value*betta[k][iter->idx-1];
//                iter++;
//            }


//            if(result < 0)
//            {
//                classVote[j]++;
//            }
//            else
//            {
//                classVote[i]++;
//            }
//            k++;
//        }
//    }

//    int max_val = 0;
//    int max_idx;
//    for(unsigned i = 0;i<classVote.size();i++)
//    {
//        if(classVote[i] > max_val)
//        {
//            max_idx = i;
//            max_val = classVote[i];
//        }
//    }
//    return classLabels[max_idx];
//}


//Real SVM::CalcError(const Data& data, int type) const
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

//        Real pred = this->Predict(data.Samples()[row]);
//        Real actual = data.Responses()[row];

//        #ifdef BMRM_INFO
//        cout << "row = " << row;
//        cout << " actual = " << actual << " pred = " << pred << endl;
//        #endif

//        if(pred != actual)
//        {
//            errorCount++;
//        }


//    }
//    return Real(errorCount)/sampleIdx.size();
//}


////------------------------------------------------------------------------------------------

//Real Omega(const Vec& w)
//{
//    return Real(0.5)*inner_prod(w, w);
//}

//Real empRisk(const Data& data, const Vec& w)
//{
//    Vec responses = data.Responses();
//    vector<int> trainSampleIdx = data.TrainSampleIdx();

//    Real sum = 0;
//    for(unsigned i = 0;i<trainSampleIdx.size();i++)
//    {
//        int idx = trainSampleIdx[i];
//        sum += max(  Real(0), 1-responses[idx]*SparseProduct(idx, data.Samples(), w)  );
//    }

//    sum /= trainSampleIdx.size();

//    return sum;
//}


//Real SparseProduct(int rowIdx, const SparseMat& mat, const Vec& vec)
//{
//    Real result = 0;

//    const list<Pair>& row =  mat[rowIdx];
//    list<Pair>::const_iterator iter = row.begin();
//    while(iter!=row.end())
//    {
//        result += iter->value*vec[iter->idx-1];
//        iter++;
//    }

//    return result;
//}



//Vec empRiskSubgradient(const Data& data, const Vec& w)
//{
//    Vec responses = data.Responses();
//    vector<int> trainSampleIdx = data.TrainSampleIdx();

//    Vec subgr;
//    subgr.resize(w.size());
//    for(unsigned i = 0;i<subgr.size();i++)
//    {
//        subgr[i] = 0;
//    }

//    for(unsigned i = 0;i<trainSampleIdx.size();i++)
//    {
//        int idx = trainSampleIdx[i];
//        Real maxVal = max(  Real(0), 1-responses[idx]*SparseProduct(idx, data.Samples(), w)  );
//        if(maxVal > 0)
//        {
//            const list<Pair>& row = data.Samples()[idx];
//            list<Pair>::const_iterator iter = row.begin();
//            while(iter!=row.end())
//            {
//                subgr[iter->idx-1] += -responses[idx]*iter->value;
//                iter++;
//            }
//        }
//    }

//    //=================================
//    subgr /= trainSampleIdx.size();
//    //=================================

//    return subgr;
//}


//Real empRiskCP(const vector<Vec>& a, const vector<Real>& b, const Vec& w)
//{
//    Real val = inner_prod(w, a[0]) + b[0];
//    for(unsigned i = 1;i<a.size();i++)
//    {
//        val = std::max (val, inner_prod(w, a[i]) + b[i]);
//    }
//    return val;
//}



//static Vec TrainBinarySVM( const Data& data,
//                            const std::vector<int>& firstClassIdx,
//                            const std::vector<int>& secondClassIdx,
//                            const Real lambda,  const Real epsilon_abs,
//                            const Real epsilon_tol, const int tMax)
//{
//    int d = data.VarNumber(); // размерность пространства признаков


//    Vec w(d);
//    std::fill(w.begin(), w.end(), 0);
//    int t = 0;
//    Real currentEps = -1;
//    vector<Vec> a;
//    vector<Real> b;



//    do
//    {
//        t++;

//        long long time_a = -gettimeus();
//        a.push_back( empRiskSubgradientBinary(data, firstClassIdx, secondClassIdx, w) );
//        time_a += gettimeus();


//        long long time_b = -gettimeus();
//        b.push_back(
//                    empRiskBinary(data, firstClassIdx, secondClassIdx, w) - inner_prod(w, a.back())
//                   );
//        time_b += gettimeus();

//#ifdef BMRM_INFO
//        cout << endl << "Iteration " << t << endl;
////        cout << "empRisk(w) = " << empRisk(data, w) << endl;


//        cout << "Subgradient calculating time: " << double(time_a)/1000000 << " seconds" << endl;
//        cout << "Coef calculating time: " << double(time_b)/1000000 << " seconds" << endl;

////        cout << "w[" << t-1 << "] = " << w << endl;
////        cout << "a[" << t << "] = " << a.back() << endl;
////        cout << "b[" << t << "] = " << b.back() << endl;
//#endif



//        //==========================================
//        // argmin begin
//        //==========================================
//        Vec alpha(t);

//        long long time_qp = -gettimeus();
//        SolveQP(a, b, lambda, epsilon_tol*0.5, alpha);
//        time_qp += gettimeus();




//        // Получение w из alpha
//        Vec temp(d);
//        std::fill(temp.begin(), temp.end(), 0);
//        for(int i = 0;i<t;i++)
//        {
//            temp = temp + alpha[i]*a[i];
//        }
//        w = -temp/lambda;

//#ifdef BMRM_INFO
//        cout << "J(w) = " << lambda*Omega(w)+empRiskBinary(data, firstClassIdx, secondClassIdx, w) << endl;
////        cout << "EmpRisk(w) = " << empRisk(data, w) << endl;
////        cout << "EmpRiskCP(w) = " << empRiskCP(a, b, w) << endl;
//#endif
//        //==========================================
//        // argmin end
//        //==========================================


//        currentEps = empRiskBinary(data, firstClassIdx, secondClassIdx, w) - empRiskCP(a, b, w);

//#ifdef BMRM_INFO
//        cout << "QP solving time: " << double(time_qp)/1000000 << " seconds" << endl;

//        cout << "Current epsilon = " << currentEps << endl;
//#endif

//    }
//    while(
//          currentEps>epsilon_abs
//          && currentEps>epsilon_tol*(lambda*Omega(w)+empRiskBinary(data, firstClassIdx, secondClassIdx, w))
//          && t<tMax
//         );


//#ifdef BMRM_INFO
//    cout << endl << endl;
//    cout << "BMRM => J(w) = " << lambda*Omega(w)+empRiskBinary(data, firstClassIdx, secondClassIdx, w) << endl;
//    printf("BMRM => Achieved epsilon: %e \n", currentEps);
//    printf("BMRM => Required abs epsilon: %e \n", epsilon_abs);
//    printf("BMRM => Required tol epsilon: %e \n", epsilon_tol);
//    cout << "BMRM => Number of iterations: " << t << " (max - " << tMax << ")" << endl;

//    cout << "w = " << w << endl;
//#endif


//    return w;
//}


//static Real empRiskBinary(const Data& data,
//                    const std::vector<int>& firstClassIdx,
//                    const std::vector<int>& secondClassIdx,
//                    const Vec& w)
//{
//    Real sum = 0;
//    for(unsigned i = 0;i<firstClassIdx.size();i++)
//    {
//        int idx = firstClassIdx[i];
//        sum += max(  Real(0), 1 - SparseProduct(idx, data.Samples(), w)  );
//    }
//    for(unsigned i = 0;i<secondClassIdx.size();i++)
//    {
//        int idx = secondClassIdx[i];
//        sum += max(  Real(0), 1 + SparseProduct(idx, data.Samples(), w)  );
//    }

//    sum /= firstClassIdx.size() + secondClassIdx.size();

//    return sum;
//}


//Vec empRiskSubgradientBinary(const Data& data,
//                              const std::vector<int>& firstClassIdx,
//                              const std::vector<int>& secondClassIdx,
//                              const Vec& w)
//{
//    empRiskSubgradientOneClass(data, firstClassIdx, 1.0, w);

//    Vec subgr =
//            empRiskSubgradientOneClass(data, firstClassIdx, 1.0, w) +
//            empRiskSubgradientOneClass(data, secondClassIdx, -1.0, w);

//    subgr /= firstClassIdx.size()+secondClassIdx.size();
//    return subgr;
//}


//Vec empRiskSubgradientOneClass(const Data& data,
//                              const std::vector<int>& classSampleIdx,
//                              double y,
//                              const Vec& w)
//{
//    Vec subgr;
//    subgr.resize(w.size());
//    std::fill(subgr.begin(), subgr.end(), 0);

//    for(unsigned i = 0;i<classSampleIdx.size();i++)
//    {
//        int idx = classSampleIdx[i];
//        Real maxVal = max(  Real(0), 1-y*SparseProduct(idx, data.Samples(), w)  );
//        if(maxVal > 0)
//        {
//            const list<Pair>& row = data.Samples()[idx];
//            list<Pair>::const_iterator iter = row.begin();
//            while(iter!=row.end())
//            {
//                subgr[iter->idx-1] += -y*iter->value;
//                iter++;
//            }
//        }
//    }

//    return subgr;
//}
