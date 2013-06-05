#ifndef _multiplicative_H_8900700
#define _multiplicative_H_8900700

#include <om636/components/context.h>
#include <om636/components/observer.h>
#include <om636/components/range.h>
#include <om636/core/typeutills.h>
#include <om636/create/singleton.h>
#include <om636/math/observer.h>
#include <om636/math/mathutills.h>
#include <om636/math/mathfunctors.h>

namespace om636
{
	namespace multiplicative
	{
        template<class T>
        struct policy
        : public math::observer< T >
        {
            typedef T context_type;
            typedef math::observer<context_type> observer_type;
            typedef typename tuple_append< typename default_subject::traits<context_type>::value_type, observer_type * >::type value_type;
            typedef typename std::tuple_element<0, value_type>::type numerator_type;
            typedef typename std::tuple_element<1, value_type>::type denumerator_type;
            
            template<class V>
            static value_type on_init(V &);
            
            template<class V, class W>
            static value_type on_init(V &, const W &);
            
        	template<class V>
            static V to_value(const context_type &);
            
            static numerator_type & num_ref(context_type &);
            static const numerator_type & num_ref(const context_type &);
            static denumerator_type & den_ref(context_type &);
            static const denumerator_type & den_ref(const context_type &);
            static observer_type * & state(context_type &);
            static observer_type * state(const context_type &);
            
            static observer_type * evaluate(context_type &);
            static observer_type * evaluate(const context_type &);
            
            static observer_type * not_factored();
            static observer_type * unit();
            static observer_type * factored();
        };

	}	// multiplicative
	
}   // om636

#include "multiplicative.hxx"

#endif // _multiplicative_H_8900700