#include <cassert>
#define ASSERT( arg ) assert( arg )

#include <iostream>

#include <mvip/src/presenter.h>
#include <mvip/lib/om636/src/components/context.h>

int main( int argc, char * argv[] )
{
	using namespace std;
	using namespace om636; 
	using namespace om636::mvip; 

	typedef Basic_Presenter< context< int > > presenter_type; 
	presenter_type p; 
	return 0;
}
