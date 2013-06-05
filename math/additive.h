/*
	policy class

	i think this would be greate candidate for a flyweight
	pattern. or even better a policy (do flyweight have 
	any relevance if policies are used?).  
	
	objective:
		implement additive arithmetic functionality.

	note: this is nice, but no cigar!!
		members of addtive need to be objects, functors, ready for mass consumption.
		
		example for a vector: 
		
			bool foo(T m, T n)
			{
				functor f( equal ); 
				return (*m).traverse_units( f, (*n) ); 	
			}
			
		my complaint here is that i need to write another equal functor, cant i use the 
		one used by T itself??? 
		
		like this: 
		
			bool foo(T m, T n)
			{	return (*m).traverse_units( T::equal, (*n) ); 	}
	
		to take it to the next level of abstraction: 
			additvie, multiplicative, matrix, modular are factories that create functors
			depending on types, or states. 

    design critisism: 
        it seems hard to add states, for example square. one would have to modify most existing states to incorpete new one
 
 
-	finite state machine
-	when switching from addition opeatoins to multiplication, comparison ... 
-	call evaluate()
 
states:
	negative
	positive
	zero
	unknown
 
 
redesign: 
it seems like this is a very concrete implementation. the user could not change state on evaluation (no ballancing) or use some prime
factorization and lookup scheme for additive. my first thougt would be to move additive into class template and providing policies for these
decisions. should also support values types other than tuples, like valarrays, vectors, c-arrays, custom...
before i start i would also like to inject error and feedback policy.
 
 
state_policy: 
    default (tuple), valarray, c-array, container, 
 
feedback_policy (stackable):
    none, debug, log, visual
 
error_policy,           (checking, reporting, handling?)
    log,
 
evaluation_policy:      <== non sense, this is what additive/multiplicative is itself
    cached, on the fly, store
 

 
*/

#ifndef _additive_H_8900700
#define _additive_H_8900700

#include <om636/components/context.h>
#include <om636/components/observer.h>
#include <om636/components/range.h>
#include <om636/core/typeutills.h>
#include <om636/create/singleton.h>
#include <om636/math/mathfunctors.h>
#include <om636/math/mathutills.h>
#include <om636/math/observer.h>
#include <tuple>

namespace om636
{
    namespace additive
    {
        template<class T>
        struct policy
        : public math::observer< T >
        {
            typedef T context_type;
            typedef math::observer<context_type> observer_type;
            typedef typename tuple_append< typename default_subject::traits<context_type>::value_type, observer_type * >::type value_type;
            typedef typename std::tuple_element<0, value_type>::type positive_type;
            typedef typename std::tuple_element<1, value_type>::type negative_type;
            
            template<class V>
            static value_type on_init(V &);
            
            template<class V, class W>
            static value_type on_init(V &, const W &);
            
        	template<class V>
            static V to_value(const context_type &);
            
            static positive_type & pos_ref(context_type &);
            static const positive_type & pos_ref(const context_type &);
            static negative_type & neg_ref(context_type &);
            static const negative_type & neg_ref(const context_type &);
            static observer_type * & state(context_type &);
            static observer_type * state(const context_type &);
                        
            static observer_type * evaluate(context_type &);
            static observer_type * evaluate(const context_type &);
            
            static observer_type * unknown();
            static observer_type * zero();
            static observer_type * positive();
            static observer_type * negative();
        };

    } // additive
    
}   // om636
        
#include "additive.hxx"

#endif // _additive_H_8900700	