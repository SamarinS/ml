#pragma once

#include "../svm/base_matrix.h"



class Test
{
public:
    // svm
    static bool test_svm_w_after_training_on_simple_dense_data();
    static bool test_svm_w_after_training_on_simple_sparse_data();

    // BaseMatrix, DenseMatrix, SparseMatrix
    static bool DenseMatrix_multiply_row_by_Vec();
    static bool DenseMatrix_add_row_multiplyed_by_value();
    static bool DenseMatrix_print();

    static bool SparseMatrix_multiply_row_by_Vec();
    static bool SparseMatrix_add_row_multiplyed_by_value();

private:
    static bool test_svm_w_after_training_on_simple_data(const BaseMatrix& data);
    static bool BaseMatrix_multiply_row_by_Vec(const BaseMatrix& data);
    static bool BaseMatrix_add_row_multiplyed_by_value(const BaseMatrix& data);

};
