#include "test.h"
#include "../svm/svm.h"
#include "../svm/dense_matrix.h"
#include "../svm/sparse_matrix.h"

#include <algorithm>
#include <sstream>

DenseMatrix* get_simple_dense_data();
SparseMatrix* get_simple_sparse_data();



//////////////////
/// class Test ///
//////////////////


/// class SVM

bool Test::test_svm_w_after_training_on_simple_data(const BaseMatrix &data)
{
    long resp[] = {0, 0, 1, 1};

    SVM clf;
    clf.Train(data, resp, 1., 0., 0.01, 100);

    const Vec& w = clf.betta()[0];
    return (w.size()==2 && w[0]==0.5 && w[1]==-0.5);
}

bool Test::test_svm_w_after_training_on_simple_dense_data()
{
    const DenseMatrix* data = get_simple_dense_data();
    return Test::test_svm_w_after_training_on_simple_data(*data);
}

bool Test::test_svm_w_after_training_on_simple_sparse_data()
{
    const SparseMatrix* data = get_simple_sparse_data();
    return Test::test_svm_w_after_training_on_simple_data(*data);
}



/// class BaseMatrix

bool Test::BaseMatrix_multiply_row_by_Vec(const BaseMatrix& data)
{
    Vec v(2);
    v[0] = 3;
    v[1] = 4;
    double result = data.multiply_row_by_Vec(3, v);

    return (result == 4);
}

bool Test::BaseMatrix_add_row_multiplyed_by_value(const BaseMatrix& data)
{
    Vec v(2);
    v[0] = 1;
    v[1] = 2;

    data.add_row_multiplyed_by_value(v, 0, -2);

    return (v.size() == 2 && v[0] == -1 && v[1] == 2);
}



/// class DenseMatrix

bool Test::DenseMatrix_multiply_row_by_Vec()
{
    DenseMatrix* data = get_simple_dense_data();
    return BaseMatrix_multiply_row_by_Vec(*data);
}

bool Test::DenseMatrix_add_row_multiplyed_by_value()
{
    DenseMatrix* data = get_simple_dense_data();
    return BaseMatrix_add_row_multiplyed_by_value(*data);
}

bool Test::DenseMatrix_print()
{
    DenseMatrix* data = get_simple_dense_data();
    std::stringstream ss;
    data->print(ss);

    std::string expected = "[ 1  0]\n[ 0 -1]\n[-1  0]\n[ 0  1]\n";

    return ss.str() == expected;
}

/// class SparseMatrix

bool Test::SparseMatrix_multiply_row_by_Vec()
{
    SparseMatrix* data = get_simple_sparse_data();
    return BaseMatrix_multiply_row_by_Vec(*data);
}

bool Test::SparseMatrix_add_row_multiplyed_by_value()
{
    SparseMatrix* data = get_simple_sparse_data();
    return BaseMatrix_add_row_multiplyed_by_value(*data);
}


////////////////////////
/// helper functions ///
////////////////////////

DenseMatrix* get_simple_dense_data()
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

    static DenseMatrix data(data_array, n_samples, n_vars, row_step, col_step);
    return &data;
}

SparseMatrix* get_simple_sparse_data()
{
    const int n_samples = 4;
    const int n_vars = 2;

    static double ptr[] = {1., -1., -1., 1.};
    static int indices[] = {0, 1, 0, 1};
    int indices_len = 4;
    static int indptr[] = {0,1,2,3,4};
    int indptr_len = 5;

    static SparseMatrix data(ptr, n_samples, n_vars, indices, indices_len, indptr, indptr_len);
    return &data;
}
