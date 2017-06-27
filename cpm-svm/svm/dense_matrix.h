#pragma once

#include "base_matrix.h"

class DenseMatrix : public BaseMatrix
{
public:
    DenseMatrix(const double* ptr, int rows_number, int cols_number, int row_step, int col_step);
    double multiply_row_by_Vec(int row, const Vec& vec) const;
    void add_row_multiplyed_by_value(Vec& vec, int row, double value) const;
    void print(std::ostream& stream) const;

    static DenseMatrix* LoadFromFile(std::string filename);
private:
    int row_step;
    int col_step;

    double at(int i, int j) const
    {
        return *(double*)((char*)ptr + i*row_step + j*col_step);
    }
};
