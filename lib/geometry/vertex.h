#ifndef VERTEXH_INCLUDE_GUARD__43897899243243
	#define VERTEXH_INCLUDE_GUARD__43897899243243

#include "geometryfwd.h"
#include <map>

namespace toolbag
{
	template<class T> 
	class vertex_policy
	{
		typedef T value_type;
		
		static value_type init_value( const value_type& position )
		{ 	return position; }
	};

	template<class T> 
	class vertex_feedback_policy
	{
	public:
		typedef std::pair< T, float* > value_type;

		static value_type init_value( const T& position )
		{	return make_pair( position, (float*) NULL );	}
	};

	template<class T, class U> 
	const T& position_of( const std::pair<T, U>& a)
	{	return a.first; }	

	template<class T, class U> 
	T& position_of( std::pair<T, U>& a)
	{	return a.first; }	

	//template<class T>
	//static T& position_of(const T& a)
	//{	return a; 	}	

	template<class T, class U>
	class vertex : public std::map< U, U > 
	{
	public:		
		// types
		typedef T value_type;
		typedef std::map< U, U > base_type;
		
		// resources
		vertex();
		vertex(const vertex & v);
		vertex(const value_type & v);
		~vertex() {}
		vertex & operator=(vertex);
		void swap(vertex &);
		
		// access
		value_type & value();
		const value_type & value() const;
	
	private:
		value_type value_;
	};

	template<class T, class U>
	void swap(vertex<T, U> &, vertex<T, U> &);


} // toolbag 

#define HEADER_TRANSLATION_UNIT__
#include "vertex.cpp"
#undef __HEADER_TRANSLATION_UNIT__

#endif // __VERTEXH_INCLUDE_GUARD__43897899243243