#include "core.h"
#include "componentsfwd.h"
#include "number.h"
#include "mathutills.h"


#include <math.h>

#ifndef _COMPRESSIVE_H_8900700
	#define _COMPRESSIVE_H_8900700

namespace om636
{
	template<class T>
	class compressive : public T
	{
	public:
        // types
		typedef number< compressive > num_type;
		typedef T context_type; 
		typedef context_type value_type; 
        typedef om636::null_type list_type; 
		
        // using
        using context_type::swap; 
        
		// resources
		compressive();
		compressive(const compressive &);
		compressive(const context_type &);
		~compressive();
		compressive & operator=(compressive);
	
		// comparisons
		bool equal(const num_type &, const num_type &) const;
		int cmp(const num_type &, const num_type &) const;
		int sign(const num_type &) const;
			
		// modifiers
		void add(num_type &, const num_type &) const;
		void subtract(num_type &, const num_type &) const;
		void mult(num_type &, const num_type &) const;
		void divide(num_type &, const num_type &) const;
		void remainder(num_type &, const num_type &) const;
	
        // static functionality 
		template<class U, class V>
		static U assign(const V &);

		template<class U, class V>
		static U to_value(const V &);
	};

	template<class T, class U>
	T & operator>>(T &, number< compressive< U > > &);
	
	template<class T, class U>
	T & operator<<(T &, const number< compressive< U > > &);

	template<class T>
	int sign(const number< compressive< T > > & n);
    
}   // om636

#include "compressive.hxx"

#endif // _COMPRESSIVE_H_8900700