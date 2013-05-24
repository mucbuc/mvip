/*
om636
Copyright (c) 2013 by Mark Busenitz
www.github.com/mucbuc

objective:
    - std::tuple traversal functions
 
dependancies:
    - std::tuple

usage: 
    - the last argument is allways the functor handling the elements
    - the tuples can be passed by left reference, right reference or const reference
    - all '_if' versions cancel traversal if the functor returns false
    - traverse( tuple< a, b, c >(), f );                             ==> f( a ); f( b ); b( c );
    - traverse_combinations( tuple< a, b, c >(), f );                 ==> f( a, b ); f( a, c ); f( b, c );
    - reduce( tuple< a, b, c >(), f );                                 ==> f( f( a, b ), c );
    - traverse_parallel( tuple< a, b, c >(), tuple< d, e >, f );     ==> f( a, d ); f( b, e );

todo:
     - traverse_adjacent( tuple< a, b, c >(), f )                     ==> f( a, b ), f( b, c );
*/

#ifndef TRAVERSE_H__emhAd95QCGblkZVTxDygf3upPMocRq
#define TRAVERSE_H__emhAd95QCGblkZVTxDygf3upPMocRq

#include <tuple>

namespace om636
{
    
//  unary
    template<class T, class U> U traverse(T &, U);
    template<class T, class U> U traverse(T &&, U);
    template<class T, class U> U traverse(const T &, U);
    
    template<class T, class U> U traverse_if(T &, U);
    template<class T, class U> U traverse_if(T &&, U);
    template<class T, class U> U traverse_if(const T &, U);

    template<class T, class U> U traverse_combinations(T &, U);
    template<class T, class U> U traverse_combinations(T &&, U);
    template<class T, class U> U traverse_combinations(const T &, U);
    
    template<class T, class U> U traverse_combinations_if(T &, U);
    template<class T, class U> U traverse_combinations_if(T &&, U);
    template<class T, class U> U traverse_combinations_if(const T &, U);
    
    template<class T, class U, class V> std::tuple<T, V> reduce(U &, V);
    template<class T, class U, class V> std::tuple<T, V> reduce(U &&, V);
    template<class T, class U, class V> std::tuple<T, V> reduce(const U &, V);
    
//  binary
    template<class T, class V> V traverse_parallel(T &, T &, V);
    template<class T, class V> V traverse_parallel(T &, T &&, V);
    template<class T, class V> V traverse_parallel(T &, const T &, V);
    
    template<class T, class V> V traverse_parallel(T &&, T &, V);
    template<class T, class V> V traverse_parallel(T &&, T &&, V);
    template<class T, class V> V traverse_parallel(T &&, const T &, V);
    
    template<class T, class V> V traverse_parallel(const T &, T &, V);
    template<class T, class V> V traverse_parallel(const T &, T &&, V);
    template<class T, class V> V traverse_parallel(const T &, const T &, V);
    
    template<class T, class U, class V> V traverse_parallel(T &, U &, V);
    template<class T, class U, class V> V traverse_parallel(T &, U &&, V);
    template<class T, class U, class V> V traverse_parallel(T &, const U &, V);
    
    template<class T, class U, class V> V traverse_parallel(T &&, U &, V);
    template<class T, class U, class V> V traverse_parallel(T &&, U &&, V);
    template<class T, class U, class V> V traverse_parallel(T &&, const U &&, V);
    
    template<class T, class U, class V> V traverse_parallel(const T &, U &, V);
    template<class T, class U, class V> V traverse_parallel(const T &, U &&, V);
    template<class T, class U, class V> V traverse_parallel(const T &, const U &&, V);
    
    template<class T, class V> V traverse_parallel_if(T &, T &, V);
    template<class T, class V> V traverse_parallel_if(T &, T &&, V);
    template<class T, class V> V traverse_parallel_if(T &, const T &, V);
    
    template<class T, class V> V traverse_parallel_if(T &&, T &, V);
    template<class T, class V> V traverse_parallel_if(T &&, T &&, V);
    template<class T, class V> V traverse_parallel_if(T &&, const T &, V);
    
    template<class T, class V> V traverse_parallel_if(const T &, T &, V);
    template<class T, class V> V traverse_parallel_if(const T &, T &&, V);
    template<class T, class V> V traverse_parallel_if(const T &, const T &, V);
    
    template<class T, class U, class V> V traverse_parallel_if(T &, U &, V);
    template<class T, class U, class V> V traverse_parallel_if(T &, U &&, V);
    template<class T, class U, class V> V traverse_parallel_if(T &, const U &, V);
    
    template<class T, class U, class V> V traverse_parallel_if(T &&, U &, V);
    template<class T, class U, class V> V traverse_parallel_if(T &&, U &&, V);
    template<class T, class U, class V> V traverse_parallel_if(T &&, const U &&, V);
    
    template<class T, class U, class V> V traverse_parallel_if(const T &, U &, V);
    template<class T, class U, class V> V traverse_parallel_if(const T &, U &&, V);
    template<class T, class U, class V> V traverse_parallel_if(const T &, const U &, V);
    
    template<class T, class V> V traverse_combinations(T &, T &, V);
    template<class T, class V> V traverse_combinations(T &, T &&, V);
    template<class T, class V> V traverse_combinations(T &, const T &, V);
    
    template<class T, class V> V traverse_combinations(T &&, T &, V);
    template<class T, class V> V traverse_combinations(T &&, T &&, V);
    template<class T, class V> V traverse_combinations(T &&, const T &, V);
    
    template<class T, class V> V traverse_combinations(const T &, T &, V);
    template<class T, class V> V traverse_combinations(const T &, T &&, V);
    template<class T, class V> V traverse_combinations(const T &, const T &, V);
    
    template<class T, class U, class V> V traverse_combinations(T &, U &, V);
    template<class T, class U, class V> V traverse_combinations(T &, U &&, V);
    template<class T, class U, class V> V traverse_combinations(T &, const U &, V);
    
    template<class T, class U, class V> V traverse_combinations(T &&, U &, V);
    template<class T, class U, class V> V traverse_combinations(T &&, U &&, V);
    template<class T, class U, class V> V traverse_combinations(T &&, const U &&, V);
    
    template<class T, class U, class V> V traverse_combinations(const T &, U &, V);
    template<class T, class U, class V> V traverse_combinations(const T &, U &&, V);
    template<class T, class U, class V> V traverse_combinations(const T &, const U &&, V);
    
    template<class T, class V> V traverse_combinations_if(T &, T &, V);
    template<class T, class V> V traverse_combinations_if(T &, T &&, V);
    template<class T, class V> V traverse_combinations_if(T &, const T &, V);
    
    template<class T, class V> V traverse_combinations_if(T &&, T &, V);
    template<class T, class V> V traverse_combinations_if(T &&, T &&, V);
    template<class T, class V> V traverse_combinations_if(T &&, const T &, V);
    
    template<class T, class V> V traverse_combinations_if(const T &, T &, V);
    template<class T, class V> V traverse_combinations_if(const T &, T &&, V);
    template<class T, class V> V traverse_combinations_if(const T &, const T &, V);
    
    template<class T, class U, class V> V traverse_combinations_if(T &, U &, V);
    template<class T, class U, class V> V traverse_combinations_if(T &, U &&, V);
    template<class T, class U, class V> V traverse_combinations_if(T &, const U &, V);
    
    template<class T, class U, class V> V traverse_combinations_if(T &&, U &, V);
    template<class T, class U, class V> V traverse_combinations_if(T &&, U &&, V);
    template<class T, class U, class V> V traverse_combinations_if(T &&, const U &&, V);
    
    template<class T, class U, class V> V traverse_combinations_if(const T &, U &, V);
    template<class T, class U, class V> V traverse_combinations_if(const T &, U &&, V);
    template<class T, class U, class V> V traverse_combinations_if(const T &, const U &, V);
    
    namespace Private
    {
        // traverse_impl
        template<int, int, class>
        struct traverse_impl;
        
        template<int M, class T>
        struct traverse_impl< M, M, T >;
        
        
        // traverse_combinations_impl
        template<int, int, int, class >
        struct traverse_combinations_impl;
        
        template<int M, int N, class T>
        struct traverse_combinations_impl< M, N, N, T >;
        
        template<int M, int N, class T >
        struct traverse_combinations_impl< M, N, M, T >;
        

        // reduce_impl
        template<int, int, class, class>
        struct reduce_impl;
        
        template<int M, class T, class U>
        struct reduce_impl< M, M, T, U>;
        
        template<class T, class U>
        struct reduce_impl<2, 1, T, U>;
        
        
        // traverse_parallel_impl
        template<int, int, class, class>
        struct traverse_parallel_impl;
        
        template<int M, class T, class U>
        struct traverse_parallel_impl< M, M, T, U >;
        
        
        // traverse_combinations_binary_impl
        template<int, int, int, int, class, class>
        struct traverse_combinations_binary_impl;
        
        template<int M, int N, int O, class T, class U>
        struct traverse_combinations_binary_impl< M, N, O, N, T, U >;
        
        template<int M, int N, int O, class T, class U>
        struct traverse_combinations_binary_impl< M, N, M, O, T, U >;
        
    }   // Private
}   //  om636

#include "traverse.hxx"

#endif // __TRAVERSE_H__emhAd95QCGblkZVTxDygf3upPMocRq