#include <cassert>
#define ASSERT( pred ) assert( pred )

#include <om636/src/parser/token.h>
#include <om636/src/parser/lexer.h>
#include <string>
#include <iostream>
#include <sstream>
#include <string>

void checkTerminator()
{
 	using namespace om636; 
	using namespace std;
	
	typedef token< string > token_type; 
	typedef lexer< token_type, stringstream > lexer_type;

	stringstream s;
	s << ";";
	lexer_type t( s ); 

    auto type( t.current().type() );
	ASSERT( type == token_type::terminator );

	cout << "checkTerminator passed " << endl;
}
