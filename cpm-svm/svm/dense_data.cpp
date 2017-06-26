#include "dense_data.h"

// ToDo: определить методы:
// DenseData::LoadFromFile
// DenseData::print

DenseData::DenseData(const double* ptr, int rows_number, int cols_number, int row_step, int col_step)
    : BaseData(ptr, rows_number, cols_number), row_step(row_step), col_step(col_step)
{}

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

void DenseData::print(std::ostream& stream) const
{
    stream << "print dense data\n";
}

DenseData* DenseData::LoadFromFile(std::string filename)
{
    return nullptr;
}