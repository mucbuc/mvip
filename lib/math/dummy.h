
#ifndef _dummy_H_8900700
	#define _dummy_H_8900700

#include <om636/lib/core/core.h>
#include <om636/lib/components/context.h>
#include <om636/lib/math/mathfwd.h>
#include <om636/lib/math/utills.h>

namespace om636
{
    template<class T>
    struct dummy_policy
    {
        typedef T context_type;
        typedef typename default_subject::traits<T>::value_type value_type;
        
        template<class V>
        static value_type on_init(V &);
        
        template<class V, class W>
        static value_type on_init(V &, const W &);
        
        template<class V>
        static V to_value(const context_type &);
        
        // comparisons
        virtual bool on_equal(const context_type &, const context_type &) const;
        virtual int on_cmp(const context_type &, const context_type &) const;
        virtual int on_sign(const context_type &) const;
        
        // modifiers
        virtual void on_swap(context_type &, context_type &) const;
        virtual void on_add(context_type &, const context_type &) const;
        virtual void on_subtract(context_type &, const context_type &) const;
        virtual void on_mult(context_type &, const context_type &) const;
        virtual void on_divide(context_type &, const context_type &) const;
        virtual void on_remainder(context_type &, const context_type &) const;
        virtual void on_inc(context_type &) const;
        virtual void on_dec(context_type &) const;
        virtual void on_invert(context_type &) const;
    };

}   // om636
    
#include "dummy.hxx"

#endif // _dummy_H_8900700	