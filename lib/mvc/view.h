#ifndef VIEW_H__7vZN2VmaLsjrQHkXpwUi540BGoltb8
#define VIEW_H__7vZN2VmaLsjrQHkXpwUi540BGoltb8

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
	std::vector< object_type * > m_listeners; 
};

#include "view.hxx"
#endif // VIEW_H__7vZN2VmaLsjrQHkXpwUi540BGoltb8