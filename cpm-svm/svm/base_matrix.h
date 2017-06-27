#pragma once

#include <iostream>

#include "linear_algebra.h"

/// Question
/// Calculating data density
/// Empty line??? (multiply_row_by_Vec && add_row_multiplyed_by_value)


class BaseMatrix
{
public:
    BaseMatrix(const double* ptr, int rows_number, int cols_number)
        : ptr(ptr), rows_number(rows_number), cols_number(cols_number) {}

    virtual double multiply_row_by_Vec(int row, const Vec& vec) const = 0;
    virtual void add_row_multiplyed_by_value(Vec& vec, int row, double value) const = 0;
    int rows() const;
    int cols() const;

    virtual void print(std::ostream& stream) const = 0;

protected:
    const double* ptr;
    int rows_number;
    int cols_number;
};

std::ostream& operator << (std::ostream& stream, const BaseMatrix& data);
