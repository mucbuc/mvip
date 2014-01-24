/*
	type: 
		policy class

	objective:
		implement matrix arithmetic
	
	note: 
		- swap is implemented by template parameter C 
*/

#include "context.h"
#include "debug.h"
#include "mathutills.h"
#include "singleton.h"
#include "typeutills.h"
#include "mathfunctors.h"
#include <tuple>

#ifdef _matrix_H_09u098
	#define _matrix_H_09u098

namespace om636
{
    template<class C>
	struct matrix : public C
	{
		// types
        typedef C context_type;
		typedef typename context_type::value_type value_type;
		typedef number<matrix> num_type;
		
        // using
        using context_type::value_ref; 
        
        // constants
		enum { rank = std::tuple_size< value_type >::value };
	
		// resources
		matrix();
		matrix(const matrix &);
		matrix(const context_type &);
        matrix(const value_type &);
        template<class T, class U> matrix(const context<T, U> &);
       
        ~matrix();
		matrix & operator=(matrix);

		template<class T, class U>
		static T assign(const U &);

		template<class T, class U, class F>
		static F to_value(const U &, F);

		template<class T>
		static void invert(const T &);

		// comparisons
		bool equal(const num_type &, const num_type &) const;
		int sign(const num_type &, const num_type &) const;
		int sign(const num_type &) const;
			
		// modifiers
		void add(num_type &, const num_type &) const;
		void subtract(num_type &, const num_type &) const;
		void mult(num_type &, const num_type &) const;
		void divide(num_type &, const num_type &) const;
		void remainder(num_type &, const num_type &) const;
	
		template<class T> 
		void outer_product(const T &) const;
	
		template<class T>
		static void power(T &, const T &);
	
		template<class T>
		static void evaluate(T &);
	
		template<class T, class U>
		T reduce(U);
	};
}   // om636

#include "matrix.hxx"

#endif // _matrix_H_09u098