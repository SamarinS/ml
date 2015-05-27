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

    const int d_size = 6;
    double data[d_size];
    for(int i = 0;i<d_size;i++)
    {
        data[i] = i;
    }

//    double p = *(data + 2);

    const int r_size = 4;
    int resp[r_size];
    for(int i = 0;i<r_size;i++)
    {
        if(i%2==0)
        {
            resp[i] = 0;
        }
        else
        {
            resp[i] = 1;
        }
    }

    int row_step = 3*sizeof(double);
    int col_step = sizeof(double);
    int n_samples = 2;
    int n_vars = 2;
//    Data d(data, row_step, col_step);
//    for(int i = 0;i < n_samples;i++)
//    {
//        for(int j = 0;j < n_vars;j++)
//        {
//            std::cout << d(i, j) << " ";
//        }
//        std::cout << std::endl;
//    }
    clf.Train(data, resp, n_samples, n_vars, row_step, col_step, 1., 0., 0.01, 100);
    return 0;
}

