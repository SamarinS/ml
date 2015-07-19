#include <iostream>

#include "test.h"

using namespace std;


#define my_test(name) cout << boolalpha << check_flag(name()) << " - " << #name << endl

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
    cout << "Testing started ..." << endl;

    my_test(Test::DenseData_multiply_row_by_Vec);
    my_test(Test::DenseData_add_row_multiplyed_by_value);
    my_test(Test::test_svm_w_after_training_on_simple_dense_data);

    my_test(Test::SparseData_multiply_row_by_Vec);
    my_test(Test::SparseData_add_row_multiplyed_by_value);
    my_test(Test::test_svm_w_after_training_on_simple_sparse_data);

    if(!tests_passed)
    {
        cout << "Some tests has failed" << endl;
    }
    else
    {
        cout << "All tests passed" << endl;
    }
//    const int n_vars = samples.data->cols();


//    denseData->add_row_multiplyed_by_value(v, 2, 5);
//    cout << v << endl;

    return 0;
}

