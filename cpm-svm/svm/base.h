#pragma once

#include "linear_algebra.h"
#include "data.h"

struct SvmParams
{
    SvmParams(double lambda, double epsilon_abs, double epsilon_tol, int tMax)
        : lambda(lambda),
          epsilon_abs(epsilon_abs),
          epsilon_tol(epsilon_tol),
          tMax(tMax) {}

    double lambda;
    double epsilon_abs;
    double epsilon_tol;
    int tMax;
};

struct SvmData
{
    std::vector<Vec> betta;
    int n_classes;
};

void trainSvm(const BaseData& data, const long* resp, const SvmParams& params,
              SvmData* svmData);
void predict(const BaseData& data, long* pred, const SvmData& svmData);
