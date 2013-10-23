#ifndef __TEST_QUERY_H__VIM4eFvTuUcy0QO3oqg6PxBENX2sDG
#define __TEST_QUERY_H__VIM4eFvTuUcy0QO3oqg6PxBENX2sDG

#include <om636/lib/lambda/query.h>
#include <sstream>
#include <string>
#include <set>

namespace om636
{
	
	template<class T>
	struct test_query
	: om636::query_base<T>
	{
		typedef T context_type;
		typedef om636::query_base<context_type> base_type;
		
		using typename base_type::value_type;
		using typename base_type::batch_base;
		using typename base_type::real_time_base;
		
		template<class U>
		test_query( U & );
		
		virtual ~test_query() {}
		
		void on_swap( const typename base_type::real_time_base::context_type &, const typename base_type::real_time_base::context_type &);
		
		void on_swap( const typename base_type::batch_base::context_type &, const typename base_type::batch_base::context_type &);
	
		void print();

        typedef std::set< value_type > data_type;
        
        data_type & data();
        const data_type & data() const; 
        
	private:
		std::set< value_type > m_data;
	};
	
} // om636 

#include "test_query.hxx"
#endif // __TEST_QUERY_H__VIM4eFvTuUcy0QO3oqg6PxBENX2sDG