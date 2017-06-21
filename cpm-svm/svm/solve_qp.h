#ifndef SOLVE_QP_H
#define SOLVE_QP_H

#include "linear_algebra.h"



void SolveQP(std::vector<double>& gram_memory, std::vector<Vec>& a, std::vector<double>& b, double lambda, double epsilon_tol,
             Vec& alpha);


#endif // SOLVE_QP_H
