#ifndef SVM_H
#define SVM_H


#include "linear_algebra.h"
#include "data.h"




class SVM
{
public:
    enum {TRAIN, TEST};
    class Exception {};
    SVM();
    void Train(const Data& data, const Real lambda,  const Real epsilonAbs,
               const Real epsilonTol, const int tMax);
    Real Predict(const std::list<Pair>& sample) const;
    Real CalcError(const Data& data, int type) const;


private:

    std::vector<Vec> betta;
    std::vector<Real> classLabels;
};

#endif // SVM_H
