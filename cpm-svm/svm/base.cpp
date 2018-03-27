#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>

#include "base.h"
#include "timer.h"
#include "solve_qp.h"


static double empRiskCP(const std::vector<Vec>& a, const std::vector<double>& b, const Vec& w);
static double Omega(const Vec& w);


static double empRiskBinary(const BaseMatrix& data,
                    const std::vector<int>& firstClassIdx,
                    const std::vector<int>& secondClassIdx,
                    const Vec& w);

static Vec empRiskSubgradientOneClass(const BaseMatrix& data,
                              const std::vector<int>& classSampleIdx,
                              double y,
                              const Vec& w);

static Vec empRiskSubgradientBinary(const BaseMatrix& data,
                              const std::vector<int>& firstClassIdx,
                              const std::vector<int>& secondClassIdx,
                              const Vec& w);

static Vec TrainBinarySVM(const BaseMatrix& data,
                            const std::vector<int>& firstClassIdx,
                            const std::vector<int>& secondClassIdx,
                            const SvmParams& params);

////--------------------------------------------------------------------------------

void trainSvm(const BaseMatrix &data, const long *resp, const SvmParams &params, SvmData *svmData)
{
    long long training_time = -gettimeus();

    int& n_classes = svmData->n_classes;
    std::vector<Vec>& betta = svmData->betta;

    const int n_samples = data.rows();

    n_classes = int(1 + *std::max_element(resp, resp + n_samples));

    std::vector<std::vector<int> > classIdxVectors(n_classes);
    for(int i = 0;i<n_samples;i++)
    {
        int classNumber = int(resp[i]);
        classIdxVectors[classNumber].push_back(i);
    }


    betta.clear();
    for(int i = 0;i<n_classes;i++)
    {
        for(int j = i+1;j<n_classes;j++)
        {
            #ifdef BMRM_INFO
            std::cout << "class " << i << " vs " << j << std::endl;
            #endif
            Vec w = TrainBinarySVM(data,
                                   classIdxVectors[i], classIdxVectors[j],
                                   params);
            betta.push_back(w);
        }
    }

    training_time += gettimeus();
    #ifdef BMRM_INFO
    std::cout << "trainSvm time: " << double(training_time)/1000000 << " seconds" << std::endl;
    #endif
}

void predict(const BaseMatrix &data, long *pred, const SvmData &svmData)
{
    int n_classes = svmData.n_classes;
    const std::vector<Vec>& betta = svmData.betta;

    assert(!betta.empty());

    for(int sample_idx = 0;sample_idx<data.rows();sample_idx++)
    {
        std::vector<int> classVote(n_classes, 0);

        int k = 0;
        for(int i = 0;i<n_classes;i++)
        {
            for(int j = i+1;j<n_classes;j++)
            {
                double result = data.multiply_row_by_Vec(sample_idx, betta[k]);


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

        auto iter = std::max_element(classVote.begin(), classVote.end());
        pred[sample_idx] = std::distance(classVote.begin(), iter);
    }
}

////------------------------------------------------------------------------------------------

double Omega(const Vec& w)
{
    return double(0.5)*inner_prod(w, w);
}


double empRiskCP(const std::vector<Vec>& a, const std::vector<double>& b, const Vec& w)
{
    double val = inner_prod(w, a[0]) + b[0];
    for(std::vector<Vec>::size_type i = 1;i<a.size();i++)
    {
        val = std::max (val, inner_prod(w, a[i]) + b[i]);
    }
    return val;
}



static Vec TrainBinarySVM(const BaseMatrix& data,
                            const std::vector<int>& firstClassIdx,
                            const std::vector<int>& secondClassIdx,
                            const SvmParams& params)
{
    const double lambda = params.lambda;
    const double epsilon_abs = params.epsilon_abs;
    const double epsilon_tol = params.epsilon_tol;
    const int tMax = params.tMax;

    int d = data.cols(); // размерность пространства признаков


    Vec w(d);
    std::fill(w.begin(), w.end(), 0);
    int t = 0;
    double currentEps = -1;
    std::vector<Vec> a;
    std::vector<double> b;
    std::vector<double> gram_memory;
    double currentEmpRiskValue = empRiskBinary(data, firstClassIdx, secondClassIdx, w);


    do
    {
        long long time_iteration = -gettimeus();

        t++;

        long long time_a = -gettimeus();
        a.push_back( empRiskSubgradientBinary(data, firstClassIdx, secondClassIdx, w) );
        time_a += gettimeus();

        b.push_back(currentEmpRiskValue - inner_prod(w, a.back()));

        //==========================================
        // argmin begin
        //==========================================
        Vec alpha(t);

        long long time_qp = -gettimeus();
        SolveQP(gram_memory, a, b, lambda, epsilon_tol*0.5, alpha);
        time_qp += gettimeus();

        // Получение w из alpha
        Vec temp(d);
        std::fill(temp.begin(), temp.end(), 0);
        for(int i = 0;i<t;i++)
        {
            temp = temp + alpha[i]*a[i];
        }
        w = -temp/lambda;

        long long time_empRisk = -gettimeus();
        currentEmpRiskValue = empRiskBinary(data, firstClassIdx, secondClassIdx, w);
        time_empRisk += gettimeus();

#ifdef BMRM_INFO
        std::cout << std::endl << "Iteration " << t << std::endl;
//        cout << "empRisk(w) = " << empRisk(data, w) << endl;


        std::cout << "Subgradient calculating time: " << double(time_a)/1000000 << " seconds" << std::endl;
        std::cout << "Emp risk calculating time: " << double(time_empRisk)/1000000 << " seconds" << std::endl;

//        cout << "w[" << t-1 << "] = " << w << endl;
//        cout << "a[" << t << "] = " << a.back() << endl;
//        cout << "b[" << t << "] = " << b.back() << endl;
#endif

#ifdef BMRM_INFO
        std::cout << "J(w) = " << lambda*Omega(w)+currentEmpRiskValue << std::endl;
//        cout << "EmpRisk(w) = " << empRisk(data, w) << endl;
//        cout << "EmpRiskCP(w) = " << empRiskCP(a, b, w) << endl;
#endif
        //==========================================
        // argmin end
        //==========================================


        currentEps = currentEmpRiskValue - empRiskCP(a, b, w);

#ifdef BMRM_INFO
        std::cout << "QP solving time: " << double(time_qp)/1000000 << " seconds" << std::endl;

        std::cout << "Current epsilon = " << currentEps << std::endl;
#endif

        bool continueFlag =
                currentEps>epsilon_abs
                && currentEps>epsilon_tol*(lambda*Omega(w)+currentEmpRiskValue)
                && t<tMax;

        time_iteration += gettimeus();

#ifdef BMRM_INFO
        std::cout << "iteration time: " << double(time_iteration)/1000000 << std::endl;
#endif

        if (!continueFlag) break;
    }
    while(true);


#ifdef BMRM_INFO
    std::cout << std::endl << std::endl;
    std::cout << "BMRM => J(w) = " << lambda*Omega(w)+empRiskBinary(data, firstClassIdx, secondClassIdx, w) << std::endl;
    printf("BMRM => Achieved epsilon: %e \n", currentEps);
    printf("BMRM => Required abs epsilon: %e \n", epsilon_abs);
    printf("BMRM => Required tol epsilon: %e \n", epsilon_tol);
    std::cout << "BMRM => Number of iterations: " << t << " (max - " << tMax << ")" << std::endl;

    std::cout << "w = " << w << std::endl;
#endif


    return w;
}


static double empRiskBinary(const BaseMatrix& data,
                    const std::vector<int>& firstClassIdx,
                    const std::vector<int>& secondClassIdx,
                    const Vec& w)
{
    double sum = 0;
    for(std::vector<int>::size_type i = 0;i<firstClassIdx.size();i++)
    {
        int idx = firstClassIdx[i];
        sum += std::max(  double(0), 1 - data.multiply_row_by_Vec(idx, w)  );
    }
    for(std::vector<int>::size_type i = 0;i<secondClassIdx.size();i++)
    {
        int idx = secondClassIdx[i];
        sum += std::max(  double(0), 1 + data.multiply_row_by_Vec(idx, w)  );
    }

    sum /= firstClassIdx.size() + secondClassIdx.size();

    return sum;
}


static Vec empRiskSubgradientBinary(const BaseMatrix& data,
                              const std::vector<int>& firstClassIdx,
                              const std::vector<int>& secondClassIdx,
                              const Vec& w)
{
    Vec subgr =
            empRiskSubgradientOneClass(data, firstClassIdx, 1.0, w) +
            empRiskSubgradientOneClass(data, secondClassIdx, -1.0, w);

    subgr /= firstClassIdx.size()+secondClassIdx.size();
    return subgr;
}


Vec empRiskSubgradientOneClass(const BaseMatrix &data,
                              const std::vector<int>& classSampleIdx,
                              double y,
                              const Vec& w)
{
    Vec subgr;
    subgr.resize(w.size());
    std::fill(subgr.begin(), subgr.end(), 0);

    for(std::vector<int>::size_type i = 0;i<classSampleIdx.size();i++)
    {
        int idx = classSampleIdx[i];
        double maxVal = std::max(  double(0), 1-y*data.multiply_row_by_Vec(idx, w) );
        if(maxVal > 0)
        {
            data.add_row_multiplyed_by_value(subgr, idx, -y);
        }
    }

    return subgr;
}
