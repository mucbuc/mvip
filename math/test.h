#include <om636/components/context.h>
#include <om636/math/additive.h>
//#include <math/matrix.h>
//#include <om636/math/multiplicative.h>
#include <om636/math/dummy.h>
#include <om636/components/subject.h>
#include <om636/toolbag/unit_test.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

namespace
{
    template<class T>
    using additive_type = om636::state_subject< om636::additive::policy< T > >;

//    template<class T>
//    using multiplicative_type = om636::state_subject< om636::multiplicative::policy< T > >;

	template<class T>
	void run_test()
	{
		using namespace std;
		using namespace om636;
		
		typedef context< tuple< unsigned, unsigned >, additive_type > number_type1;
        tools::tester< number_type1 >::test_number();
        
//		typedef context< tuple< int, int >, multiplicative_type > number_type2;
//		tools::tester< number_type2 >::test_number();
//		
//		typedef context< tuple< number_type1, number_type1 >, multiplicative_type > number_type3;
//		tools::tester< number_type3 >::test_number();
		
//		typedef context< tuple< number_type2, number_type2 >, additive_type > number_type4;
//		tools::tester< number_type4 >::test_number();
//		
//		typedef context< int, dummy_policy > number_type5;
//		tools::tester< number_type5 >::test_number();
	#if 0
		number_type1 a( 0 );
		int i( a.to_value<int>() );
		number_type2 b( 1 );
		float f( b.to_value<float>() );
		std::cout << i << " " << f << std::endl;
		
	#endif
		
	#if 0
		typedef context< tuple< number_type1, number_type2, number_type3 > > context_type;
		typedef number< matrix< context_type > > array_type;
		array_type a( context_type( make_tuple( 1, 2, 4 ) ) );
		a[ index<0>() ] = 0;
		cout << a << endl;
	#endif
	
		cout << "math test passed" << endl;
	}
}