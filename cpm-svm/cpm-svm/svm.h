#ifndef SVM_H
#define SVM_H


#include "linear_algebra.h"
#include "data.h"




class SVM
{
public:
    //enum {TRAIN, TEST};
    //class Exception {};
    //SVM();
//    void Train(const double* data, const long* resp, int n_samples, int n_vars,
//               int row_step, int col_step,
//               double lambda, double epsilon_abs, double epsilon_tol, int tMax);
    void Train(const BaseData& data, const long* resp,
               double lambda, double epsilon_abs, double epsilon_tol, int tMax);
    //Real Predict(const std::list<Pair>& sample) const;
//    void Predict(const double* data, long* pred,
//                 int n_samples, int n_vars,
//                 int row_step, int col_step) const;
    void Predict(const BaseData& data, long* pred) const;
    //Real CalcError(const Data& data, int type) const;


private:

    std::vector<Vec> betta;
    int n_classes;
};


#endif // SVM_H
