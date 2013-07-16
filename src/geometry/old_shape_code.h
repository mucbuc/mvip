


		template<class V>
		key_type even_polygon(unsigned, const V&, double = 0);


#if 0
	template<class T>
	template<class U>
	void shape_policy<T>::feedback(U& shape)
	{
		feedback_buffer.resize( shape.vertecies().size() * 5 );
		glFeedbackBuffer( feedback_buffer.size(), GL_2D, &feedback_buffer[0] );
		glRenderMode(GL_FEEDBACK);
		feedback_frame a;
		
		for_each( shape.vertecies().begin(), shape.vertecies().end(), a );
		glRenderMode(GL_RENDER);
		
		U::vertex_container::iterator d( shape.vertecies().begin() );
		buffer_type::iterator s( feedback_buffer.begin() );
		
		while( d != shape.vertecies().end() )
		{
			s += 2;
			if( *s == GL_POINT_TOKEN ) 
			{
				(*d).second.value().second = &(*(++s) );
				s += 2;
			}
			else (*d).second.value().second = NULL;
			d++;
		}
	}
#endif 

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class P>
	template<class V>
	typename shape<T, U, P>::key_type shape<T, U, P>::even_polygon(unsigned n, const V& axis, double angle)
	{
		key_type face_id( unused_face() ), next( unused_vertex() ), vert_id;
		_faces.push_back( make_pair( face_id, next ) );
		
		for ( double angle_inc( 2 * om636::phi / n ); n--; angle += angle_inc )
		{
			vert_id = next; 
			_vertecies[ vert_id ] = vertex_type();
			
		#if 0
			position_of( _vertecies[ vert_id ].value() ) = Rotate(axis, angle, OrthVector(3, 0) );
		#elif 0
			valarray<double> temp( Rotate(axis, angle, OrthVector(3, 0) ) );
			position_of( _vertecies[ vert_id ].value() )[index<0>()] = temp[0];
			position_of( _vertecies[ vert_id ].value() )[index<1>()] = temp[1];
			position_of( _vertecies[ vert_id ].value() )[index<2>()] = temp[2];
		#endif	
			
			next = _vertecies[ vert_id ][ face_id ] = unused_vertex();
		}
		
		_vertecies[ vert_id ][ face_id ] = _faces.back().second;
		return face_id;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void render_face_ids(T& s) 
	{
#if 0 	
        for (T::face_container::const_iterator i( s._faces.begin() ); i != s._faces.end(); i++)
		{
			glIndexd( (double) (*i).first );
			s.traverse_coordinates( *i, render_face( GL_POLYGON ) );		
		}
#endif 	
    }
	// this belongs in render module 
	template<class T>
	void render(const number< matrix< T > > &);
	
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void render(const number< matrix< T > > & b)
	{
		glVertex3d( b[kleft], b[ktop], 0.0 );
		glVertex3d( b[kright], b[ktop], 0.0 );
		glVertex3d( b[kright], b[kbottom], 0.0 );
		glVertex3d( b[kleft], b[kbottom], 0.0 );
	} 


	/////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class P>
	void shape<T, U, P>::render() const 
	{
#if 0	
        typedef typename face_container::const_iterator const_iterator;
		
		for (const_iterator i( faces().begin() ); i != faces().end(); i++)
			traverse_coordinates( *i, render_face( GL_LINE_LOOP ) );		
#endif 	
    }



    

	namespace private_geometry

	{

        using std::valarray; 

        

		/////////////////////////////////////////////////////////////////////////////////////////////



		/////////////////////////////////////////////////////////////////////////////////////////////

		template<class T, class U, class P>

		template<class V>

		void factory< shape<T, U, P> >::register_(V& factory)

		{

			typedef typename V::functor_type functor_type;

			typedef typename V::key_type key_type;

			factory.register_create( key_type("shape"), functor_type( & create_shape ) );

			factory.register_create( key_type("polygon"), functor_type( & create_polygon ) );

			factory.register_create( key_type("circle"), functor_type( & create_circle ) );

			factory.register_create( key_type("rect"), functor_type( & create_rect ) );

			factory.register_create( key_type("box.obj"), functor_type( & create_box ) );

		}

		

		/////////////////////////////////////////////////////////////////////////////////////////////



		/////////////////////////////////////////////////////////////////////////////////////////////

		template<class T, class U, class P>

		typename factory< shape<T, U, P> >::value_type* factory< shape<T, U, P> >::create_shape()

		{

			static unsigned n( 3 );

			value_type * _shape( new value_type );

#if 0 	
            _shape->even_polygon( n++, OrthVector(3, 2) );

			transpond_face< value_type, valarray<double> > a( *_shape, OrthVector(3, 1) + OrthVector(3, 2) );

			_shape->traverse_vertecies( _shape->faces().front(), a );

#endif 	
            return _shape;

		}



		/////////////////////////////////////////////////////////////////////////////////////////////



		/////////////////////////////////////////////////////////////////////////////////////////////

		template<class T, class U, class P>

		typename factory< shape<T, U, P> >::value_type* factory< shape<T, U, P> >::create_polygon()

		{

			static unsigned n( 4 );

			value_type * _shape( new value_type );

#if 0		
            _shape->even_polygon( n++, OrthVector(3, 2) );

#endif 
            return _shape;

		}



		/////////////////////////////////////////////////////////////////////////////////////////////



		/////////////////////////////////////////////////////////////////////////////////////////////

		template<class T, class U, class P>

		typename factory< shape<T, U, P> >::value_type* factory< shape<T, U, P> >::create_circle()

		{

			static unsigned n( 5 );

			value_type * _shape( new value_type );

//			_shape->even_polygon( n++, OrthVector(3, 2) );

			return _shape;

		}



		/////////////////////////////////////////////////////////////////////////////////////////////



		/////////////////////////////////////////////////////////////////////////////////////////////

		template<class T, class U, class P>

		typename factory< shape<T, U, P> >::value_type* factory< shape<T, U, P> >::create_rect()

		{

			value_type * _shape( new value_type );

//			_shape->even_polygon( 4, OrthVector(3, 2), om636::phi / 4 );

			return _shape;

		}



		/////////////////////////////////////////////////////////////////////////////////////////////



		/////////////////////////////////////////////////////////////////////////////////////////////

		template<class T, class U, class P>

		typename factory< shape<T, U, P> >::value_type * factory< shape<T, U, P> >::create_box()

		{

#if 0	

            using namespace toolbag;

			typedef shape<T, U, P> context_type;

			

			std::ifstream fin( "box.obj" ); 

			ASSERT( fin ); 

			

			lexer<double, istream> _lexer(fin);

			

			context_type _context;

			parser< context_type, lexer<double, istream> > a( _lexer, statement_state(), _context );

			

			value_type * _shape( new value_type );

			_shape->swap( a.interpret() );

			return _shape;

#endif 		

        }



	} // private_geometry

	namespace private_geometry
	{	
		template<class T, class U, class P>
		struct factory< shape<T, U, P> >
		{
			typedef shape<T, U, P> value_type;
			
			template<class V>
			static void register_(V&);
		private:
			
			static value_type * create_shape();	
			static value_type * create_polygon();	
			static value_type * create_circle();	
			static value_type * create_rect();	
			static value_type * create_box();
		};
	}