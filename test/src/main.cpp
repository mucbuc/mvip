#include <iostream>

#include <lib/mvip/src/presenter.h>
#include <lib/mvip/src/view.h>
#include <lib/context/src/interface.h>
#include <lib/sense/src/observer/same_scope.h>

#include "debug.h"

template<class T>
struct Test_View
: om636::mvip::Basic_View< T > 
{
	typedef om636::mvip::Basic_View< T > base_type;
	using typename base_type::context_type;
    
    virtual ~Test_View()
    {
        ASSERT( m_passed );
    }

    Test_View()  {}
	void on_swap( const context_type & c, const context_type & )
	{
	    m_passed = true;
    }
    
private:
    
    mutable bool m_passed = false;
};

template<class T, template<class> class U>
struct Test_Presenter
: om636::mvip::Basic_Presenter< T, U >
{
	typedef om636::mvip::Basic_Presenter< T, U > base_type;
	using typename base_type::observer_type;
    using typename base_type::context_type;
    using base_type::observers;

    Test_Presenter(const Test_Presenter &) = delete;
    Test_Presenter & operator=(const Test_Presenter &) = delete;
    
    Test_Presenter() = default;
    
    virtual ~Test_Presenter() = default;

	void test() 
	{
        context_type tmp;
        base_type::on_swap( tmp, tmp );
    }

};

int main( int argc, char * argv[] )
{
	using namespace std;
	using namespace om636;
	using namespace om636::mvip;

    typedef context< int > context_type;
	typedef Test_Presenter< context_type, const_observer > presenter_type;
	presenter_type p;
		
    typedef Test_View< presenter_type::context_type > view_type;
	view_type v;
    p.attach( v );
    p.test();

	return 0;
}
