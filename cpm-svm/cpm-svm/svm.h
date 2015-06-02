#ifndef SVM_H
#define SVM_H


#include "linear_algebra.h"
//#include "data.h"




class SVM
{
public:
    //enum {TRAIN, TEST};
    //class Exception {};
    //SVM();
    void Train(const double* data, const int* resp, int n_samples, int n_vars,
               int row_step, int col_step,
               double lambda, double epsilon_abs, double epsilon_tol, int tMax);
    //Real Predict(const std::list<Pair>& sample) const;
    //Real CalcError(const Data& data, int type) const;


private:

    std::vector<Vec> betta;
};

class Data
{
public:
    Data(const double* ptr, int row_step, int col_step)
        : ptr(ptr), row_step(row_step), col_step(col_step) {}
    double operator() (int i, int j) const
    {
        return *(double*)((char*)ptr + i*row_step + j*col_step);
    }

private:
    const double* ptr;
    int row_step;
    int col_step;
};

#endif // SVM_H
