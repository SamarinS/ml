#include "data.h"

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