/* 
 objective:
    collection of simple "geometric" primitives: 
        - point: 2 dimensional vector 
        - rect: has noting to do with a rectangle, vertical and horizontal range, right >= left, top >= bottom
            currently rect is implemented as a matrix, i think it should be a vector of ranges. 
 */ 


#ifndef _PRIMITIVES_H_0870980980980
	#define _PRIMITIVES_H_0870980980980

#include "assert.h"
#include "components.h"
#include "math.h"
#include "matrix.h"
#include "number.h"

// if mac
#include <OpenGL/gl.h>


namespace om636
{
	namespace primitives
	{	
		static index<0> kx;
		static index<1> ky;
		
        // point_with
		template<class T>
		class point_with
		{
			typedef context< composite< TYPE_LIST_2( T, T ) > > context_type;
		public:
			typedef number< matrix< context_type > > result_type; 		
		};
        
        // make_point
        template<class T, class U>
        number< matrix< context< composite< TYPE_LIST_2( T, U ) > > > > make_point(const T &, const U &); 
		
		static index<0> kleft;
		static index<1> ktop;
		static index<2> kright;
		static index<3> kbottom;
		
        // rect_with
		template<class T>
		class rect_with
		{
			typedef context< composite< TYPE_LIST_4( T, T, T, T ) > > context_type;
		public:
			typedef number< matrix< context_type > > result_type; 		
		};
        
        // make_rect
        template<class T, class U, class V, class W>
        number< matrix< context< composite< TYPE_LIST_4( T, U, V, W ) > > > > make_rect(const T &, const U &, const V &, const W &); 
        
		template<class T>
		typename type_at<typename T::list_type, 2>::result_type::value_type width(const number< matrix< T > > &);

		template<class T>
		typename type_at<typename T::list_type, 3>::result_type::value_type height(const number< matrix< T > > &); 

		template<class T, class U>
		bool is_union( const number< matrix< context< composite< TYPE_LIST_4( T, T, T, T ) > > > > &, const number< matrix< context< composite< TYPE_LIST_2( U, U ) > > > > &);		
	
		template<class T, class U>
		bool is_union( const number< matrix< context< composite< TYPE_LIST_2( T, T ) > > > > &, const number< matrix< context< composite< TYPE_LIST_4( U, U, U, U ) > > > > &);
		
		// this belongs in render module 
		template<class T>
		void render(const number< matrix< T > > &);

	}	// primitives

}	// om636
		
#define HEADER_TRANSLATION_UNIT__
#include "primitives.cpp"
#undef __HEADER_TRANSLATION_UNIT__


#endif // _TEMPLATE_H_8900700