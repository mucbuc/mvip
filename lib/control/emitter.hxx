	
	
	
namespace om636
{
    /////////////////////////////////////////////////////////////////////////////////////////////
	// Agent
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    emitter<T, U, V>::Agent::Agent( function_type callback )
    : m_cancel(0)
    , m_callback( callback )
    {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    void emitter<T, U, V>::Agent::cancel()
    {
        m_cancel = 1;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    bool emitter<T, U, V>::Agent::is_canceled()
    {
        return m_cancel;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    auto emitter<T, U, V>::Agent::callback() -> function_type
    {
        return m_callback;
    }
        
    /////////////////////////////////////////////////////////////////////////////////////////////
	// Listener
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    emitter<T, U, V>::Listener::Listener( Agent & agent )
    : m_agent( agent )
    {}

    template<class T, class U, template<class> class V>
    emitter<T, U, V>::Listener::~Listener()
    {
        m_agent.cancel();
    }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	// emitter<T>
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    emitter<T, U, V>::emitter()
    : m_traversing( 0 )
    {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    emitter<T, U, V>::~emitter()
    {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    void emitter<T, U, V>::include( batch_type & dst, batch_type & src )
    {
        if (!src.empty())
        {
            dst.insert( src.begin(), src.end() );
            src.clear();
        }
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    void emitter<T, U, V>::process( batch_type & batch )
    {
        for_each( batch.begin(), batch.end(), [](Agent * a){
            if (!a->is_canceled())
                std::cout << "process" << std::endl;
            
            //    a->callback()();
        } );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    void emitter<T, U, V>::emit( event_type e )
    {
        // TODO: lock before check
        if (!m_traversing)
        {
            // TODO: scope_guard
            m_traversing = 1;
            
            event_type current(e);
            do
            {
                batch_type & singles( m_singles[current] );
                include( singles, m_add_singles[current] );
                
                batch_type & repaters( m_repeaters[current] );
                batch_type & to_add( m_add_repeaters[current] );
                include( repaters, to_add );
                
                process( singles );
                process( repaters );
                
                // keep repeaters not canceled
                for_each( repaters.begin(), repaters.end(), [& to_add](Agent * a) {
                    if (!a->is_canceled())
                        to_add.insert( a );
                } );
                repaters.clear();
            }
            while (m_queue.try_pop(current));
            m_traversing = 0;
        }
        else
            m_queue.push( e );
    }
        
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    auto emitter<T, U, V>::on( event_type e, function_type f ) -> Listener *
    {
        Agent * a( new Agent( f ) );
        m_add_repeaters[e].insert( a );
        return new Listener( * a );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    auto emitter<T, U, V>::once( event_type e, function_type f) -> Listener *
    {
        Agent * a( new Agent( f ) );
        m_add_singles[e].insert( a );
        return new Listener( * a );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    void emitter<T, U, V>::remove_all_listeners(event_type)
    {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    void emitter<T, U, V>::remove_all_listeners()
    {}
/*
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    auto emitter<T, U, V>::listeners( event_type ) -> std::vector< Listener >
    {
        return std::vector< Listener >();
    }
  */   
	
}	// om636