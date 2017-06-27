#include "dense_matrix.h"

// ToDo: определить методы:
// DenseMatrix::LoadFromFile
// DenseMatrix::print

DenseMatrix::DenseMatrix(const double* ptr, int rows_number, int cols_number, int row_step, int col_step)
    : BaseMatrix(ptr, rows_number, cols_number), row_step(row_step), col_step(col_step)
{}

double DenseMatrix::multiply_row_by_Vec(int row, const Vec& vec) const
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

void DenseMatrix::add_row_multiplyed_by_value(Vec& vec, int row, double value) const
{
    assert(0<=row && row<rows_number);
    assert(int(vec.size()) == cols_number);

    for(int i = 0;i<cols_number;i++)
    {
        vec(i) += value*this->at(row, i);
    }
}

void DenseMatrix::print(std::ostream& stream) const
{
    for (int i = 0; i < rows(); i++)
    {
        stream << "[";
        for (int j = 0; j < cols(); j++)
        {
            auto value = at(i, j);

            if (value >= 0)
            {
                stream << " ";
            }
            stream << value;
            if (j != cols()-1)
            {
                stream << " ";
            }
        }
        stream << "]\n";
    }
}

DenseMatrix* DenseMatrix::LoadFromFile(std::string filename)
{
    return nullptr;
}