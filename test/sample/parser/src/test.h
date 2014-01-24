
#include <om636/src/core/core.h>
#include <om636/src/parser/parser.h>
#include <om636/src/parser/token.h>
#include <om636/src/components/context.h>
#include <om636/src/components/subject.h>
#include <om636/src/parser/parserfwd.h>
#include <om636/src/parser/builder.h>
#include <om636/src/parser/lexer.h>
#include <om636/src/parser/policies.h>
#include <om636/src/parser/token.h>

#include <sstream>

namespace
{
    typedef om636::token<> token_type;
    
    template<class T>
    using parser_policy = om636::parser_policies::push_policy< T, token_type >;
    
    template<class T>
    T check_arithmetic(const char * exp)
    {
        using namespace std;
        using namespace om636;
        
        //typedef variable_functor<number_type> variable_type;
        //variable_type::table()[ "a" ] = 7;
        
        using namespace std;
        using namespace om636;
        
        typedef std::vector< token_type > container_type;
        typedef context< container_type, parser_policy > context_type;
        context_type _context;
        
        stringstream command;
		command << exp;
		
        typedef lexer< token_type, std::istream > lexer_type;
        parser< context_type, lexer_type > a( command, _context );
        a.interpret();
        
        auto i( context_type::tokens( _context ).begin() );
        auto e( context_type::tokens( _context ).end() );
        
        typedef float number_type;
        builder< number_type > b;
        b.build_first_operator( i, e );
        b.build(  i, e );
        return b.result();
    }

    template<class T>
    void run_calculator_test()
    {
        ASSERT( check_arithmetic<float>( "1+3;" ) == 4 );
        ASSERT( check_arithmetic<float>( "4*3;" ) == 12 );
        ASSERT( check_arithmetic<float>( "4*3+1;" ) == 13 );
        ASSERT( check_arithmetic<float>( "1+4*3;" ) == 13 );
        ASSERT( check_arithmetic<float>( "4+3*1;" ) == 7 );
        ASSERT( check_arithmetic<float>( "1*4+3;" ) == 7 );
        ASSERT( check_arithmetic<float>( "4+3+1*5;" ) == 12 );
        ASSERT( check_arithmetic<float>( "1*4+3*5;" ) == 19 );
        ASSERT( check_arithmetic<float>( "4*3+8*7;" ) == 68 );
        
        std::cout << "calculator test passed" << std::endl;
	}
}