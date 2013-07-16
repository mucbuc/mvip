namespace toolbag
{
	// shape 
    template<class> 
	class shape_policy; 

	template<class, class, class>  
	class shape; 

	template<class, class>
	class transpond_face;

    // vertex 
	template<class T> 
	class vertex_policy;
	
	template<class T> 
	class vertex_feedback_policy;
	
	template<class T, class U>
	class vertex;
	
    // geofactory 
	template<class T>
	struct geometry_factory;
	
	namespace private_geometry
	{	
		template<class>
		struct factory;

		template<class>
		struct unit;
	}

    // primitives 
    template<class> class point_with;
    template<class> class rect_with;
}