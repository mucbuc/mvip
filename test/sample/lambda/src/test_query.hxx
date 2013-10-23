
namespace om636
{
    /////////////////////////////////////////////////////////////////////////////////////////////
    // test_query<T>
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    template<class U>
    test_query<T>::test_query( U & c )
    : base_type( c )
    {}
        
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void test_query<T>::on_swap( const typename base_type::real_time_base::context_type & lhs, const typename base_type::real_time_base::context_type & rhs)
    {
        m_data.insert( rhs.value_ref() );
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void test_query<T>::on_swap( const typename base_type::batch_base::context_type & lhs, const typename base_type::batch_base::context_type & rhs)
    {
        rhs.value_ref()->traverse( [&](const value_type & s){ m_data.insert( s ); } );
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void test_query<T>::print()
    {
        using namespace std;
        for_each( m_data.begin(), m_data.end(), [&](const value_type & s) {
            std::cout << s << std::endl;
        } );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    auto test_query<T>::data() -> data_type &
    {
        return m_data;
    }
    
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    auto test_query<T>::data() const -> const data_type & 
    {
        return m_data;
    }
    
}   // om636 