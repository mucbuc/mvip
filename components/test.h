#include <iostream>
#include <om636/core/core.h>
#include <om636/components/context.h>
#include <om636/components/observer.h>
#include <om636/components/subject.h>
#include <om636/math/dummy.h>

#include <string>

namespace 
{
	
	template<class T>
	struct test_observer : om636::observer< T >
	{
		test_observer( T & s )
		: m_context( & s )
		, m_swapped( 0 )
		{
			m_context->attach( this );
		}
		
		virtual ~test_observer()
		{
			if (m_context)
				m_context->detach( this );
		}
		
		virtual void on_swap( const T & lhs, const T &)
		{
			m_swapped = 1;
		}
		
		virtual void detach( void * subject )
		{
			ASSERT( m_context == subject );
			
			m_context = 0; 
		}
		
		void reset()
		{
			m_swapped = 0;
		}
		
		bool swapped()
		{
			return m_swapped;
		}
	
		T * m_context;
	
	private:
		bool m_swapped;
	};
	
	template<class T>
	struct test_observer2 : test_observer< T >
	{
		typedef test_observer<T> base_type;
		
		test_observer2( T & s )
		: base_type( s )
		{}
		
		virtual ~test_observer2()
		{}
		
		virtual void on_swap( const T & lhs, const T & rhs)
		{
			base_type::m_context->detach( this );
			base_type::on_swap( lhs, rhs );
		}
	};
	
	template<class T>
	struct test_observer3 : test_observer< T >
	{
		typedef test_observer<T> base_type;
		
		test_observer3( T & s )
		: base_type( s )
		{}
		
		virtual ~test_observer3()
		{}
		
		virtual void on_swap( const T & lhs, const T & rhs)
		{
			* base_type::m_context = 1;
			base_type::on_swap( lhs, rhs );
		}
	};
	
	void test_swap()
	{
		using namespace om636;
		
		typedef context< int, basic_subject > context_type;
		typedef test_observer< context_type  > observer_type;
		
		context_type c;
		observer_type o( c );
		o.reset();
	
		ASSERT( ! o.swapped() );
		c = 0;
		ASSERT( o.swapped() );
	}
	
	template< template<class> class T >
	void test_detach_while_swap()
	{
		using namespace om636;
		
		typedef context< int, T > context_type;
		typedef test_observer2< context_type  > observer_type;
		
		context_type c;
		observer_type o( c );
		
		o.reset();
		
		ASSERT( ! o.swapped() );
		
		try
		{
			c = 0;
		}
		catch (typename context_type::locked)
		{
			return;
		}
		
		ASSERT( 0 );
	}
	
	template< template<class> class T >
	void test_subject_invalidate()
	{
		using namespace om636;
		
		typedef context< int, T > context_type;
		typedef test_observer2< context_type  > observer_type;
		
		context_type * c( new context_type() );
		observer_type o( * c );
		
		ASSERT( c == o.m_context );
		
		delete c;
	
		ASSERT( !o.m_context );
	}
	
	template< template<class> class T >
	void test_swap_while_swap()
	{
		using namespace om636;
		
		typedef context< int, T > context_type;
		typedef test_observer3< context_type  > observer_type;
		
		context_type c;
		observer_type o( c );
		
		try
		{
			c = 0;
		}
		catch (typename context_type::locked)
		{
			return;
		}
	
		ASSERT( 0 );
	}
	
	template< template<class> class T >
	void test_persistence()
	{
		typedef om636::context< int, T > context_type;
		
		if (1)
		{
			context_type a( std::string("test_persistence_var") );
			a = 1230;
		}
		
		if (1)
		{
			context_type a( std::string("test_persistence_var") );
			
			ASSERT( a.value_ref() == 1230 );
		
			a = 1239;
		}
	
		if (1)
		{
			context_type a( std::string("test_persistence_var") );
		
			ASSERT( a.value_ref() == 1239 );
		}
	}
	
	template<class T>
	using safe_policy = om636::safe_subject< om636::basic_subject< T > >;
	
	template<class T>
	using persistent_policy = om636::persistent_subject< safe_policy< T > >;
	
    template<class T>
    void run_observer_test()
    {
        using namespace om636;
    
        test_swap();
        test_detach_while_swap< safe_policy >();
        test_subject_invalidate< safe_policy >();
        test_swap_while_swap< safe_policy >();
        test_persistence< persistent_policy >();
        std::cout << "observer test passed" << std::endl;
	}
}