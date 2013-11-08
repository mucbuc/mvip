#ifndef VIEW_H__7vZN2VmaLsjrQHkXpwUi540BGoltb8
#define VIEW_H__7vZN2VmaLsjrQHkXpwUi540BGoltb8

template<typename T> 
class view
{
protected: 

	typedef T controller_type;

	virtual controller_type & controller() = 0;

public: 
	virtual ~view() = default;
};

#include "view.hxx"
#endif // VIEW_H__7vZN2VmaLsjrQHkXpwUi540BGoltb8