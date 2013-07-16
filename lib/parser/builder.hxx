/*
	todo:
		get_constant 
`		get_variable, 	
*/

namespace om636
{
    
#pragma mark -
#pragma mark builder
#pragma mark -
    
	/////////////////////////////////////////////////////////////////////////////////////////////
    // builder<T>
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
	builder<T>::builder()
    : m_operator()
    , m_name()
    , m_result()
    , m_value()
    {}
    
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
	builder<T>::builder(const builder & c)
    : m_operator( c.m_operator )
    , m_name( c.m_name.begin(), c.m_name.end() )
    , m_result( c.m_result )
    , m_value()
	{}
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	builder<T> & builder<T>::operator=(builder c)
	{
		swap( c );
		return *this;
	}
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void builder<T>::swap(builder & c)
	{
		using std::swap;
		swap( m_operator, c.m_operator );
		swap( m_name, c.m_name );
		swap( m_result, c.m_result );
	}
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	template<class U>
	U builder<T>::build(U & i, U e)
	{
		using namespace om636;
       
     	while (i != e)
		{
			builder rhs;
			if ( get_precedence( m_operator ) < get_precedence( rhs.build_first_operator( i, e ) ) )
                i = rhs.build(i, e);
            
            if (m_name.empty() && rhs.m_name.empty())
                get_operator( m_operator )( m_result(), rhs.m_result() );
            else
			{
                m_result = std::bind( get_operator( m_operator ), m_result(), rhs.m_result() );

				if (!rhs.m_name.empty())
					m_name.insert( m_name.end(), rhs.m_name.begin(), rhs.m_name.end() ); 
			}
						
			if (i != e)
            	m_operator = rhs.m_operator;
        }
		return i;
	}	
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    template<class U> 
    const typename builder<T>::weighted_type & builder<T>::build_first_operator( U & i, U e )
    {
        ASSERT(i != e);
        
        i = build_leaf( i, e );
        if (i != e)
            build_weighted_op( (i++)->name()[0] );
    
        return m_operator;
    }
                
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    const typename builder<T>::value_type & builder<T>::result()
    {
        return m_result();
    }

	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    typename builder<T>::operator_type & builder<T>::get_operator( weighted_type & w )
    {
        return std::get<0>( w );
    }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    unsigned & builder<T>::get_precedence( weighted_type & w )
    {
        return std::get<1>( w );
    }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    unsigned builder<T>::get_precedence( const weighted_type & w )
    {
        return std::get<1>( w );
    }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void builder<T>::build_weighted_op(char c)
	{
		using namespace std;
		
		enum { 	add = '+',
            sub = '-',
            mult = '*',
            divide = '/',
            power = '^',
            terminate = ';',
            _assign = '=',
            comma = ',',
		};
        
		switch (c)
		{
			case add:
				get_operator( m_operator ) = sum();
                get_precedence( m_operator ) = 1;
				break;
			case sub:
				get_operator( m_operator ) = difference();
				get_precedence( m_operator ) = 1;
				break;
			case mult:
				get_operator( m_operator ) = product();
				get_precedence( m_operator ) = 2;
				break;
			case divide:
				get_operator( m_operator ) = quotient();
				get_precedence( m_operator ) = 2;
				break;
			case power:
				get_operator( m_operator ) = sum();
				get_precedence( m_operator ) = 3;
				break;
			case _assign:
			case terminate:
			default:
				// get_operator( m_operator ) = error();
				ASSERT( !"parse error" );
                
                get_precedence( m_operator ) = 0;
		}
    }
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	template<class U>
	U builder<T>::build_leaf(U i, U e)
	{
		ASSERT( i != e );
		
		bool negate( false );
		
		if (i->type() == token_type::_operator)
		{
			ASSERT( i->name()[0] == '-' );
            
			negate = true;
			++i;
            
			ASSERT( i != e );
		}
        
		switch (i->type())
		{
            case token_type::number:
			{
				i->to_value(m_value);
                m_result = [&]()->value_type & { return m_value; };
                break;
			}
#if 0
            case token_type::variable:
			{
				typedef typename variable_functor<value_type>::map_type map_type;
				
				// handle negate
				const std::string & name( i->name() );
				map_type & map( variable_functor<value_type>::table() );
				
				if (map.find( name ) == map.end())
				{
					m_result = variable_functor<value_type>( name );
					m_name.push_back( name );
				}
				else
					m_result = value_functor<value_type>( negate ? -map[name] : map[name] );
				break;
			}
#endif 		
            default:
                break;
        }
        
		return ++i; 
	}

#pragma mark -
#pragma mark non members
#pragma mark -
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void swap(builder<T> & lhs, builder<T> & rhs)
	{	lhs.swap( rhs );	}
    
}	// om636
