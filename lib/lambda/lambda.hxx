namespace om636
{
    /////////////////////////////////////////////////////////////////////////////////////////////
    // lambda<T>
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    void lambda<T, U>::insert( value_type f )
    {
        speed() = f;
    
        fbp::on_speed_insert_done( * this );
        
        batch().insert( f );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    void lambda<T, U>::process()
    {
        batch().process( serving() );
        speed().clear();
    }
   
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    auto lambda<T, U>::batch() -> batch_type &
    {
        return m_batch;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    auto lambda<T, U>::batch() const -> const batch_type & 
    {
        return m_batch;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    auto lambda<T, U>::serving() -> serving_type & 
    {
        return m_serving;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    auto lambda<T, U>::serving() const -> const serving_type &
    {
        return m_serving;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    auto lambda<T, U>::speed()-> speed_type &
    {
        return m_speed;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    auto lambda<T, U>::speed() const-> const speed_type &
    {
        return m_speed;
    }
    
} // om636