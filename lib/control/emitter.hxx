	
	
	
namespace om636
{
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
    void emitter<T, U, V>::emit( event_type )
    {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    auto emitter<T, U, V>::on( event_type, function_type f ) -> Listener *
    {
        Agent * a( new Agent( f ) );
        
        return new Listener( * a );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    auto emitter<T, U, V>::addListener(event_type, function_type) -> Listener
    {
        return Listener();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    auto emitter<T, U, V>::once( event_type, function_type ) -> Listener *
    {
        return Listener();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    void emitter<T, U, V>::removeListener( Listener )
    {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, template<class> class V>
    void emitter<T, U, V>::removeAllListeners()
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