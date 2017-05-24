#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H


#include <list>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/rational.hpp>


//typedef double Real;
using Mat = boost::numeric::ublas::matrix<double>;
using Vec = boost::numeric::ublas::vector<double>;

using ZeroMat = boost::numeric::ublas::zero_matrix<double>;
using ZeroVector = boost::numeric::ublas::zero_vector<double>;


//struct Pair
//{
//    Pair(Real _value, int _idx) : value(_value), idx(_idx) {}

//    Real value;
//    int idx;
//};

//typedef std::vector< std::list<Pair> > SparseMat;


#endif // LINEAR_ALGEBRA_H
