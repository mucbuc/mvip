
#include <om636/lib/core/assert.h> 
#include <om636/lib/mvc/controller.h>
#include <om636/lib/mvc/model.h>
#include <om636/lib/mvc/view.h>
#include <om636/lib/control/emitter.h>
#include <functional>

template<typename T>
struct view_impl : basic_view< T > 
{
	typedef basic_view< T > base_type;
	using typename base_type::controller_type;
	using typename base_type::listener_type;
    
	using base_type::m_listeners;
    

	view_impl( controller_type & c ) 
	: base_type( c )
	{
		auto listener( c.on( 4, [](){
			std::cout << "got 4" << std::endl;
		}) );

		m_listeners.push_back( listener_type( listener ) );
	}

	~view_impl() = default;
};

int main()
{	
	typedef emit_controller< int > controller_type;
	typedef view< controller_type > view_type;
    
    
	controller_type impl;
	view_impl< controller_type > v( impl );
	impl.emit( 4 );

	return 0;
}

