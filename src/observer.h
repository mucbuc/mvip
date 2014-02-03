#ifndef OBSERVER_H__gwKkTNUltSXG8eMjWO9rqVDAHyB5fC
#define OBSERVER_H__gwKkTNUltSXG8eMjWO9rqVDAHyB5fC

namespace om636
{
	namespace mvip
	{
		template<class T>
		struct observer
		{
			// types
			typedef T context_type;
			
			virtual ~observer() = default;
		};
	}	// mvip
}	// om636

#include "observer.hxx"
#endif // OBSERVER_H__gwKkTNUltSXG8eMjWO9rqVDAHyB5fC