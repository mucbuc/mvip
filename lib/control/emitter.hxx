	
	
	
namespace om636
{
	/////////////////////////////////////////////////////////////////////////////////////////////
	// emitter<T>
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U> 
	emitter<T, U>::emitter()
	//: m_listeners()
	: m_batches()
	{}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U> 
	emitter<T, U>::~emitter()
	{
#if 0
        for_each( m_listeners.begin(), m_listeners.end(), [](typename map_type::value_type & f)
        {
            for_each( f.second.begin(), f.second.end(), [](typename id_map_type::value_type & i)
            {
                i.first->detach();
            } );
        } );
#endif 
    }
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U> 
	void emitter<T, U>::emit( event_type e )
	{
		auto batches = m_batches[ e ];
		batches.first.invoke();
		batches.second.invoke();
		
#if 0
        const id_map_type & range( m_listeners[ e ] );
        std::for_each( range.begin(), range.end(), [](typename id_map_type::value_type g)
        {
            g.second();
        } );
#endif
    }
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U>
 	typename emitter<T, U>::key_type emitter<T, U>::on( event_type e, U f )
	{
#if 0
		listener * result( new listener( * this ) );
		m_listeners[ e ][ result ] = f;
        return result;
#else 
        
        return 0; 
#endif
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U>
    void emitter<T, U>::remove( key_type key )
    {
#if 0
        for_each( m_listeners.begin(), m_listeners.end(), [=](typename map_type::value_type & f)
        {
            if (f.second.erase( key ))
                return;
        } ); 
#endif 
    }


    #if 0
    	/////////////////////////////////////////////////////////////////////////////////////////////
	// emitter<T, U>::listener
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U> 
	struct emitter<T, U>::listener
	{
    	listener( emitter & e )
		: m_emitter( & e )
		{}
		
        void detach()
        {
            m_emitter = 0;
        }
    
		~listener()
		{
            if (m_emitter)
                m_emitter->remove( this );
        }
	
    private:
		emitter * m_emitter;
	}; 
	
#endif 
    
	
}	// om636