namespace om636
{
    static om636::index<0> _key;
	static om636::index<1> _fill;
    	
	/////////////////////////////////////////////////////////////////////////////////////////////
    // compressive<T>
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	compressive<T>::compressive()
		: context_type( 0 ) 
	{}
		
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	compressive<T>::compressive(const compressive & c)
		: context_type( dynamic_cast<const context_type &>(c) )
	{}	
	
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	compressive<T>::compressive(const context_type & c)
		: context_type( c )
	{}	

    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	compressive<T>::~compressive()
	{}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	compressive<T> & compressive<T>::operator=(compressive a)
	{	
		swap(a);	
		return *this;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	template<class U, class V>
	U compressive<T>::assign(const V & v)
	{	
        using namespace std;
        
        U result; 
        V pf( om636::find_hypersum( v, result[_fill] ) );  
        
        return U( value_type( v - pf , result[ _fill ] ) );	
    }

	/////////////////////////////////////////////////////////////////////////////////////////////
    // accumulator 
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T> 
    struct accumulator
    {
        accumulator( size_t key )
            : m_result( key )
            , m_dimension( 0 ) 
        {
            std::cout << key; 
        }
      
        void operator()(T n)
        {
            std::cout << ", " << n;
            
            while(n)
                m_result += om636::binary_hyperdelta( m_dimension, n-- ); 
            ++m_dimension; 
        }
        
        T result() const 
        {
            return m_result; 
        }
        
    private:
        T m_result; 
        T m_dimension;  
    }; 
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	template<class U, class V>
	U compressive<T>::to_value(const V & _m)
	{
        return for_each( _m[ _fill ].begin(), _m[ _fill ].end(), accumulator< U >( _m[ _key ] ) ).result();
    }

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	bool compressive<T>::equal(const num_type & lhs, const num_type & rhs) const
	{	return false; }

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	int compressive<T>::cmp(const num_type & lhs, const num_type & rhs) const
	{	return 0; }

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	int compressive<T>::sign(const num_type & n) const 
	{	return 0; }

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void compressive<T>::add(num_type &, const num_type &) const
	{}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void compressive<T>::subtract(num_type &, const num_type &) const
	{}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void compressive<T>::mult(num_type &, const num_type &) const
	{}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void compressive<T>::divide(num_type &, const num_type &) const
	{}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void compressive<T>::remainder(num_type &, const num_type &) const
	{}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U>
	T & operator>>(T & s, number< compressive< U > > & n)
	{ 	return s;	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U>
	T & operator<<(T & s, const number< compressive< U > > & n)
	{ 	return s; } 

}   // om636

