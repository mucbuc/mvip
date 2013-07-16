/*
	policy class

	i think this would be greate candidate for a flyweight
	pattern. or even better a policy (do flyweight have 
	any relevance if policies are used?).  
	
	objective:
		implement modular arithmetic functinality. 
*/

#include "mathutills.h"
#include "typetree.h"
#include "context.h"
#include "typeutills.h"
#include "range.h"

#if 0 // ndef _modular_H_8900700
	#define _modular_H_8900700
    
namespace om636
{
    template<class C>
	struct modular : public C 
	{
		// constants
        enum { _mod = 645 };
		
        // types
        typedef C context_type;
		typedef typename context_type::value_type value_type;
		typedef number< modular > num_type;
	
        // using
        using context_type::value_ref;
        
		// resources
		modular();
		modular(const modular &);
		modular(const context_type &);
		~modular();
		modular & operator=(modular);
	
		// comparisons
		bool equal(const num_type &) const;
		int cmp(const num_type &) const;
		int sign() const;
			
		// modifiers
		void add(const num_type &);
		void subtract(const num_type &);
		void mult(const num_type &);
		void divide(const num_type &);
		void remainder(const num_type &);

		// intent
		template<class T, class U>
		static T assign(const U &);

		template<class T, class U>
		static const T to_value(const U &);

		template<class T>
		static void invert(const T &);

		template<class T>
		static void power(T &, const T &);
	
		template<class T>
		static void evaluate(T &);
	};

// non members
	template<class T, class U>
	T & operator>>(T &, number< modular< U > > &);
	
	template<class T, class U>
	T & operator<<(T &, number< modular< U > > &);
    
}   // om636

#include "modular.hxx"

#endif // _modular_H_8900700