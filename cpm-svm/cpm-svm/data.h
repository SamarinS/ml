#ifndef DATA_H
#define DATA_H

#include "linear_algebra.h"

class Data
{
public:
    Data(const double* ptr, int row_step, int col_step)
        : ptr(ptr), row_step(row_step), col_step(col_step) {}
    double operator() (int i, int j) const
    {
        return *(double*)((char*)ptr + i*row_step + j*col_step);
    }

private:
    const double* ptr;
    int row_step;
    int col_step;
};


class BaseData
{
public:
    BaseData(const double* ptr, int rows_number, int cols_number)
        : ptr(ptr), rows_number(rows_number), cols_number(cols_number) {}

    virtual double multiply_row_by_Vec(int row, const Vec& vec) const = 0;
    virtual void add_row_multiplyed_by_value(Vec& vec, int row, double value) const = 0;
    int rows() const;
    int cols() const;

protected:
    const double* ptr;
    int rows_number;
    int cols_number;
};


class DenseData : public BaseData
{
public:
    DenseData(const double* ptr, int rows_number, int cols_number, int row_step, int col_step)
        : BaseData(ptr, rows_number, cols_number), row_step(row_step), col_step(col_step) {}
    double multiply_row_by_Vec(int row, const Vec& vec) const;
    void add_row_multiplyed_by_value(Vec& vec, int row, double value) const;
private:
    int row_step;
    int col_step;

    double at(int i, int j) const
    {
        return *(double*)((char*)ptr + i*row_step + j*col_step);
    }
};


#endif // DATA_H
