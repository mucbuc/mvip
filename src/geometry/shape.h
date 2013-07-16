#ifndef SHAPEH_INCLUDE_GUARD__43243243
	#define SHAPEH_INCLUDE_GUARD__43243243

#include "geometryfwd.h"
#include <list>
#include <map>
#include <vector>

#import <OpenGL/gl.h>
#include "vertex.h"
#include "mathutills.h"
//#include "cont.h"
//#include "lexer.h"
//#include "render.h"

namespace toolbag
{
	template<class T>
	class shape_policy 
	{
	public:
		//typedef std::vector<T> buffer_type;
		//buffer_type feedback_buffer;

		shape_policy()
		{}
		void swap(shape_policy &) {}
		//template<class U>	
		//void feedback(U& shape);
	};
	
	template<class T>
	void swap(shape_policy<T> &, shape_policy<T> &) {}

	template<class T, class U, class P>  
	class shape 
		: protected P
	{
	public:
		// types
		typedef T value_type;
		typedef U key_type;
		typedef P base_type;
		typedef std::pair< key_type, key_type > face_type;
		typedef std::list< face_type > face_container;
		typedef vertex< value_type, key_type > vertex_type;
		typedef std::map< key_type, vertex_type > vertex_container;
	
		// resources	
		shape();
		shape( const shape& );
		~shape() {}
		shape& operator=(shape);
		void swap(shape &);
	
		// access	
		const face_container & faces() const;
		const vertex_container & vertecies() const;
		vertex_container & vertecies();

		template<class F>
		void traverse_coordinates(const face_type&, F) const;
		
		template<class F> 
		void traverse_vertecies(const face_type&, F); 

		template<class I>
		key_type insert_loop(I i, I e);
		
		template<class V>
		key_type insert_vertex(const V&);
		
		template<class V>
		void insert_face(const V&);

		void render() const; 
	
	private:
		key_type unused_face() const;
		key_type unused_vertex() const;
		
		face_container _faces;
		mutable vertex_container _vertecies;
	};
	
	template<class T, class U, class P>
	void swap(shape<T, U, P> &, shape<T, U, P> &);
	
	template<class T, class U>
	class transpond_face 
	{
		mutable T _shape; 
		mutable typename T::key_type original, astral;
		U offset;
		
	public:

		transpond_face(T& s, const U& v);
		~transpond_face();
		void operator()(const typename T::key_type& v) const;
	};

	template<class T>
	void render_face_ids( T& );

	template<class T, class O>
	O rect_grid(unsigned n, unsigned m, const T& nu, const T& mu, O out);

	template<class O>
	O wave(unsigned n, O out);

	template<class I, class O>		
	O transpond(I b, I e, O o, bool wrap_around);
	
} // toolbag

#define HEADER_TRANSLATION_UNIT__
#include "shape.cpp"
#undef __HEADER_TRANSLATION_UNIT__

#endif // __SHAPEH_INCLUDE_GUARD__43243243