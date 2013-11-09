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
class controller 
{
protected:
	typedef T model_type;
	typedef view< controller > view_type;

public: 
	virtual ~controller() = default;
};

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


#include "controller.hxx"
#endif // CONTROLLER_H__xewRTf24PyHN56nUqav1pzlS8MAJjo