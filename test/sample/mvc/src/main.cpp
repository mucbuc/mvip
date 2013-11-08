
#include <om636/lib/core/assert.h> 
#include <om636/lib/mvc/controller.h>
#include <om636/lib/mvc/model.h>
#include <om636/lib/mvc/view.h>
#include <om636/lib/control/emitter.h>

#include <functional>

//#include 

template<typename T> 
struct controller_impl : controller< T > 
{
	typedef controller< T > base_type;
	typedef om636::emitter< int, std::function<void()> > emitter_type;
	using typename base_type::view_type;

	emitter_type m_emitter;
}; 

template<typename T>
struct view_impl : view< T > 
{
	typedef view< T > base_type;
	using typename base_type::controller_type;

	view_impl( controller_type & c ) 
	{
		auto listener( c.m_emitter.on( 4, [](){
			std::cout << "got 4" << std::endl;
		}) );

		m_listeners.push_back( listener );
	}

	~view_impl() 
	{}

	std::vector< typename controller_type::emitter_type::object_type * > m_listeners; 
};

int main() 
{	
	typedef controller_impl< int > controller_type;
	typedef view< controller_type > view_type;

	controller_type impl;
	view_impl< controller_type > v( impl );

	impl.m_emitter.emit( 4 );

	return 0;
}