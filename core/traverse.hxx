namespace om636
{
    namespace
    {
        /////////////////////////////////////////////////////////////////////////////////////////////
        // traverse_impl 
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int N, int M>
        struct traverse_impl
        {
            template<class T, class U>
            static U apply( T & t, U visitor )
            {
                visitor( std::get< N >(t) );
                return traverse_impl< N + 1, M >::apply( t, visitor );
            }
            
            template<class T, class U>
            static U apply( const T & t, U visitor )
            {
                visitor( std::get< N >(t) );
                return traverse_impl< N + 1, M >::apply( t, visitor );
            }
            
            template<class T, class U>
            static U apply_if( T & t, U visitor )
            {
                if (visitor( std::get< N >(t) ) )
                    return traverse_impl< N + 1, M >::apply( t, visitor );
                return visitor;
            }
            
            template<class T, class U>
            static U apply_if( const T & t, U visitor )
            {
                if (visitor( std::get< N >(t) ) )
                    return traverse_impl< N + 1, M >::apply( t, visitor );
                return visitor;
            }
            
        };
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // traverse_impl< N, N >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int N>
        struct traverse_impl< N, N >
        {
            template<class T, class U>
            static U apply( T & t, U visitor )
            {   return visitor; }
            
            template<class T, class U>
            static U apply( const T & t, U visitor )
            {   return visitor; }
            
            template<class T, class U>
            static U apply_if( T & t, U visitor )
            {   return visitor; }
            
            template<class T, class U>
            static U apply_if( const T & t, U visitor )
            {   return visitor; }
        };

        /////////////////////////////////////////////////////////////////////////////////////////////
        // traverse_combinations_impl
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int N, int M, int L>
        struct traverse_combinations_impl
        {
            template<class T, class U>
            static U apply( T & t, U visitor )
            {
                visitor( std::get< N >(t), std::get< M >(t) );
                return traverse_combinations_impl< N, M + 1, L >::apply( t, visitor );
            }
            
            template<class T, class U>
            static U apply( const T & t, U visitor )
            {
                visitor( std::get< N >(t), std::get< M >(t) );
                return traverse_combinations_impl< N, M + 1, L >::apply( t, visitor );
            }
        
            template<class T, class U>
            static U apply_if( T & t, U visitor )
            {
                if (visitor( std::get< N >(t), std::get< M >(t) ) )
                    return traverse_combinations_impl< N, M + 1, L >::apply_if( t, visitor );
                return visitor; 
            }
            
            template<class T, class U>
            static U apply_if( const T & t, U visitor )
            {
                if (visitor( std::get< N >(t), std::get< M >(t) ) )
                    return traverse_combinations_impl< N, M + 1, L >::apply_if( t, visitor );
                return visitor;
            }
        };
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // traverse_combinations_impl< N, M, M >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int N, int M>
        struct traverse_combinations_impl< N, M, M >
        {
            template<class T, class U>
            static U apply( T & t, U visitor )
            {
                return traverse_combinations_impl< N + 1, N + 2, M >::apply( t, visitor );
            }
            
            template<class T, class U>
            static U apply( const T & t, U visitor )
            {
                return traverse_combinations_impl< N + 1, N + 2, M >::apply( t, visitor );
            }
            
            template<class T, class U>
            static U apply_if( T & t, U visitor )
            {
                return traverse_combinations_impl< N + 1, N + 2, M >::apply_if( t, visitor );
            }
            
            template<class T, class U>
            static U apply_if( const T & t, U visitor )
            {
                return traverse_combinations_impl< N + 1, N + 2, M >::apply_if( t, visitor );
            }
        };
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // traverse_combinations_impl< N, M, N >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int N, int M >
        struct traverse_combinations_impl< N, M, N >
        {
            template<class T, class U>
            static U apply( T & t, U visitor )
            {   return visitor; }
            
            template<class T, class U>
            static U apply( const T & t, U visitor )
            {   return visitor; }
            
            template<class T, class U>
            static U apply_if( T & t, U visitor )
            {   return visitor; }
            
            template<class T, class U>
            static U apply_if( const T & t, U visitor )
            {   return visitor; }
        };
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // reduce_impl< N, M, R >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int N, int M, class R>
        struct reduce_impl
        {
            template<class T, class U>
            static std::tuple<R, U> apply( T & t, U visitor )
            {
                using namespace std;
                
                const tuple<R, U> & recursion( reduce_impl<N+1, M, R>::apply( t, visitor ) );
                visitor = get<1>(recursion);
                const R & result_value( visitor( get<N-2>(t), get<0>(recursion) ) );
                return make_tuple( result_value, visitor );
            }
        };
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // reduce_impl< N, N, R >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int N, class R>
        struct reduce_impl<N, N, R>
        {
            template<class T, class U>
            static std::tuple<R, U> apply( T & t, U visitor )
            {
                using namespace std;
                const R & value( visitor( get<N - 2>(t), get<N - 1>(t) ) );
                return make_tuple( value, visitor );
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////////////
        // reduce_impl< 0, 1, R >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class R>
        struct reduce_impl<2, 1, R>
        {
            template<class T, class U>
            static std::tuple<R, U> apply( T & t, U visitor )
            {
                using namespace std;
                const R & value( visitor( std::get<0>(t) ) );
                return std::make_tuple( value, visitor );
            }
        };
    }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U traverse(T & t, U visitor)
    {   return traverse_impl< 0, std::tuple_size<T>::value >::apply( t, visitor ); }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U> U traverse(const T & t, U visitor)
    {   return traverse_impl< 0, std::tuple_size<T>::value >::apply( t, visitor );  }
	
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U traverse_if(T & t, U visitor)
    {   return traverse_impl< 0, std::tuple_size<T>::value >::apply_if( t, visitor ); }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U traverse_if(const T & t, U visitor)
    {   return traverse_impl< 0, std::tuple_size<T>::value >::apply_if( t, visitor );  }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U traverse_combinations(T & t, U visitor)
    {   return traverse_combinations_impl< 0, 1, std::tuple_size<T>::value >::apply( t, visitor ); }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U traverse_combinations(const T & t, U visitor)
    {   return traverse_combinations_impl< 0, 1, std::tuple_size<T>::value >::apply( t, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U traverse_combinations_if(T & t, U visitor)
    {   return traverse_combinations_impl< 0, 1, std::tuple_size<T>::value >::apply_if( t, visitor ); }
	
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U traverse_combinations_if(const T & t, U visitor)
    {   return traverse_combinations_impl< 0, 1, std::tuple_size<T>::value >::apply_if( t, visitor ); }
    
#if 0
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U reduce(T & t, U visitor)
    {   return reduce_impl< 0, std::tuple_size<T>::value >::apply( t, visitor ); }
	
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U reduce(const T & t, U visitor)
    {   return reduce_impl< 0, std::tuple_size<T>::value >::apply( t, visitor ); }
#else 
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V> std::tuple<T, V> reduce(U & t, V visitor)
    {   return reduce_impl< 2, std::tuple_size<U>::value, T >::apply( t, visitor );    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V> std::tuple<T, V> reduce(const U & t, V visitor)
    {   return reduce_impl< 2, std::tuple_size<U>::value, T >::apply( t, visitor );    }
#endif
    
} // om636