namespace om636
{
    namespace
    {
        /////////////////////////////////////////////////////////////////////////////////////////////
        // traverse_impl< M, N, T >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int M, int N, class T>
        struct traverse_impl
        {
            enum { index = M, size = N };
            typedef traverse_impl< index + 1, size, T > permutation;
            
            template<class U>
            static U visit( T t, U visitor )
            {
                visitor( std::get< index >(t) );
                return permutation::visit( t, visitor );
            }
            
            template<class U>
            static U visit_if( T t, U visitor )
            {
                if (visitor( std::get< N >(t) ) )
                    return permutation::visit( t, visitor );
                return visitor;
            }
        };
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // traverse_impl< M, M, T >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int M, class T>
        struct traverse_impl< M, M, T >
        {
            template<class U>
            static U visit( T, U visitor )
            {   return visitor; }
            
            template<class U>
            static U visit_if( T, U visitor )
            {   return visitor; }
        };

        /////////////////////////////////////////////////////////////////////////////////////////////
        // traverse_combinations_impl< M, N, L, T >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int M, int N, int L, class T >
        struct traverse_combinations_impl
        {
            enum { l_index = M, r_index = N, size = L };
            typedef traverse_combinations_impl< l_index, r_index + 1, size, T > permutation;
            
            template<class U>
            static U visit( T t, U visitor )
            {
                using std::get; 
                visitor( get< N >(t), get< M >(t) );
                return permutation::visit( t, visitor );
            }
           
            template<class U>
            static U visit_if( T t, U visitor )
            {
                using std::get;
                if (visitor( get< N >(t), get< M >(t) ) )
                    return permutation::visit_if( t, visitor );
                return visitor; 
            }
        };
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // traverse_combinations_impl< M, N, N, T >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int M, int N, class T>
        struct traverse_combinations_impl< M, N, N, T >
        {
            enum { l_index = M, r_index = N, size = N };
            typedef traverse_combinations_impl< l_index + 1, l_index + 2, size, T > permutation;
            
            template<class U>
            static U visit( T t, U visitor )
            {   return permutation::visit( t, visitor );    }
            
            template<class U>
            static U visit_if( T t, U visitor )
            {   return permutation::visit_if( t, visitor ); }
        };
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // traverse_combinations_impl< M, N, M, T >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int M, int N, class T >
        struct traverse_combinations_impl< M, N, M, T >
        {
            template<class U>
            static U visit( T, U visitor )
            {   return visitor; }
            
            template<class U>
            static U visit_if( T, U visitor )
            {   return visitor; }
        };
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // reduce_impl< M, N, T, U >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int M, int N, class T, class U>
        struct reduce_impl
        {
            enum { index = M, size = N };
            typedef reduce_impl< index + 1, size, T, U> permutation;
            
            template<class V>
            static std::tuple<T, V> visit(U t, V visitor )
            {
                using namespace std;
                
                tuple<T, V> r( permutation::visit( t, visitor ) );
                visitor = get<1>(r);
                T value( visitor( get< index - 2 >(t), get< 0 >(r) ) );
                return make_tuple( value, visitor );
            }
        };
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // reduce_impl< M, M, T, U >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int M, class T, class U>
        struct reduce_impl<M, M, T, U>
        {
            enum { index = M, size = M }; 
            
            template<class V>
            static std::tuple<T, V> visit( U t, V visitor )
            {
                using namespace std;
                T value( visitor( get< index - 2 >(t), get< index - 1 >(t) ) );
                return make_tuple( value, visitor );
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////////////
        // reduce_impl<2, 1, T, U>
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        struct reduce_impl<2, 1, T, U>
        {
            template<class V>
            static std::tuple<T, V> visit( U t, V visitor )
            {
                using namespace std;
                T value( visitor( get< 0 >(t) ) );
                return make_tuple( value, visitor );
            }
        };
   
// binary
        /////////////////////////////////////////////////////////////////////////////////////////////
        // traverse_parallel_impl< M, N, T, U >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int M, int N, class T, class U>
        struct traverse_parallel_impl
        {
            enum { index = M, size = N };
            typedef traverse_parallel_impl< index + 1, size, T, U > permutation;
            
            template<class V>
            static V visit( T lhs, U rhs, V visitor )
            {
                using namespace std;
                visitor( get< index >(lhs), get< index >(rhs) );
                return permutation::visit( lhs, rhs, visitor );
            }

            template<class V>
            static V visit_if( T lhs, U rhs, V visitor )
            {
                using namespace std;
                visitor( get< index >(lhs), get< index >(rhs) );
                return permutation::visit_if( lhs, rhs, visitor );
            }
        };
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // traverse_parallel_impl< M, M, T, U >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int M, class T, class U>
        struct traverse_parallel_impl< M, M, T, U >
        {
            template<class V>
            static V visit( T, U, V visitor )
            {   return visitor; }
            
            template<class V>
            static V visit_if( T, U, V visitor )
            {   return visitor; }
        };
    
        /////////////////////////////////////////////////////////////////////////////////////////////
        // traverse_combinations_binary_impl< M, N, O, P, T, U >
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int M, int N, int O, int P, class T, class U>
        struct traverse_combinations_binary_impl
        {
            enum { l_index = M, r_index = N, l_size = O, r_size = P };
            typedef traverse_combinations_binary_impl< l_index, r_index + 1, l_size, r_size, T, U > permutation;
            
            template<class V>
            static V visit( T lhs, U rhs, V visitor )
            {
                using namespace std;
                visitor( get< l_index >(lhs), get< r_index >(rhs) );
                return permutation::visit( lhs, rhs, visitor );
            }
        };
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // traverse_combinations_impl< M, N, O, N, T, U>
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int M, int N, int O, class T, class U>
        struct traverse_combinations_binary_impl< M, N, O, N, T, U >
        {
            enum { l_index = M, r_index = N, l_size = O, r_size = N };
            typedef traverse_combinations_binary_impl< l_index + 1, 0, l_size, r_size, T, U > permutation;
            
            template<class V>
            static V visit( T lhs, U rhs, V visitor )
            {   return permutation::visit( lhs, rhs, visitor ); }
        };
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // traverse_combinations_impl< M, N, M, O, T, U > 
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<int M, int N, int O, class T, class U>
        struct traverse_combinations_binary_impl< M, N, M, O, T, U > 
        {
            template< class V>
            static V visit( T, U, V visitor )
            {   return visitor; }
        };
    }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U traverse(T & t, U visitor)
    {   return traverse_impl< 0, std::tuple_size<T>::value, T & >::visit( t, visitor ); }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U traverse(T && t, U visitor)
    {   return traverse_impl< 0, std::tuple_size<T>::value, T && >::visit( t, visitor ); }

	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U> U traverse(const T & t, U visitor)
    {   return traverse_impl< 0, std::tuple_size<T>::value, const T & >::visit( t, visitor );  }
	
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U traverse_if(T & t, U visitor)
    {   return traverse_impl< 0, std::tuple_size<T>::value, T >::visit_if( t, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U traverse_if(T && t, U visitor)
    {   return traverse_impl< 0, std::tuple_size<T>::value, T && >::visit_if( t, visitor ); }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U traverse_if(const T & t, U visitor)
    {   return traverse_impl< 0, std::tuple_size<T>::value, const T & >::visit_if( t, visitor );  }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U traverse_combinations(T & t, U visitor)
    {   return traverse_combinations_impl< 0, 1, std::tuple_size<T>::value, T & >::visit( t, visitor ); }
	
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U traverse_combinations(T && t, U visitor)
    {   return traverse_combinations_impl< 0, 1, std::tuple_size<T>::value, T && >::visit( t, visitor ); }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U traverse_combinations(const T & t, U visitor)
    {   return traverse_combinations_impl< 0, 1, std::tuple_size<T>::value, const T & >::visit( t, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U traverse_combinations_if(T & t, U visitor)
    {   return traverse_combinations_impl< 0, 1, std::tuple_size<T>::value, T & >::visit_if( t, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U traverse_combinations_if(T && t, U visitor)
    {   return traverse_combinations_impl< 0, 1, std::tuple_size<T>::value, T && >::visit_if( t, visitor ); }
	
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    U traverse_combinations_if(const T & t, U visitor)
    {   return traverse_combinations_impl< 0, 1, std::tuple_size<T>::value, const T & >::visit_if( t, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    std::tuple<T, V> reduce(U & t, V visitor)
    {   return reduce_impl< 2, std::tuple_size<U>::value, T, U & >::visit( t, visitor );    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    std::tuple<T, V> reduce(U && t, V visitor)
    {   return reduce_impl< 2, std::tuple_size<U>::value, T, U && >::visit( t, visitor );    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    std::tuple<T, V> reduce(const U & t, V visitor)
    {   return reduce_impl< 2, std::tuple_size<U>::value, T, const U & >::visit( t, visitor );    }
    
//  binary
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_parallel(T & lhs, T & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &, T & >::visit( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_parallel(T & lhs, T && rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &, T && >::visit( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_parallel(T & lhs, const T & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &, const T & >::visit( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_parallel(T && lhs, T & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &&, T & >::visit( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_parallel(T && lhs, T && rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &&, T && >::visit( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_parallel(T && lhs, const T & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &&, const T & >::visit( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_parallel(const T & lhs, T & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, const T &, T & >::visit( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_parallel(const T & lhs, T && rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, const T &, T && >::visit( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_parallel(const T & lhs, const T & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, const T &, const T & >::visit( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_parallel(T & lhs, U & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &, U & >::visit( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_parallel(T & lhs, U && rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &, U && >::visit( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_parallel(T & lhs, const U & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &, const U & >::visit( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_parallel(T && lhs, U & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &&, U & >::visit( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_parallel(T && lhs, U && rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &&, U && >::visit( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_parallel(T && lhs, const U & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &&, const U & >::visit( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_parallel(const T & lhs, U & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, const T &, U & >::visit( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_parallel(const T & lhs, U && rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, const T &, U && >::visit( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_parallel(const T & lhs, const U & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, const T &, const U & >::visit( lhs, rhs, visitor );     }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_parallel_if(T & lhs, T & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &, T & >::visit_if( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_parallel_if(T & lhs, T && rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &, T && >::visit_if( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_parallel_if(T & lhs, const T & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &, const T & >::visit_if( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_parallel_if(T && lhs, T & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &&, T & >::visit_if( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_parallel_if(T && lhs, T && rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &&, T && >::visit_if( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_parallel_if(T && lhs, const T & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &&, const T & >::visit_if( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_parallel_if(const T & lhs, T & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, const T &, T & >::visit_if( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_parallel_if(const T & lhs, T && rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, const T &, T && >::visit_if( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_parallel_if(const T & lhs, const T & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, const T &, const T & >::visit_if( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_parallel_if(T & lhs, U & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &, U & >::visit_if( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_parallel_if(T & lhs, U && rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &, U && >::visit_if( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_parallel_if(T & lhs, const U & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &, const U & >::visit_if( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_parallel_if(T && lhs, U & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &&, U & >::visit_if( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_parallel_if(T && lhs, U && rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &&, U && >::visit_if( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_parallel_if(T && lhs, const U & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, T &&, const U & >::visit_if( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_parallel_if(const T & lhs, U & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, const T &, U & >::visit_if( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_parallel_if(const T & lhs, U && rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, const T &, U && >::visit_if( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_parallel_if(const T & lhs, const U & rhs, V visitor )
    {   return traverse_parallel_impl< 0, std::tuple_size<T>::value, const T &, const U & >::visit_if( lhs, rhs, visitor );     }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_combinations(T & lhs, T & rhs, V visitor)
    {   return traverse_combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &, T & >::visit( lhs, rhs, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_combinations(T & lhs, T && rhs, V visitor)
    {   return traverse_combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &, T && >::visit( lhs, rhs, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_combinations(T & lhs, const T & rhs, V visitor)
    {   return traverse_combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &, const T & >::visit( lhs, rhs, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_combinations(T && lhs, T & rhs, V visitor)
    {   return traverse_combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &&, T & >::visit( lhs, rhs, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_combinations(T && lhs, T && rhs, V visitor)
    {   return traverse_combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &&, T && >::visit( lhs, rhs, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_combinations(T && lhs, const T & rhs, V visitor)
    {   return traverse_combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &&, const T & >::visit( lhs, rhs, visitor ); }
 
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_combinations(const T & lhs, T & rhs, V visitor)
    {   return traverse_combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, const T &, T & >::visit( lhs, rhs, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_combinations(const T & lhs, T && rhs, V visitor)
    {   return traverse_combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, const T &, T && >::visit( lhs, rhs, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class V>
    V traverse_combinations(const T & lhs, const T & rhs, V visitor)
    {   return traverse_combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, const T &, const T & >::visit( lhs, rhs, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_combinations(T & lhs, U & rhs, V visitor)
    {   return traverse_combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &, U & >::visit( lhs, rhs, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_combinations(T & lhs, U && rhs, V visitor)
    {   return traverse_combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &, U && >::visit( lhs, rhs, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_combinations(T & lhs, const U & rhs, V visitor)
    {   return traverse_combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &, const U & >::visit( lhs, rhs, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_combinations(T && lhs, U & rhs, V visitor)
    {   return traverse_combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &&, U & >::visit( lhs, rhs, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_combinations(T && lhs, U && rhs, V visitor)
    {   return traverse_combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &&, U && >::visit( lhs, rhs, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_combinations(T && lhs, const U & rhs, V visitor)
    {   return traverse_combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &&, const U & >::visit( lhs, rhs, visitor ); }
    
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_combinations(const T & lhs, U & rhs, V visitor)
    {   return traverse_combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, const T &, U & >::visit( lhs, rhs, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_combinations(const T & lhs, U && rhs, V visitor)
    {   return traverse_combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, const T &, U && >::visit( lhs, rhs, visitor ); }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, class V>
    V traverse_combinations(const T & lhs, const U & rhs, V visitor)
    {   return traverse_combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, const T &, const U & >::visit( lhs, rhs, visitor ); }
    
    
} // om636