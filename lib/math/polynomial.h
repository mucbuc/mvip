/*
	policy class

*/



#if 0 // ndef _polynomial_H_8900700
	#define _polynomial_H_8900700


#include "components.h"
#include "mathutills.h"
#include "typeutills.h"
#include "debug.h"
#include "singleton.h"
#include <string>

	namespace 
	{
		// 
		template<class T>
		class polynomial_subject;
	}

	template<class T>
	class polynomial 
		: public om636::context< abstract_number< number< polynomial<T> > > *, polynomial_subject<T> >
	{
	private:
		// types
		typedef T value_type;
		typedef number< polynomial > num_type;
		typedef abstract_number< num_type > impl_type;
		
		typedef om636::context< impl_type *, polynomial_subject< value_type > > context_type;
		typedef std::string name_type; 
		
	public:
		
		impl_type * evaluate();
		impl_type * evaluate() const;
	
		// resources
		polynomial();
		polynomial(const polynomial &);
		polynomial(const value_type &);
		~polynomial();
		polynomial & operator=(polynomial);
		void swap(polynomial &);
	
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

		template<class U> 
		static void power(U &, const U &);
	};

	template<class T>
	void swap(polynomial< T > &, polynomial< T > &);

	template<class T, class U>
	T & operator>>(T &, number< polynomial< U > > &);
	
	template<class T, class U>
	T & operator<<(T &, const number< polynomial< U > > &);

	#include "polynomial.hxx"

#endif // _polynomial_H_8900700	