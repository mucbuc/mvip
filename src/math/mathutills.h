#ifndef MATHUTILLS__INCLUDE_GUARD__2434545345345
	#define MATHUTILLS__INCLUDE_GUARD__2434545345345

#include <utility>
#include <iostream>
#include <valarray>
#include <algorithm>
#include "assert.h"
#include <math.h>


namespace om636
{
    static const double phi( 3.1419999 );
    
    template<class I, class O>
    O convergent( I, I, O);

    template<class T> 
    T mod_inverse(const T&, const T&);

    template<class T>
    T power_factorial(T);

    template<class T>
    T find_power_factorial(T);

    template<class T>
    T find_power_factorial(T, T &);
    
    template<class T> 
    T factorial( const T & );
    
    template<class T>
    T binomal_coefficient( T, const T & );
    
    template<class T> 
    T binary_hyperdelta(const T &, const T &);
    
    template<class T, class U> 
    T find_hypersum( const T &, U & );
    
    
} // om636

#include "mathutills.hxx"

#endif // __MATHUTILLS__INCLUDE_GUARD__2434545345345





#if 0
template<class T>
class variable 
{};

template<class Domain, class F>
class function
{};

namespace relation
{
	struct equivalence;
	
	struct order;
	
	template<class T>
	struct traits;
	
	template<>
	struct traits< equivalence >
	{
		enum { 
			reflexive = true, 
			irreflexive = false,
			symmetric = true, 
			antisymmetric = false,
			asymmetric = false,
			transitive = true };
	};
	
	template<>
	struct traits< partial_order >
	{
		enum { 
			reflexive = true, 
			symmetric = true, 
			antisymmetric = false,
			asymmetric = false,
			transitive = true };
	};
    
	template<>
	struct traits< total_order >
	{
		enum { 
			reflexive = true, 
			symmetric = false,
			antisymmetric = true,
			asymmetric = false,
			transitive = true };
	};
}

#endif	