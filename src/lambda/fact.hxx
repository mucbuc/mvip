namespace om636
{
    /////////////////////////////////////////////////////////////////////////////////////////////
    // fact<T, U, V>
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename U, typename V>
    fact<T, U, V>::fact()
    : m_time()
    , m_id()
    , m_data()
    {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename U, typename V>
    fact<T, U, V>::~fact()
    {}

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename U, typename V>
    auto fact<T, U, V>::time() const -> const time_type &
    {
        return m_time;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename U, typename V>
    auto fact<T, U, V>::time() -> time_type &
    {
        return m_time;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename U, typename V>
    auto fact<T, U, V>::id() const -> const id_type &
    {
        return m_id;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename U, typename V>
    auto fact<T, U, V>::id() -> id_type &
    {
        return m_id;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename U, typename V>
    auto fact<T, U, V>::data() const -> const data_type &
    {
        return m_data;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename U, typename V>
    auto fact<T, U, V>::data() -> data_type &
    {
        return m_data;
    }
    
    template<typename T, typename U, typename V>
    bool fact<T, U, V>::operator<(const fact & f) const
    {
        return  time() < f.time()
            ||  (time() == f.time() && id() < f.id());
    }
    
// non members
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<typename S, typename T, typename U, typename V>
	S & operator>>(S & s, fact< T, U, V > & f)
    {   
        using namespace std;

        s >> f.time();
        s >> f.id();
        s >> f.data();
        
        return s;
    }
	
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<typename S, typename T, typename U, typename V>
	S & operator<<(S & s, const fact< T, U, V > & f)
    {
        s << f.time() << ' ' << f.id() << ' ' << f.data() << std::endl;
        return s;
    }
    
}   // om636 