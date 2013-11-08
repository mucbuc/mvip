
#include <om636/lib/core/assert.h> 
#include <om636/lib/mvc/controller.h>
#include <om636/lib/mvc/model.h>
#include <om636/lib/mvc/view.h>

template<typename T> 
struct controller_impl : controller< T > 
{
	typedef controller< T > base_type;
	using typename base_type::view_type;

	void attach( const view_type & ) 
	{

	}
	
	void detach( const view_type & )
	{


	}
}; 

template<typename T>
struct view_impl : view< T > 
{
	typedef view< T > base_type;
	using typename base_type::controller_type;

	view_impl( controller_type & c ) 
	: m_controller( c )
	{
		m_controller.attach( * this );
	}

	~view_impl() 
	{
		m_controller.detach( * this );
	}

	controller_type & controller()
	{
		return m_controller; 
	}

private:
	controller_type & m_controller;
};

int main() 
{	
	typedef controller< int > controller_type;
	typedef view< controller_type > view_type;

	controller_impl< int > impl;

	view_impl< controller_type > v( impl );



	return 0;
}