#ifndef SVM_H
#define SVM_H


//#include "linear_algebra.h"
//#include "data.h"




class SVM
{
public:
    //enum {TRAIN, TEST};
    //class Exception {};
    //SVM();
    void Train(double* data, int* resp, int n_samples, int n_vars,
               int row_offset, int col_offset,
               double lambda, double epsilonAbs, double epsilonTol, int tMax);
    //Real Predict(const std::list<Pair>& sample) const;
    //Real CalcError(const Data& data, int type) const;


private:

    //std::vector<Vec> betta;
    double** betta;

    //std::vector<Real> classLabels;
};

#endif // SVM_H
