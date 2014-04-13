#include <iostream>

#include <mvip/src/presenter.h>
#include <mvip/src/view.h>
#include <mvip/lib/om636/src/components/context.h>

#include "debug.h"

template<class T>
struct Test_View
: om636::mvip::Basic_View< T > 
{
	typedef om636::mvip::Basic_View< T > base_type;
	using typename base_type::context_type;
	virtual ~Test_View() = default;
	Test_View()  {}
	void on_swap( const context_type & c, const context_type & )
	{}
};

template<class T> 
struct Test_Presenter
: om636::mvip::Basic_Presenter< T >
{
	typedef om636::mvip::Basic_Presenter< T > base_type;
	using typename base_type::observer_type;
	using base_type::m_observers;

	Test_Presenter() 
	: m_passed( false )
	{}

	virtual ~Test_Presenter() 
	{
		ASSERT( m_passed );
	}

	void test() 
	{
	}

	void pass() const
	{
		m_passed = true; 
	}

private:

	mutable bool m_passed;
};

int main( int argc, char * argv[] )
{
	using namespace std;
	using namespace om636; 
	using namespace om636::mvip; 

	typedef Test_Presenter< context< int > > presenter_type; 
	presenter_type p;
		
	typedef Test_View< context< int > > view_type; 
	view_type v;
	p.attach( & v );

	p.test();

	return 0;
}
