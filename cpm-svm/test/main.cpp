#include <iostream>
#include "../cpm-svm/svm.h"

using namespace std;

struct Samples
{
    BaseData* data;
    long* resp;

    Samples()
    {
        const int n_samples = 4;
        const int n_vars = 2;
        static double data[n_samples*n_vars] = {1., 0.,
                        0., -1.,
                        -1., 0.,
                        0., 1.};

        int row_step = 2*sizeof(double);
        int col_step = sizeof(double);

        this->data = new DenseData(data, n_samples, n_vars, row_step, col_step);
        static long resp_array[] = {0, 0, 1, 1};
        this->resp = resp_array;
    }
};


int main()
{
    cout << "Testing..." << endl;

    Samples samples;

    SVM clf;
    clf.Train(*samples.data, samples.resp, 1., 0., 0.01, 100);

    const int n_samples = samples.data->rows();
    long pred[n_samples];
    clf.Predict(*samples.data, pred);

//    cout << sizeof(long) << endl;


//
//    Vec v(n_vars);
//    v[0] = 3;
//    v[1] = 4;
//    cout << denseData->multiply_row_by_Vec(3, v) << endl;
//    denseData->add_row_multiplyed_by_value(v, 2, 5);
//    cout << v << endl;

    return 0;
}

