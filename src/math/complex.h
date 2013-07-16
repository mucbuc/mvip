#include "context.h"
#include "debug.h"
#include "number.h"
#include "mathutills.h"
#include "singleton.h"
#include "typeutills.h"
#include "range.h"

#ifndef _complex_H_8900700
	#define _complex_H_8900700

namespace om636
{
    namespace complex_private
	{
		template<class T>
		class complex_subject;
	}

	template<class T>
	class complex 
    : public om636::context< abstract_number< number< complex<T> > > *, complex_private::complex_subject<T> >
    {
    public:
        
		// types
		typedef T value_type;
		typedef number< complex > num_type;
		typedef abstract_number< num_type > impl_type;
		typedef om636::context< impl_type *, complex_private::complex_subject< value_type > > context_type;
		typedef typename value_type::list_type list_type; 
        typedef typename type_at<list_type, 0>::result_type::value_type real_type;
        typedef typename type_at<list_type, 1>::result_type::value_type imaginary_type;
              
        // using 
        using context_type::subject_ref; 
        using context_type::value_ref;
        
        impl_type * evaluate();
		impl_type * evaluate() const;
	
		// resources
		complex();
		complex(const complex &);
		complex(const value_type &);
		~complex();
		complex & operator=(complex);
		void swap(complex &);
		
        // access
        real_type & real(); 
        const real_type & real() const; 
        imaginary_type & imaginary(); 
        const imaginary_type & imaginary() const; 
              
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
	
		// static functionality 
		template<class U> 
		static const U & identity();

		template<class U>
		static void invert(U &);
	
		template<class U, class V>
		static U assign(const V &);

		template<class U, class V>
		static U to_value(const V &);

		static void power(T &, const T &);
    };
	
	template<class T>
	void swap(complex< T > &, complex< T > &);

	template<class T, class U>
	T & operator>>(T &, number< complex< U > > &);
	
	template<class T, class U>
	T & operator<<(T &, const number< complex< U > > &);

	template<class T>
	int sign(const number< complex< T > > & n);
}   // om636

#include "complex.hxx"

#endif // _complex_H_8900700