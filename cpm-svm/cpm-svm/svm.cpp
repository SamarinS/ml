#include "svm.h"

void SVM::Train(const BaseData &data, const long* resp,
                 double lambda, double epsilon_abs, double epsilon_tol, int tMax)
{
    SvmParams params(lambda, epsilon_abs, epsilon_tol, tMax);

    trainSvm(data, resp, params, &svmData);
}

void SVM::Predict(const BaseData &data, long *pred) const
{
    predict(data, pred, svmData);
}

int SVM::n_classes() const
{
    return svmData.n_classes;
}

const std::vector<Vec>& SVM::betta() const
{
    return svmData.betta;
}
