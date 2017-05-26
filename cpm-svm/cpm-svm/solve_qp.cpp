#include "solve_qp.h"


#ifdef BMRM_INFO
#include "timer.h"
#include <iostream>
#endif //BMRM_INFO


typedef double Real;


Real Delta(const Vec& alpha, const Vec& b_minus_H_alpha, const Mat& H, int u, int v);


void SolveQP(std::vector<double> &gram_memory, std::vector<Vec>& a, std::vector<double> &b, double lambda, double epsilon_tol,
             Vec& alpha)
{
    int n = b.size();
    Vec bVec(n);
    for(int i = 0;i<n;i++)
    {
        bVec[i] = b[i];
    }

//    //==========================count density
//    int count = 0;
//    Vec& v = a[n-1];
//    for(int i = 0;i<v.size();i++)
//    {
//        if(v(i)!=0)
//        {
//            count++;
//        }
//    }
//    cout << "density " << double(count)/v.size()*100 << "%" << endl;
//    //==========================

    std::fill(alpha.begin(), alpha.end(), 1./n);

    Mat H(n, n);

    ///===========================
    /// begin calculating matrix H
    /// ==========================
#ifdef BMRM_INFO
    long long time_Hnn_calc = -gettimeus();
#endif //BMRM_INFO

    for(int i = 0;i<n;i++)
    {
        gram_memory.push_back(inner_prod(a[i], a[n-1]));
    }

    for(int i = 0;i<n;i++)
    {
        for(int j = i;j<n;j++)
        {
            H(i,j) = gram_memory[j*(j+1)/2 + i] / lambda;
            H(j,i) = H(i,j);
        }
    }
#ifdef BMRM_INFO
    time_Hnn_calc += gettimeus();
#endif //BMRM_INFO
    ///===========================
    /// end calculating matrix H
    /// ==========================

    Vec b_minus_H_alpha = bVec - prod(H, alpha);


    ///===========================
    /// begin search loop
    /// ==========================
#ifdef BMRM_INFO
    long long time_while = -gettimeus();
#endif //BMRM_INFO

    int iter_count = 0;
    while( *std::max_element(b_minus_H_alpha.begin(), b_minus_H_alpha.end()) -
           inner_prod(alpha, b_minus_H_alpha)
           >
           epsilon_tol*fabs( inner_prod(bVec,alpha) - 0.5*inner_prod(alpha, prod(H, alpha)) )
         )
    {
        Real maxValue = b_minus_H_alpha(0);
        int maxIdx = 0;
        for(int i = 0;i<n;i++)
        {
            Real m = b_minus_H_alpha(i);
            if(m>maxValue)
            {
                maxValue = m;
                maxIdx = i;
            }
        }

        int u = maxIdx;


        Real maxDelta = -1;
        int v = -1;
        for(int i = 0;i<n;i++)
        {
            if(alpha(i)>0 && b_minus_H_alpha(u)>b_minus_H_alpha(i))
            {
                Real d = Delta(alpha, b_minus_H_alpha, H, u, i);
                if(d>maxDelta)
                {
                    v = i;
                    maxDelta = d;
                }
            }
        }


        Vec betta = alpha;
        betta(v) = 0;
        betta(u) = alpha(u) + alpha(v);

        Real H_sum = H(u,u) - 2*H(u,v) + H(v,v);
        Real tau = std::min(1., (b_minus_H_alpha(u)-b_minus_H_alpha(v)) / (alpha(v)*H_sum));


        alpha = (1-tau)*alpha + tau*betta;
        b_minus_H_alpha = bVec-prod(H,alpha);

        iter_count++;
    }

    ///===========================
    /// end search loop
    /// ==========================
#ifdef BMRM_INFO
    time_while += gettimeus();
    std::cout << "QP Hnn_calc time: " << double(time_Hnn_calc)/1000000 << " seconds" << std::endl;
    std::cout << "QP cycle time: " << double(time_while)/1000000 << " seconds" << std::endl;
    std::cout << "QP iter number: " << iter_count << std::endl;
#endif //BMRM_INFO
}



Real Delta(const Vec& alpha, const Vec& b_minus_H_alpha, const Mat& H, int u, int v)
{
    Real H_sum = H(u,u) - 2*H(u,v) + H(v,v);

    if( b_minus_H_alpha(u)-b_minus_H_alpha(v) < alpha(v)*H_sum )
    {
        return pow(b_minus_H_alpha(u)-b_minus_H_alpha(v), 2) / (2*H_sum);
    }
    else
    {
        return alpha(v)*(b_minus_H_alpha(u)-b_minus_H_alpha(v)) - 0.5*pow(alpha(v), 2)*H_sum;
    }
}


