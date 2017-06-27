#pragma once

#include "../svm/data.h"



class Test
{
public:
    // svm
    static bool test_svm_w_after_training_on_simple_dense_data();
    static bool test_svm_w_after_training_on_simple_sparse_data();

    // BaseData, DenseData, SparseData
    static bool DenseData_multiply_row_by_Vec();
    static bool DenseData_add_row_multiplyed_by_value();
    static bool DenseData_print();

    static bool SparseData_multiply_row_by_Vec();
    static bool SparseData_add_row_multiplyed_by_value();

private:
    static bool test_svm_w_after_training_on_simple_data(const BaseData& data);
    static bool BaseData_multiply_row_by_Vec(const BaseData& data);
    static bool BaseData_add_row_multiplyed_by_value(const BaseData& data);

};
