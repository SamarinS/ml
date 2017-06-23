#include "data.h"

// ToDo: определить методы:
// SparseData::LoadFromFile
// DenseData::LoadFromFile
// SparseData::print
// DenseData::print


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

std::ostream& operator << (std::ostream& stream, const BaseData& data)
{
    data.print(stream);
    return stream;
}

///////////////////////
/// class DenseData ///
///////////////////////

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

////////////////////////
/// class SparseData ///
////////////////////////

SparseData::SparseData(const double *ptr, int rows_number, int cols_number,
                       const int *indices, int indices_len,
                       const int *indptr, int indptr_len)
    : BaseData(ptr, rows_number, cols_number),
      indices(indices), indices_len(indices_len),
      indptr(indptr), indptr_len(indptr_len)
{
}

//double SparseProduct(int rowIdx, SparseData& samples, const Vec& vec)
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

double SparseData::multiply_row_by_Vec(int row, const Vec& vec) const
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

void SparseData::add_row_multiplyed_by_value(Vec &vec, int row, double value) const
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

void SparseData::set_row(int i) const
{
    assert(0<=i && i<indptr_len-1);
    current_index = indptr[i];
    current_row = i;
}

bool SparseData::next_element() const
{
    assert( (indptr[current_row]<=current_index) && (current_index<indptr[current_row+1]) );

    current_index++;
    if(current_index==indptr[current_row+1])
    {
        return false;
    }
    return true;
}

int SparseData::element_idx() const
{
    assert( (indptr[current_row]<=current_index) && (current_index<indptr[current_row+1]) );
    return indices[current_index];
}

double SparseData::element_value() const
{
    assert( (indptr[current_row]<=current_index) && (current_index<indptr[current_row+1]) );
    return ptr[current_index];
}

void SparseData::print(std::ostream& stream) const
{
    stream << "print sparse data\n";
}

SparseData* SparseData::LoadFromFile(std::string filename)
{ 
    return nullptr;
}
