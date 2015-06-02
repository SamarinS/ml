#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H


#include <list>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/rational.hpp>


//typedef double Real;
typedef boost::numeric::ublas::matrix<double> Mat;
typedef boost::numeric::ublas::vector<double> Vec;

typedef boost::numeric::ublas::zero_matrix<double> ZeroMat;
typedef boost::numeric::ublas::zero_vector<double> ZeroVector;


//struct Pair
//{
//    Pair(Real _value, int _idx) : value(_value), idx(_idx) {}

//    Real value;
//    int idx;
//};

//typedef std::vector< std::list<Pair> > SparseMat;


#endif // LINEAR_ALGEBRA_H
