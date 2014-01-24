namespace om636
{
	/////////////////////////////////////////////////////////////////////////////////////////////
    // parser<T> 
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U>
    template<class V>
	parser<T, U>::parser(V & u, context_type & w)
    : m_lexer( u )
    , m_context( w )
	{}

	////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U>
	typename parser<T, U>::context_type & parser<T, U>::context() 
	{	return m_context; }
			
	////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U>
	const typename parser<T, U>::context_type & parser<T, U>::context() const 
	{	return m_context; }

	////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U>
	typename parser<T, U>::lexer_type & parser<T, U>::lexer() 
	{	return m_lexer; } 
			
	////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U>
	const typename parser<T, U>::lexer_type & parser<T, U>::lexer() const 
	{	return m_lexer; } 

	////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U>
	typename parser<T, U>::context_type & parser<T, U>::interpret()
	{
		auto t( m_lexer.current() );
        while(t)
        {
            context_type::state(context())->on_token( context(), m_lexer.current() );
            t = m_lexer.next();
        }
        return context();
	}
} 	// om636
