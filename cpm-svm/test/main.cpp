#include <iostream>
#include "../cpm-svm/svm.h"

using namespace std;

//class Data
//{
//public:
//    Data(const double* ptr, int row_step, int col_step)
//        : ptr(ptr), row_step(row_step), col_step(col_step)
//    {
//        for(int i = 0;i<6;i++)
//        {
//            cout << ptr[i] << endl;
//        }
//    }
//    double operator() (int i, int j) const
//    {
//        return *((char*)ptr + i*row_step + j*col_step);
//    }

//private:
//    const double* ptr;
//    int row_step;
//    int col_step;
//};


int main()
{
    cout << "Hello World!" << endl;



    SVM clf;

    const int n_samples = 4;
    const int n_vars = 2;
    double data[n_samples*n_vars] = {1., 0.,
                    0., -1.,
                    -1., 0.,
                    0., 1.};

    long resp[n_samples] = {0, 0, 1, 1};

    int row_step = 2*sizeof(double);
    int col_step = sizeof(double);

    clf.Train(data, resp, n_samples, n_vars, row_step, col_step, 1., 0., 0.01, 100);

    long pred[n_samples];
    clf.Predict(data, pred, n_samples, n_vars, row_step, col_step);

    cout << sizeof(long) << endl;

    return 0;
}

