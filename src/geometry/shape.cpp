#ifdef __HEADER_TRANSLATION_UNIT__

namespace toolbag
{
	/////////////////////////////////////////////////////////////////////////////////////////////
    // shape<T, U, P>
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class P>
	const typename shape<T, U, P>::face_container & shape<T, U, P>::faces() const
	{ return _faces; }

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class P>
	typename shape<T, U, P>::vertex_container & shape<T, U, P>::vertecies()
	{ return _vertecies; }

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class P>
	const typename shape<T, U, P>::vertex_container & shape<T, U, P>::vertecies() const
	{ return _vertecies; }

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class P>
	typename shape<T, U, P>::key_type shape<T, U, P>::unused_face() const
	{	return _faces.size() + 1;	}
		
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class P>
	typename shape<T, U, P>::key_type shape<T, U, P>::unused_vertex() const
	{	return _vertecies.size() + 1;	}
		
	/////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class P> 
	shape<T, U, P>::shape()
	{}
	
	/////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class P> 
	shape<T, U, P>::shape( const shape& s)
		: _faces( s._faces.begin(), s._faces.end() )
		, _vertecies( s._vertecies.begin(), s._vertecies.end() )
		, base_type( s )
	{	assert( _faces.size() == s._faces.size() && _vertecies.size() == s._vertecies.size() );	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class P>
	template<class F> 
	void shape<T, U, P>::traverse_vertecies(const face_type& face, F func)
	{
		func( face.second );
		vertex_type* here( &(_vertecies[ face.second ]) );
		for (int index( (*here)[ face.first ] ); index != face.second; index = (*here)[ face.first ])
		{
			func( index );
			here = &_vertecies[ index ];
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class P>
	template<class I>
	typename shape<T, U, P>::key_type shape<T, U, P>::insert_loop(I i, I e)
	{
		typename shape<T, U, P>::key_type result( unused_face() );
		
		key_type first( *i );
		key_type last; 	
		while(i != e)
		{
			last = *i++;
			_vertecies[last][ result ] = *i;
		}
		_vertecies[last][ result ] = first;
		return result;
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class P>
	template<class V>
	typename shape<T, U, P>::key_type shape<T, U, P>::insert_vertex(const V& v)
	{
		key_type result( unused_vertex() );
		position_of( _vertecies[ result ].value() ) = v;
		return result;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class P>
	template<class V>
	void shape<T, U, P>::insert_face(const V& f)
	{	_faces.push_back( f );	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class P> 
	shape<T, U, P> & shape<T, U, P>::operator=(shape s)
	{
		swap( s );
		return *this;
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class P>
	template<class F>  
	void shape<T, U, P>::traverse_coordinates(const face_type& face, F func) const
	{
		assert( _vertecies.find( face.second ) != _vertecies.end() );
		
		vertex_type* here( &(_vertecies[ face.second ]) );
		func( (*here).value() );
		
		for (int index( (*here)[ face.first ] ); index != face.second; index = (*here)[ face.first ])
		{
			assert( _vertecies.find( index ) != _vertecies.end() ); 
			here = &_vertecies[ index ];
			func( (*here).value() );
		}
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class P>
	void shape<T, U, P>::swap(shape & s)
	{
		base_type::swap( s );
		_faces.swap( s._faces );
		_vertecies.swap( s._vertecies );
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class P>
	void swap(shape<T, U, P> & lhs, shape<T, U, P> & rhs)
	{	rhs.swap( lhs );	}

    /////////////////////////////////////////////////////////////////////////////////////////////
    // transpond_face<T, U>
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U>
    transpond_face<T, U>::transpond_face(T& s, const U& v) 
        : _shape(s)
        , offset( v )
        , original( 0 )
        , astral( 0 )
    {}
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U>
	transpond_face<T, U>::~transpond_face() {} 
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U>
	void transpond_face<T, U>::operator()(const typename T::key_type& v) const
	{
		//assert( v );
		
		if (original)
		{
			typename T::key_type temp( _shape.insert_vertex( position_of(_shape.vertecies()[ v ].value() ) + offset ) );
            std::vector<typename T::key_type> l;
			l.push_back( temp );
			l.push_back( v );
			l.push_back( original );
			l.push_back( astral );
			_shape.insert_face( make_pair( _shape.insert_loop( l.begin(), l.end() ), temp ) );
			astral = temp;
		}
		else
			astral = _shape.insert_vertex( position_of( _shape.vertecies()[ v ].value() ) + offset );
		original = v;	
	}
} // toolbag 

#else 

#include "shape.h"

using namespace std;

#endif // __HEADER_TRANSLATION_UNIT__ 
