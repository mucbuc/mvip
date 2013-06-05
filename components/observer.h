#ifndef OBSERVER_H__cIuO6MV2doHZDmg8ijr17zB0YCelG3
#define OBSERVER_H__cIuO6MV2doHZDmg8ijr17zB0YCelG3

#include <algorithm>

namespace om636
{

    template<class T>
	struct observer
	{
		// types
		typedef T context_type;

		virtual ~observer();
        virtual void on_swap(const context_type &, const context_type &) = 0;
        virtual void detach(void *) = 0;
	}; 
	    
    template<class T>
    struct value_observer
    : public T
    {
        // types
        typedef T base_type;
        typedef typename base_type::context_type context_type;
        
        virtual ~value_observer();
        virtual bool on_swap(context_type &, context_type &) const;
    };
	    
	    
}	// om636

#include "observer.hxx"
#endif // __OBSERVER_H__cIuO6MV2doHZDmg8ijr17zB0YCelG3