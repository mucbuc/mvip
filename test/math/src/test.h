#include <om636/components/context.h>
#include <om636/components/subject.h>
#include <om636/core/tests.h>
#include <om636/math/additive.h>
#include <om636/math/multiplicative.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

namespace
{
    template<class T>
    using additive_type = om636::state_subject< om636::additive::policy< T > >;

    template<class T>
    using multiplicative_type = om636::state_subject< om636::multiplicative::policy< T > >;

	template<class T>
	void run_math_test()
	{
		using namespace std;
		using namespace om636;
		
		typedef context< tuple< unsigned, unsigned >, additive_type > number_type1;
        tools::tester< number_type1 >::test_number();
        
		typedef context< tuple< int, int >, multiplicative_type > number_type2;
		tools::tester< number_type2 >::test_number();

		typedef context< tuple< number_type1, number_type1 >, multiplicative_type > number_type3;
		tools::tester< number_type3 >::test_number();
		
		typedef context< tuple< number_type2, number_type2 >, additive_type > number_type4;
		tools::tester< number_type4 >::test_number();

		cout << "math test passed" << endl;
	}
}
