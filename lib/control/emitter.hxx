	
	
	
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
                a->callback()();
        } );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    template<class W>
    void emitter<T, U, V>::process( batch_type & batch, W w )
    {
        for_each( batch.begin(), batch.end(), [&](Agent * a){
            if (!a->is_canceled())
                a->callback()(w);
        } );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    void emitter<T, U, V>::pop_events( std::function<void()> f )
    {
        std::unique_lock<mutex_type> lock( m_mutex, std::try_to_lock );
        if (lock.owns_lock())
            do
                f();
            while (m_queue.try_pop(f));
        else
            m_queue.push( f );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    void emitter<T, U, V>::emit( event_type e )
    {
        std::function< void() > p = [&]() {
            using std::swap;
            
            batch_type singles;
            swap( singles, m_singles[e] );
            
            batch_type repeaters;
            batch_type & to_add( m_repeaters[e] );
            swap( repeaters, to_add );
            
            process( singles );
            process( repeaters );
            
            // keep repeaters not canceled
            for_each( repeaters.begin(), repeaters.end(), [& to_add](Agent * a) {
                if (!a->is_canceled())
                    to_add.insert( a );
            } );
        };
        
        pop_events( p );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    template< typename W >
    void emitter<T, U, V>::emit( event_type e, W w )
    {
        std::function< void() > p = [&]() {
            using std::swap;
            
            batch_type singles;
            swap( singles, m_singles[e] );
            
            batch_type repeaters;
            batch_type & to_add( m_repeaters[e] );
            swap( repeaters, to_add );
            
            process( singles, w );
            process( repeaters, w );
            
            // keep repeaters not canceled
            for_each( repeaters.begin(), repeaters.end(), [& to_add](Agent * a) {
                if (!a->is_canceled())
                    to_add.insert( a );
            } );
        };
        
        pop_events( p );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    auto emitter<T, U, V>::on( event_type e, function_type f ) -> Listener *
    {
        Agent * a( new Agent( f ) );
        m_repeaters[e].insert( a );
        return new Listener( * a );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    auto emitter<T, U, V>::once( event_type e, function_type f) -> Listener *
    {
        Agent * a( new Agent( f ) );
        m_singles[e].insert( a );
        return new Listener( * a );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    void emitter<T, U, V>::remove_all( batch_type & batch )
    {
        for_each( batch.begin(), batch.end(), [](Agent * a){
            a->cancel();
        } );
        batch.clear();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    void emitter<T, U, V>::remove_all( map_type & m )
    {
        for_each( m.begin(), m.end(), [](typename map_type::value_type & v) {
            remove_all( v.second );
        } );
        m.clear();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    void emitter<T, U, V>::remove_all_listeners(event_type e)
    {
        remove_all( m_singles[e] );
        remove_all( m_repeaters[e] );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    void emitter<T, U, V>::remove_all_listeners()
    {
        remove_all( m_singles );
        remove_all( m_repeaters );
    }
	
}	// om636