#ifndef _SCOPE_GUARD_H_8900700
	#define _SCOPE_GUARD_H_8900700
	
namespace toolbag
{
	class scope_guard_base
	{
	public:		
		scope_guard_base();
		scope_guard_base( const scope_guard_base & );
		~scope_guard_base();
	
		void dismiss() const throw(); 
	
	protected:
		bool is_dismissed();
	private:
		mutable bool m_dismissed;
	};

	template<class T> 
	class scope_guard_impl 
	: public scope_guard_base 
	{
	public:	
		scope_guard_impl(const T &);
		scope_guard_impl(const scope_guard_impl &);
		~scope_guard_impl();
		
		void dismiss(); 
					
	private:
		T m_functor; 
	
        // undefined
		scope_guard_impl & operator=(const scope_guard_impl &); 
	};

	template<class T> scope_guard_impl<T> make_scope_guard(const T &);
    
}	// toolbag 
	
#include "scopeguard.hxx"

#endif // _SCOPE_GUARD_H_8900700