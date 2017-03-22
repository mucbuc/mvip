namespace om636
{
    /////////////////////////////////////////////////////////////////////////////////////////////
    // dynamic
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    dynamic<T>::dynamic( context_type & c )
        : m_context( & c )
    {   
        context()->attach( * this );    
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    dynamic<T>::dynamic(const dynamic & _c)
        : m_context( _c.m_context )
    {   
        if (context_type * c = context())
            c->attach( * this ); 
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    dynamic<T>::~dynamic()
    {   
        if (context_type * c = context())
            c->detach( * this );        
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    auto dynamic<T>::context() const -> context_type * 
    {   
        return m_context;   
    }   

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T> 
    void dynamic<T>::detach()
    {   
        m_context = nullptr;    
    }   
}   // om636