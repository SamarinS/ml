#ifndef DATA_H
#define DATA_H

#include "linear_algebra.h"

/// Question
/// Calculating data density
/// Empty line??? (multiply_row_by_Vec && add_row_multiplyed_by_value)


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
    DenseData(const double* ptr, int rows_number, int cols_number, int row_step, int col_step);
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


class SparseData : public BaseData
{
public:
    SparseData(const double* ptr, int rows_number, int cols_number,
               const int* indices, int indices_len,
               const int* indptr, int indptr_len);
    double multiply_row_by_Vec(int row, const Vec& vec) const;
    void add_row_multiplyed_by_value(Vec& vec, int row, double value) const;
private:
    const int* indices;
    int indices_len;

    const int* indptr;
    int indptr_len;

    mutable int current_index;
    mutable int current_row;


    void set_row(int i) const;
    bool next_element() const;
    int element_idx() const;
    double element_value() const;
};


#endif // DATA_H
