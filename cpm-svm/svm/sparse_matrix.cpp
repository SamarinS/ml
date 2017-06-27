#include "sparse_matrix.h"

// ToDo: определить методы:
// SparseMatrix::LoadFromFile
// SparseMatrix::print

SparseMatrix::SparseMatrix(const double *ptr, int rows_number, int cols_number,
                       const int *indices, int indices_len,
                       const int *indptr, int indptr_len)
    : BaseMatrix(ptr, rows_number, cols_number),
      indices(indices), indices_len(indices_len),
      indptr(indptr), indptr_len(indptr_len)
{
}

//double SparseProduct(int rowIdx, SparseMatrix& samples, const Vec& vec)
//{
//    double result = 0.;

//    samples.set_row(rowIdx);
//    do
//    {
//        int col_idx = samples.element_idx();
//        double value = samples.element_value();
//        result += value*vec(col_idx);
//    }
//    while(samples.next_element());
////    for(int i = 0;i<vec.size();i++)
////    {
////        result += samples(rowIdx, i)*vec(i);
////    }

//    return result;
//}

double SparseMatrix::multiply_row_by_Vec(int row, const Vec& vec) const
{
    double result = 0.0;

    set_row(row);
    do
    {
        int col_idx = element_idx();
        double value = element_value();
        result += value*vec(col_idx);
    }
    while(next_element());

    return result;
}

void SparseMatrix::add_row_multiplyed_by_value(Vec &vec, int row, double value) const
{
    set_row(row);
    do
    {
        int col_idx = element_idx();
        double elem_value = element_value();
        vec(col_idx) += elem_value*value;
    }
    while(next_element());
}

void SparseMatrix::set_row(int i) const
{
    assert(0<=i && i<indptr_len-1);
    current_index = indptr[i];
    current_row = i;
}

bool SparseMatrix::next_element() const
{
    assert( (indptr[current_row]<=current_index) && (current_index<indptr[current_row+1]) );

    current_index++;
    if(current_index==indptr[current_row+1])
    {
        return false;
    }
    return true;
}

int SparseMatrix::element_idx() const
{
    assert( (indptr[current_row]<=current_index) && (current_index<indptr[current_row+1]) );
    return indices[current_index];
}

double SparseMatrix::element_value() const
{
    assert( (indptr[current_row]<=current_index) && (current_index<indptr[current_row+1]) );
    return ptr[current_index];
}

void SparseMatrix::print(std::ostream& stream) const
{
    stream << "print sparse matrix\n";
}

SparseMatrix* SparseMatrix::LoadFromFile(std::string filename)
{ 
    return nullptr;
}