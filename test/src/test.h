#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>

#include <lib/context/src/interface.h>
#include <lib/context/src/forward_policy.h>
#include "base.h"

namespace
{
	template<class T>
	void run_math_test()
	{
		using namespace std;
		using namespace om636;
		
		typedef context< int, forward_policy > number_type;
        tools::tester< number_type >::test_number();
        FOOTER;
    }

    template<class T> 
    void run_io_test()
    {
		using namespace std;
		using namespace om636;
		
		typedef context< int, forward_policy > number_type;
		number_type a(0);
		ASSERT( a == 0 );
        stringstream( "1" ) >> a; 
        ASSERT( a == 1 );
        FOOTER;
    }
}
