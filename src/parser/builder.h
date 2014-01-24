/*
    objective: 
        evaluates tokens 
 
    this is very raw (and maybe useles?) and limitied module. 
    - it seems like some states and the getters could be wrapped into a policy
    - 
 
    need to include concept of abstract factory to builder.
    builder< token_type, abstract_factory, result_type >
*/

#ifndef _builder_H_8900700
#define _builder_H_8900700

#include <om636/src/components/componentsfwd.h>
#include <om636/src/components/context.h>
#include <om636/src/math/mathfunctors.h>
#include <om636/src/math/mathutills.h>
#include <om636/src/parser/parserfwd.h>
#include <om636/src/parser/token.h>
#include <functional>
#include <iostream>
#include <tuple>
#include <vector>

namespace om636
{	
    using namespace om636;
    
	template<class T>
	class builder
	{
	public: 	
		typedef T value_type; 
		typedef std::function< value_type & () > leaf_type;
		typedef	std::function< value_type & (value_type &, const value_type &) > operator_type;
        typedef std::tuple< operator_type, unsigned > weighted_type;
		typedef std::vector< std::string > name_container_type;
        typedef token<> token_type; 
		typedef lexer< token_type, std::istream > lexer_type;
        
        builder();
        builder(const builder &); 
		builder & operator=(builder); 
		
		void swap( builder & );
        
		template<class U>
		U build(U &, U);
        
        template<class U>
        const weighted_type & build_first_operator( U &, U);

        const value_type & result();
		
	private:
        
		void build_weighted_op(char);
		template<class U> U build_leaf(U, U);

        static operator_type & get_operator( weighted_type & );
        static unsigned & get_precedence( weighted_type & );
        static unsigned get_precedence( const weighted_type & );
        
        value_type m_value;
		weighted_type m_operator;
		name_container_type m_name;
		leaf_type m_result;
	};

	template<class T>
	void swap( builder<T> &, builder<T> & );

} // om636 

#include "builder.hxx"

#endif // _builder_H_8900700