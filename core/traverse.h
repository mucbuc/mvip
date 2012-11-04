#ifndef __TRAVERSE_H__emhAd95QCGblkZVTxDygf3upPMocRq
#define __TRAVERSE_H__emhAd95QCGblkZVTxDygf3upPMocRq

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
}

#include "traverse.hxx"

#endif // __TRAVERSE_H__emhAd95QCGblkZVTxDygf3upPMocRq