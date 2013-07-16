#ifndef SERVING_H__zZ435R9CerfksUNnSiBuYP0E1vTxJ6
#define SERVING_H__zZ435R9CerfksUNnSiBuYP0E1vTxJ6

#include <om636/components/componentsfwd.h>
#include <om636/components/context.h>
#include <om636/lambda/lambda_fwd.h>
#include <vector>

namespace om636
{
	template<class T>
	struct serving_layer
    : basic_subject< T >
	{
        typedef T context_type;
        typedef basic_subject< context_type > base_type;
        
        typedef typename default_subject::traits<context_type>::value_type * value_type;   // this is what i want stored in the context
        
        typedef batch_view< context_type > view_type;
    
        template<class V>
        static value_type on_init(V &)
        {
            return 0;
        }

        template<class V>
        static value_type on_init(V &, value_type i)
        {
            return i;
        }
        
        virtual void process( const value_type & );
    };

    template<class T>
    struct batch_view
    : observer< T >
    {
        typedef T context_type;
        typedef observer< context_type > base_type;
        
        template<class U> batch_view( U & );
        virtual ~batch_view();
        
    private:
        
        std::function< void() > m_detach;
    };
}

#include "serving.hxx"
#endif // __SERVING_H__zZ435R9CerfksUNnSiBuYP0E1vTxJ6