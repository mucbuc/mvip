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
        // reduce_impl< N, M >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int N, int M>
        struct reduce_impl
        {
            template<class T, class U>
            static U apply( T & t, U visitor )
            {
                visitor( std::get<N>(t) );
                return reduce_impl<N+1, M>::apply( t, visitor );
            }
        };
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // reduce_impl< N, N >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int N>
        struct reduce_impl<N, N>
        {
            template<class T, class U>
            static U apply( T & t, U visitor )
            {   return visitor; }
        };
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // reduce_impl< 0, N >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int N>
        struct reduce_impl<0, N>
        {
            template<class T, class U>
            static U apply( T & t, U visitor )
            {
                visitor( std::get<0>(t), std::get<1>(t) );
                return reduce_impl<2, N>::apply( t, visitor );
            }
        };
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // reduce_impl< 0, 1 >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<>
        struct reduce_impl<0, 1>
        {
            template<class T, class U>
            static U apply( T & t, U visitor )
            {
                visitor( std::get<0>(t) );
                return visitor;
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
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U reduce(T & t, U visitor)
    {   return reduce_impl< 0, std::tuple_size<T>::value >::apply( t, visitor ); }
	
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U reduce(const T & t, U visitor)
    {   return reduce_impl< 0, std::tuple_size<T>::value >::apply( t, visitor ); }
    
} // om636