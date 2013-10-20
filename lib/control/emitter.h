/*

 */

#ifndef emitter_H__JhLAPnS3Wp842MtFlNU59YkvsoQyIR
#define EMITTER_H__JhLAPnS3Wp842MtFlNU59YkvsoQyIR

#include <map>
#include <vector> 

namespace om636
{
    struct object_base
    {
        virtual ~object_base() = 0;
        
    };
    
    
    template<typename T>
    struct default_emitter_policy
    {
        typedef object_base obeject_type;
    };
    
    
    template<class T, class U, template<class> class V = default_emitter_policy>
	class emitter
    : private V< emitter<T, U, V> > 
	{
        typedef T event_type;
        typedef U function_type;
        typedef V< emitter< event_type, function_type, V > > base_type;
      //  typedef om636::queue< event_type > queue_type;

        using typename base_type::object_type;
        
        
        struct Batch
        {
			void include( function_type );
        	void exclude( function_type ); 
        
        	void invoke(); 

        private: 

        	std::vector< function_type > m_functions;
        };

        
    public:
        
        struct Listener : object_type
        {
            virtual ~Listener();
        };

        emitter();
		virtual ~emitter();
		virtual void emit( event_type ); 
	
		Listener on( event_type, function_type );
        Listener addListener( event_type, function_type );
        Listener once( event_type, function_type );
        
        void removeListener( Listener );
        void removeAllListeners();
        
        std::vector< Listener > listeners( event_type );
        
	private:
    
	//	typedef std::map< key_type, pair< Batch, Batch > > map_type;
    //	map_type m_batches;
    };

}	// om636

#include "emitter.hxx"
#endif // __EMITTER_H__JhLAPnS3Wp842MtFlNU59YkvsoQyIR