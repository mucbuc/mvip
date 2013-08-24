/* 
 objective: - create/register and destroy/unregister the batch and realtime view
            - compile view (ignore or listen to facts) 
 
 TODO: implement query_base::detach( void * ); 
*/

#ifndef QUERY_H__HNiAPBUXg5IzhQCSlO46yp3fmLWZsY
#define QUERY_H__HNiAPBUXg5IzhQCSlO46yp3fmLWZsY

#include <om636/lib/lambda/lambda_fwd.h>
#include <om636/lib/lambda/batch.h>
#include <om636/lib/lambda/serving.h>
#include <om636/lib/lambda/speed.h>

namespace om636
{
    struct query
    {
        virtual ~query() = default;
    };

    template<class T>
    struct query_base
    : query
    , T::serving_type::view_type
    , T::speed_type::view_type
    {
        typedef T context_type;
        typedef typename context_type::value_type value_type;
        typedef typename context_type::serving_type::view_type batch_base;
        typedef typename context_type::speed_type::view_type real_time_base;
        
        template<class U>
        query_base( U & );
        
        virtual ~query_base() = default; 
        virtual void detach( void * );
    };
}

#include "query.hxx"
#endif // __QUERY_H__HNiAPBUXg5IzhQCSlO46yp3fmLWZsY