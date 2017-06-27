#include "test.h"
#include "../svm/svm.h"
#include "../svm/dense_data.h"
#include "../svm/sparse_data.h"

#include <algorithm>
#include <sstream>

DenseData* get_simple_dense_data();
SparseData* get_simple_sparse_data();



//////////////////
/// class Test ///
//////////////////


/// class SVM

bool Test::test_svm_w_after_training_on_simple_data(const BaseData &data)
{
    long resp[] = {0, 0, 1, 1};

    SVM clf;
    clf.Train(data, resp, 1., 0., 0.01, 100);

    const Vec& w = clf.betta()[0];
    return (w.size()==2 && w[0]==0.5 && w[1]==-0.5);
}

bool Test::test_svm_w_after_training_on_simple_dense_data()
{
    const DenseData* data = get_simple_dense_data();
    return Test::test_svm_w_after_training_on_simple_data(*data);
}

bool Test::test_svm_w_after_training_on_simple_sparse_data()
{
    const SparseData* data = get_simple_sparse_data();
    return Test::test_svm_w_after_training_on_simple_data(*data);
}



/// class BaseData

bool Test::BaseData_multiply_row_by_Vec(const BaseData& data)
{
    Vec v(2);
    v[0] = 3;
    v[1] = 4;
    double result = data.multiply_row_by_Vec(3, v);

    return (result == 4);
}

bool Test::BaseData_add_row_multiplyed_by_value(const BaseData& data)
{
    Vec v(2);
    v[0] = 1;
    v[1] = 2;

    data.add_row_multiplyed_by_value(v, 0, -2);

    return (v.size() == 2 && v[0] == -1 && v[1] == 2);
}



/// class DenseData

bool Test::DenseData_multiply_row_by_Vec()
{
    DenseData* data = get_simple_dense_data();
    return BaseData_multiply_row_by_Vec(*data);
}

bool Test::DenseData_add_row_multiplyed_by_value()
{
    DenseData* data = get_simple_dense_data();
    return BaseData_add_row_multiplyed_by_value(*data);
}

bool Test::DenseData_print()
{
    DenseData* data = get_simple_dense_data();
    std::stringstream ss;
    data->print(ss);

    std::string expected = "[ 1  0]\n[ 0 -1]\n[-1  0]\n[ 0  1]\n";

    return ss.str() == expected;
}

/// class SparseData

bool Test::SparseData_multiply_row_by_Vec()
{
    SparseData* data = get_simple_sparse_data();
    return BaseData_multiply_row_by_Vec(*data);
}

bool Test::SparseData_add_row_multiplyed_by_value()
{
    SparseData* data = get_simple_sparse_data();
    return BaseData_add_row_multiplyed_by_value(*data);
}


////////////////////////
/// helper functions ///
////////////////////////

DenseData* get_simple_dense_data()
{
    const int n_samples = 4;
    const int n_vars = 2;
    static double data_array[n_samples*n_vars] =
                   {1., 0.,
                    0., -1.,
                    -1., 0.,
                    0., 1.};

    int row_step = 2*sizeof(double);
    int col_step = sizeof(double);

    static DenseData data(data_array, n_samples, n_vars, row_step, col_step);
    return &data;
}

SparseData* get_simple_sparse_data()
{
    const int n_samples = 4;
    const int n_vars = 2;

    static double ptr[] = {1., -1., -1., 1.};
    static int indices[] = {0, 1, 0, 1};
    int indices_len = 4;
    static int indptr[] = {0,1,2,3,4};
    int indptr_len = 5;

    static SparseData data(ptr, n_samples, n_vars, indices, indices_len, indptr, indptr_len);
    return &data;
}
