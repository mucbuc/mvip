namespace om636
{
#if 0 
	/////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class I, class O>
	O convergent( I b, I e, O out )
		{
		typename I::value_type p0, q0, p1, q1;
		
		p0 = *b++;
		q0 = 1;
		*(out++) = rational<I::value_type>( p0 );
		
		p1 = p0 * *b + 1;
		q1 = *b++;
		*(out++) = rational<I::value_type>( p1, q1 );
		
		while( b != e )
			{
			I::value_type pk, qk;
			pk = *b * p1 + p0;
			qk = *b * q1 + q0;
			*(out++) = rational<I::value_type>( pk, qk );
			p0 = p1;
			q0 = q1;
			p1 = pk;
			q1 = qk;
			b++;
			}		
		return out;
		}
		
	/////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T> 
	T mod_inverse(const T& n, const T& mod)
	{	
		vector< T > partials;
		vector< rational< T > > convergents;
		
		euclidian( mod, n, back_inserter( partials ) );
		convergent( partials.begin(), partials.end(), back_inserter( convergents ) );
		convergents.pop_back();
		if( convergents.size() & 1 )
			return mod - numerator( convergents.back() );
		return numerator( convergents.back() );
	}
#endif 	
    
	/////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	T power_factorial(T n)
	{
		T result( 0 ); 
		while (--n)
			result += std::pow( 2, double( n ) ) * n;           //<= not so good
		return result; 
	}

	/////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	T find_power_factorial(T n)
	{
		T pf; 
		return find_power_factorial(n, pf);
	}
		
	/////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	T find_power_factorial( T n, T & pf )
	{		 
		double result( 0 );             // <= not so good
		using std::pow; 
        
		T next( std::pow( 2.0, result ) * result );
		while (next < n)
		{
			pf = next;
			++result;
			next += pow( 2.0, result ) * result;
		}
		return result;
	}
	    
    /////////////////////////////////////////////////////////////////////////////////////////////
    
    /////////////////////////////////////////////////////////////////////////////////////////////        
    template<class T> 
    T factorial( const T & n )
    {
        T result( 1 ); 
        for (T i( 1 ); i <= n; ++i)
            result *= i; 
        return result; 
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    T binomal_coefficient( T n, const T & r )
    {
        if (!n || !r || n == r)
            return 1; 
        --n;
        return binomal_coefficient( n, r ) + binomal_coefficient( n, r - 1 ); 
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T> 
    T binary_hyperdelta(const T & m, const T & n)
    {
        T sum( m + n ); 
        return binomal_coefficient( sum, m + 1 ) << sum;
    }   
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U> 
    T find_hypersum( const T & n, U & result )
    {        
        T dimension( 0 ); 
        T value( 0 ); 
        T next( 0 );
        
        while (next < n)
        {
            next = value; 
            T recursion( 0 ); 
            
            while (next < n)
            {
                value = next;
                next += binary_hyperdelta( dimension, ++recursion );
                
                if (next == n)
                {
                    result.push_back( recursion );
                    return next;  
                }
            }
            
            result.push_back( recursion - 1 );
            next = value; 
            next += binary_hyperdelta( ++dimension, T(1) );
        }
        return value;
    }
    
	namespace 
	{

		/////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////
		template<class T>
		std::valarray<T> natural_series(T n)
		{	std::valarray<T> r(n);
			for(T i(0); i < n; i++) 
				r[i] = T(i);
			return r;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////
		double length(const std::valarray<double>& v)
		{ 	return sqrt( pow(v, 2.0 ).sum() ); 	}

		/////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////
		std::valarray<double> unit(const std::valarray<double>& v)
		{	return v / length(v);	}

		/////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////
		double skalar_product(const std::valarray<double>& v, const std::valarray<double>& w) 
		{ 	return (v * w).sum(); 	}

		/////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////
		std::valarray<double> cross_product(const std::valarray<double>& v, const std::valarray<double>& w) 
		{ 	return v.cshift(1) * w.cshift(2) - v.cshift(2) * w.cshift(1); 	}

		/////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////
		std::valarray<double> identity(unsigned n)
		{	std::valarray<double> r(0.0, n * n);
			r[ std::slice(0, n, n + 1) ] = 1.0;
			return r;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////
		std::valarray<double> orthogonal_vector(unsigned n, unsigned m)
		{	std::valarray<double> r(0.0, n);
			r[m] = 1.0;
			return r;
		}
			
		/////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////
		std::valarray<double> rotate(const std::valarray<double>& axis, double x, const std::valarray<double>& v)
		{
			std::valarray<double> unit_axis( unit(axis) );
			if( fabs( skalar_product(v, unit_axis) ) != length(v) ) 
			{
				std::valarray<double> center, _x, _y;
				center = axis * skalar_product(unit_axis, v);
				_x = v - center;
				_y = cross_product(_x, unit_axis);
				_y *= length(_x) / length(_y);
				return _x * cos(x) + _y * sin(x) + center;
			}
			return v;			
		}	
        
	}	// private 
}// om636 
