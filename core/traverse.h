#ifndef __TRAVERSE_H__emhAd95QCGblkZVTxDygf3upPMocRq
#define __TRAVERSE_H__emhAd95QCGblkZVTxDygf3upPMocRq

#include <tuple>

namespace om636
{
	template<class T, class U> U traverse(T &, U);
	template<class T, class U> U traverse(const T &, U);
    
    template<class T, class U> U traverse_if(T &, U);
	template<class T, class U> U traverse_if(const T &, U);

	template<class T, class U> U traverse_combinations(T &, U);
	template<class T, class U> U traverse_combinations(const T &, U);
    
    template<class T, class U> U traverse_combinations_if(T &, U);
	template<class T, class U> U traverse_combinations_if(const T &, U);
    
    template<class T, class U> U reduce(T &, U);
    template<class T, class U> U reduce(const T &, U);
}

#include "traverse.hxx"

#endif // __TRAVERSE_H__emhAd95QCGblkZVTxDygf3upPMocRq