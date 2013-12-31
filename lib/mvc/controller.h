
/*
objective: 
	
	a) controll model access
	b) view registry
	c) update views 
*/

#ifndef CONTROLLER_H__xewRTf24PyHN56nUqav1pzlS8MAJjo
#define CONTROLLER_H__xewRTf24PyHN56nUqav1pzlS8MAJjo

#include <functional>
#include <om636/lib/control/emitter.h>
#include "view.h"

template<typename T> 
struct traits
{
	typedef T model_type; 
	typedef observer<T> view_type; 
	typedef vector< view_type > views_type; 

	struct dispatch_policy
	{
		template<typename U, typename V> 
		static const U & read( U &, const U &, const V & );
	
		template<typename U, typename V> 
		static void write( const U &, const V & );
	};

	struct registration_policy
	{
		template<typename U, typename V> 
		static void detach( const U &, V & ); 

		template<typename U, typename V> 
		static void attach( const U &, V & ); 
	}; 
};

template<typename T, template<typename> typename U>
class controller 
: public U< controller< T, U > >
{
protected:
	typedef U< controller< T, U > > base_type;
	using typename base_type::dispatch_policy;
	using typename base_type::registration_policy;
	using typename base_type::views_type;

public:
	using typename base_type::model_type;
	using typename base_type::view_type;

	virtual ~controller() = default;

	virtual void attach( const view_type & ) = 0; 
	virtual void detach( const view_type & ) = 0;

	virtual void write( const model_type & ) = 0;
	virtual const model_type & read() = 0;
};

template<typename T, template<typename> typename U>
class basic_controller
: public controller< T, U > 
{
	basic_controller() = default;
	basic_controller( const basic_controller & ) = default; 
	basic_controller & operator=(const basic_controller &) = default;

	basic_controller( const model_type & ); 

	virtual ~basic_controller() = default;

	virtual void attach( const view_type & ); 
	virtual void detach( const view_type & );

	virtual void write( const model_type & );
	virtual const model_type & read();
	 
private: 
	views_type m_views; 
	model_type m_model;
};


/* 


template<typename T> 
struct emit_controller 
: controller< T > 
, om636::emitter< int, std::function<void()> >
{
	typedef controller< T > base_type;
	typedef om636::emitter< int, std::function<void()> > emitter_type;
	using typename base_type::view_type;

	virtual ~emit_controller() = default;
};

	// virtual access< model_type, read > model() const = 0; 
	// virtual access< model_type, write > model() = 0; 

	// virtual void attach( const view_type & ) = 0; 
	// virtual void detach( const view_type & ) = 0;

*/


#include "controller.hxx"
#endif // CONTROLLER_H__xewRTf24PyHN56nUqav1pzlS8MAJjo