#include <iostream>

#include "test.h"


#define my_test(name) std::cout << std::boolalpha << check_flag(name()) << \
                      " - " << #name << std::endl

bool tests_passed = true;

bool check_flag(bool flag)
{
    if(flag == false)
    {
        tests_passed = false;
    }
    return flag;
}


int main()
{
    std::cout << "Testing started ..." << std::endl;

    my_test(Test::DenseData_multiply_row_by_Vec);
    my_test(Test::DenseData_add_row_multiplyed_by_value);
    my_test(Test::test_svm_w_after_training_on_simple_dense_data);

    my_test(Test::SparseData_multiply_row_by_Vec);
    my_test(Test::SparseData_add_row_multiplyed_by_value);
    my_test(Test::test_svm_w_after_training_on_simple_sparse_data);

    if(!tests_passed)
    {
        std::cout << "Some tests has failed" << std::endl;
    }
    else
    {
        std::cout << "All tests passed" << std::endl;
    }
//    const int n_vars = samples.data->cols();


//    denseData->add_row_multiplyed_by_value(v, 2, 5);
//    cout << v << endl;

    return 0;
}

