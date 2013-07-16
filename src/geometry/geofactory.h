#ifndef _factory_H_83k3kjelkjw8i
	#define _factory_H_83k3kjelkjw8i

#include "createfwd.h"
#include "componentsfwd.h"
#include "functorfwd.h"
#include "geometryfwd.h"
#include <string>
#include "object_factory.h"

namespace toolbag
{
	template<class T>
	struct geometry_factory 
	{
		typedef T value_type;
		typedef std::string key_type;
		typedef om636::functor< om636::dynamic_policy< value_type * (*)() > > functor_type;
		typedef om636::object_factory< key_type, functor_type > factory_type;
		
		static const factory_type & instance();
	};

	namespace private_geometry
    
	{	
		template<class>
		struct factory;
	}	//. private_geometry
} // toolbag

#define HEADER_TRANSLATION_UNIT__
#include "geofactory.cpp"
#undef __HEADER_TRANSLATION_UNIT__

#endif // _factory_H_83k3kjelkjw8i