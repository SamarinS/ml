#include "data.h"


///////////////////////
/// class BaseData ////
///////////////////////

int BaseData::cols() const
{
    return cols_number;
}

int BaseData::rows() const
{
    return rows_number;
}



///////////////////////
/// class DenseData ///
///////////////////////

double DenseData::multiply_row_by_Vec(int row, const Vec& vec) const
{
    assert(0<=row && row<rows_number);
    assert(int(vec.size()) == cols_number);

    double result = 0.;
    for(int i = 0;i<cols_number;i++)
    {
        result += this->at(row, i)*vec(i);
    }
    return result;
}

void DenseData::add_row_multiplyed_by_value(Vec& vec, int row, double value) const
{
    assert(0<=row && row<rows_number);
    assert(int(vec.size()) == cols_number);

    for(int i = 0;i<cols_number;i++)
    {
        vec(i) += value*this->at(row, i);
    }
}
