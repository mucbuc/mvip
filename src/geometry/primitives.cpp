#ifdef __HEADER_TRANSLATION_UNIT__
	
namespace om636
{
	namespace primitives
	{
        /////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U>
        number< matrix< context< composite< TYPE_LIST_2( T, U ) > > > > make_point(const T & a, const U & b)
        {
            return number< matrix< context< composite< TYPE_LIST_2( T, U ) > > > >( a, b ); 
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U, class V, class W>
        number< matrix< context< composite< TYPE_LIST_4( T, U, V, W ) > > > > make_rect(const T & a, const U & b, const V & c, const W & d)
        {
            return number< matrix< context< composite< TYPE_LIST_4( T, U, V, W ) > > > >( a, b, c, d ); 
        }
       
		/////////////////////////////////////////////////////////////////////////////////////////////
		template<class T>
		typename type_at<typename T::list_type, 2>::result_type::value_type width(const number< matrix< T > > & r)
		{	
            SMART_ASSERT( r[kright] >= r[kleft] )(r[kright])(r[kleft]);
            return r[kright] - r[kleft]; 
		} 

		/////////////////////////////////////////////////////////////////////////////////////////////
		template<class T>
		typename type_at<typename T::list_type, 3>::result_type::value_type height(const number< matrix< T > > & r)
		{	
			ASSERT( r[kbottom] >= r[ktop] ); 
			return r[kbottom] - r[ktop]; 
		} 

		/////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U>
		bool is_union( const number< matrix< context< composite< TYPE_LIST_4( T, T, T, T ) > > > > & r, const number< matrix< context< composite< TYPE_LIST_2( U, U ) > > > > & p)
		{
			return 		p[kx] > r[kleft] &&	p[kx] < r[kright] 
					&& 	p[ky] > r[ktop]  &&	p[ky] < r[kbottom];
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U>
		bool is_union( const number< matrix< context< composite< TYPE_LIST_2( T, T ) > > > > & p, const number< matrix< context< composite< TYPE_LIST_4( U, U, U, U ) > > > > & r)
		{
			return 		p[kx] > r[kleft] &&	p[kx] < r[kright] 
					&& 	p[ky] > r[ktop]  &&	p[ky] < r[kbottom];
		}

		/////////////////////////////////////////////////////////////////////////////////////////////
		template<class T>
		void render(const number< matrix< T > > & b)
		{
			glVertex3d( b[kleft], b[ktop], 0.0 );
			glVertex3d( b[kright], b[ktop], 0.0 );
			glVertex3d( b[kright], b[kbottom], 0.0 );
			glVertex3d( b[kleft], b[kbottom], 0.0 );
	    } 

	}	// primitives
	
}	// om636

#endif 
