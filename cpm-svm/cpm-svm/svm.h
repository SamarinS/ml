#ifndef SVM_H
#define SVM_H

/// Question
/// Is it necessary to check if input data is not empty
/// in methods SVM.Train and SVM.Predict?


#include "linear_algebra.h"
#include "data.h"




class SVM
{
public:
    void Train(const BaseData& data, const long* resp,
               double lambda, double epsilon_abs, double epsilon_tol, int tMax);
    void Predict(const BaseData& data, long* pred) const;

private:

    std::vector<Vec> betta;
    int n_classes;
};


#endif // SVM_H
