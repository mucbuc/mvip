#ifdef __HEADER_TRANSLATION_UNIT__

//#include "parser_fwd.h"
//#include "parser.h"

#include <iostream>
#include <fstream>
#include "mathfwd.h"
#include "singleton.h"
//#include "statement_state.h"

namespace toolbag
{
	template<class T>
	struct create_unit
	{
		typedef typename T::value_type value_type;
		typedef typename T::factory_type factory_type;
		
		/////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////
		static factory_type * create()
		{
			factory_type * temp( new factory_type );
			private_geometry::factory<value_type>::register_( *temp );
			return temp;	
		}

		/////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////
		static void destroy(factory_type * d)
		{	delete d;	}
	};		

	/////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	const typename geometry_factory<T>::factory_type & geometry_factory<T>::instance()
	{
		typedef om636::singleton < factory_type, om636::default_lifetime<factory_type>, create_unit<geometry_factory> > factory_singleton_type;
		
		return factory_singleton_type::instance();
	}

} // toolbag

#endif 
