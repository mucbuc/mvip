#ifndef VIEW_H__7vZN2VmaLsjrQHkXpwUi540BGoltb8
#define VIEW_H__7vZN2VmaLsjrQHkXpwUi540BGoltb8

#include <vector>
#include <memory>

template<typename T> 
class view
{
protected: 

	typedef T controller_type;

public: 
	virtual ~view() = default;
};

template<typename T>
struct basic_view : view< T > 
{
	typedef view< T > base_type;
	using typename base_type::controller_type;
	typedef typename controller_type::emitter_type::object_type object_type;
	
	basic_view( controller_type & )
	: base_type() 
	{}
	
	virtual ~basic_view() = default;

protected:
    
    typedef std::vector< std::shared_ptr< object_type > > listeners_type;
    typedef typename listeners_type::value_type listener_type;
    listeners_type m_listeners;
};

#include "view.hxx"
#endif // VIEW_H__7vZN2VmaLsjrQHkXpwUi540BGoltb8