#ifndef SPARSE_DATA_H
#define SPARSE_DATA_H

#include "data.h"

class SparseData : public BaseData
{
public:
    SparseData(const double* ptr, int rows_number, int cols_number,
               const int* indices, int indices_len,
               const int* indptr, int indptr_len);
    double multiply_row_by_Vec(int row, const Vec& vec) const;
    void add_row_multiplyed_by_value(Vec& vec, int row, double value) const;
    void print(std::ostream& stream) const;

    static SparseData* LoadFromFile(std::string filename);
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

#endif // SPARSE_DATA