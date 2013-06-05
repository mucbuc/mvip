namespace om636
{
    
#pragma mark -
#pragma mark record
#pragma mark -
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	// record< T, U >
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, template<class> class U>
	void record< T, U >::append( node * n )
    {
        std::lock_guard< mutex_type > lock( m_mutex );
        n->next() = std::move( m_head );
        m_head.reset( n );
    }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, template<class> class U> 
	void record< T, U >::append( const value_type & v )
	{
		append( new single_node( v ) );
    }
		
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, template<class> class U> 
	template<class I> 
	void record< T, U >::append( I i, I e )
	{
        append( new block_node( i, e ) );
	}
		
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, template<class> class U>
	void record< T, U >::traverse( visitor_type visitor, std::function< void() > done ) const
	{
		traverse( visitor );
        done();
	}
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, template<class> class U>
	void record< T, U >::traverse( visitor_type visitor ) const 
	{
		if (m_head)
        {
            fbp::on_head_pass( * this );
            m_head->traverse( visitor );
		}
    }
    
#pragma mark -
#pragma mark non members
#pragma mark -
    
  	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class S, class T, template<class> class U>
    S & operator>>( S & s, record< T, U > & record )
    {
        typedef T value_type;
        
        value_type temp;
        std::vector< value_type > init;
        while (s && s >> temp)
            init.push_back( temp );
        record.append( init.begin(), init.end() );
        return s;
    }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class S, class T, template<class> class U>
    S & operator<<( S & s, const record< T, U > & record )
    {
        typedef T value_type;
    
        using namespace std;
        record.traverse( [&]( const value_type & i ) {
            s << i << std::endl;
        } );
        
        return s; 
    }
}
