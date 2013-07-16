#ifndef SPEED_H__d80j4xB7cXD3RTLtgGkH2lWAUVvFSi
#define SPEED_H__d80j4xB7cXD3RTLtgGkH2lWAUVvFSi

#include <om636/lambda/lambda_fwd.h>
#include <om636/components/subject.h>
#include <om636/components/observer.h>

namespace om636
{
	template<class T>
	struct speed_layer
    : basic_subject< T >
	{
        typedef T context_type; 
        typedef basic_subject< context_type > base_type;
        typedef real_time_view< context_type > view_type;
        
        typedef typename default_subject::traits< context_type >::value_type value_type;
        
        template<class V>
        static value_type on_init(V & i)
        {
            return value_type();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class V, class W>
        value_type on_init(V & s, const W & init)
        {
            return value_type( init ); 
        }
        
        virtual void clear();        
	};
	
	template<class T>
	struct real_time_view
    : observer< T >
	{
        typedef T context_type;
        typedef observer< context_type > base_type; 
        typedef typename default_subject::traits< context_type >::value_type value_type;
        
        template<class U>
        real_time_view( U & );
        
        virtual ~real_time_view(); 
        
        virtual void insert(value_type);
        virtual void clear();
    private:
        std::function< void() > m_detach;
    };
}

#include "speed.hxx"
#endif // __SPEED_H__d80j4xB7cXD3RTLtgGkH2lWAUVvFSi