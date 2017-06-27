#include "base_matrix.h"

int BaseMatrix::cols() const
{
    return cols_number;
}

int BaseMatrix::rows() const
{
    return rows_number;
}

std::ostream& operator << (std::ostream& stream, const BaseMatrix& data)
{
    data.print(stream);
    return stream;
}