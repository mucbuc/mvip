/*
objective: 
	
	a) controll model access
	b) view registry
	c) update views 
*/

#ifndef CONTROLLER_H__xewRTf24PyHN56nUqav1pzlS8MAJjo
#define CONTROLLER_H__xewRTf24PyHN56nUqav1pzlS8MAJjo

#include "view.h"

//Controller
template<typename T>
class controller 
{
protected:
	typedef T model_type;
	typedef view< controller > view_type;

	// virtual access< model_type, read > model() const = 0; 
	// virtual access< model_type, write > model() = 0; 

public: 
	virtual ~controller() = default;

	virtual void attach( const view_type & ) = 0; 
	virtual void detach( const view_type & ) = 0;
};

#include "controller.hxx"
#endif // CONTROLLER_H__xewRTf24PyHN56nUqav1pzlS8MAJjo