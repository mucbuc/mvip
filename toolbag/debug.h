#ifndef DEBUG_H__INCLUDE_GUARD__a8e63jjdj8729k
	#define DEBUG_H__INCLUDE_GUARD__a8e63jjdj8729k

#include "toolbagfwd.h"
#include "assert.h"
#include <iostream>
#include <vector>

namespace toolbag
{
	struct message_base
	{
		virtual ~message_base();
	    virtual	void print() = 0;
        virtual message_base * copy() = 0;
	}; 

	template<class T>
	class static_msg : public message_base
	{
		T msg;

		static_msg();
		static_msg & operator=(static_msg) = delete; 
		
	public:

		static_msg(T);
		static_msg(const static_msg &);
		
		void print();
		message_base * copy();
	};

	class message
	{
		message_base * msg;
		
		message();
		message & operator=(message) = delete; 
		
	public:
		template<int N>
		message( const char(& m)[N] );
		
		message(const message &);
		~message();
		void operator()(); 
	};

#if FALSE

	namespace track_function
	{

	class function_stack
	{
		static std::vector<const char* > function_names;

		function_stack() {}

		~function_stack()
		{
			while( function_names.size() )
			{
				std::cout << function_names.back() << std::endl;
				function_names.pop_back();
			}
		}
		
	public:
		
		struct pop
	 	{
		 	const char* operator()()
			{
				const char *result( function_names.back() );
				function_names.pop_back();
				return result;
			}
		};

		static pop push(const char* name)
		{
			static function_stack call_destruct;
			
			function_names.push_back(name);
			return pop();
		}
	};

	std::vector<const char* > function_stack::function_names;

	}

	#define TRACK_FUNCTION \
		static const char* TRACK_FUNCTION_name =__FUNCTION__; \
		destructor_call<track_function::function_stack::pop> __FUNCTION__tracker( \
			track_function::function_stack::push( TRACK_FUNCTION_name ) );

	//#define TRACK_SCOPE( msg ) \
	//	static const char* TRACK_FUNCTION_name = msg; \
	//	destructor_call<track_function::function_stack::pop> __FUNCTION__tracker( \
	//		track_function::function_stack::push( TRACK_FUNCTION_name ) );	
#endif	

} // toolbag

#include "debug.hxx"

#endif // DEBUG_H__INCLUDE_GUARD__a8e63jjdj8729k