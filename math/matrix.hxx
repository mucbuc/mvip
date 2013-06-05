
namespace om636
{
	namespace 
	{
		template<class T>
		struct assign_functor
		{
			typedef T value_type; 
			
			assign_functor(const value_type &);
			assign_functor(const assign_functor &);
			assign_functor & operator=(assign_functor);
			void swap(assign_functor);

			template<class U>
			void operator()(U &) const;
			
		private:
			
			// undefined
			assign_functor();
			
			value_type m_value;
		};
	
		template<class T>
		void swap(assign_functor<T> &, assign_functor<T> &);
	}
		
	/////////////////////////////////////////////////////////////////////////////////////////////
    // matrix<T>
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	matrix<T>::matrix()
		: T() 
	{}
		
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	matrix<T>::matrix(const matrix & c)
		: T( c ) 
	{}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	matrix<T>::matrix(const context_type & c) 
		: T( c ) 	
	{}
    
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    matrix<T>:: matrix(const value_type & v)
        : context_type(v)
    {}
    
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class C> 
    template<class T, class U>
    matrix<C>::matrix(const context<T, U> & c)
        : context_type(c)
    {}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	matrix<T>::~matrix()
	{}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	matrix<T> & matrix<T>::operator=(matrix c)
	{	
		swap(c);
		return *this;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class C>
	template<class T, class U>
	T matrix<C>::assign(const U & v)
	{	
		T result;
		traverse( result, assign_functor<U>(v) );
		return result; 
	} 

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class C>
    bool matrix<C>::equal(const num_type & lhs, const num_type & rhs) const
    {	
        return traverse_parallel_if( value_ref(), rhs.value_ref(), equal() ).result();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class C>    
    int matrix<C>::sign(const num_type & lhs, const num_type & rhs) const
    {
        return traverse_parallel_if( value_ref(), rhs.value_ref(), compare() ).result();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class C>    
    int matrix<C>::sign(const num_type &) const
    {
        return traverse_if( value_ref(), compare() ).result();
    }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class C>
	template<class T>
	void matrix<C>::invert(const T & _m)
	{}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class C>
	template<class T, class U, class F>
	F matrix<C>::to_value(const U & _m, F func)
	{
		_m.value_ref()->traverse_units( func );
		return func;
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class C>
	template<class T> 
	void matrix<C>::outer_product(const T & rhs) const
	{	traverse_combinations( value_ref(), rhs, product() ); 	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class C>
	void matrix<C>::add(num_type & lhs, const num_type & _n) const
	{	traverse_parallel( lhs.value_ref(), _n.value_ref(), sum() );  }
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class C>
	void matrix<C>::subtract(num_type & lhs, const num_type & _n) const
	{	traverse_parallel( lhs.value_ref(), _n.value_ref(), difference() );  }
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class C>
	void matrix<C>::mult(num_type & lhs, const num_type & _n) const
	{	traverse_parallel( lhs.value_ref(), _n.value_ref(), product() );  }

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class C>
	void matrix<C>::divide(num_type & lhs, const num_type & _n) const
	{	traverse_parallel( lhs.value_ref(), _n.value_ref(), quotient() );  }

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class C>
	void matrix<C>::remainder(num_type & lhs, const num_type & _n) const
	{	traverse_parallel( lhs.value_ref(), _n.value_ref(), remainder() );  }

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class C>
	template<class T>
	void matrix<C>::power(T & _m, const T & _n)
	{}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class C>
	template<class T, class U>
	T matrix<C>::reduce(U w) 
	{	return std::get<1>( value_ref().template reduce<T>(w) ); 	}

	namespace 
	{	
		template<class T>
		assign_functor<T>::assign_functor(const value_type & v) : m_value( v ) {}
		
		template<class T>
		assign_functor<T>::assign_functor(const assign_functor & v) : m_value(v.m_value) {}
		
		template<class T>
		assign_functor<T> & assign_functor<T>::operator=(assign_functor rhs)
		{
			swap(rhs);
			return *this;
		}
					
		template<class T>
		void assign_functor<T>::swap(assign_functor rhs)
		{
			using std::swap;
			swap(m_value, rhs.m_value); 
		}

		template<class T>
		template<class U>
		void assign_functor<T>::operator()(U & o) const
		{	o = U(m_value);	}
		
		template<class T>
		void swap(assign_functor<T> & lhs, assign_functor<T> & rhs)
		{	lhs.swap(rhs);	}
	
	} // private
}   // om636
	
