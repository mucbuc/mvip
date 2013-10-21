/*

 */

#ifndef emitter_H__JhLAPnS3Wp842MtFlNU59YkvsoQyIR
#define EMITTER_H__JhLAPnS3Wp842MtFlNU59YkvsoQyIR

#include <map>
#include <set>
#include <memory>

namespace om636
{
    template<typename T>
    struct default_emitter_policy
    {
        struct object_base
        {
            virtual ~object_base() = 0;
        };
        
        typedef object_base object_type;
    };
    
    template<class T, class U, template<class> class V = default_emitter_policy>
	class emitter
    : private V< emitter<T, U, V> > 
	{
        typedef T event_type;
        typedef U function_type;
        typedef V< emitter< event_type, function_type, V > > base_type;
      //  typedef om636::queue< event_type > queue_type;
        
        
        struct Agent
        {
            Agent( function_type callback )
            : m_cancel(0)
            , m_callback( callback )
            {}
            
            void cancel() { m_cancel = 1; }
            bool is_canceled() { return m_cancel; }
            function_type callback() { return m_callback; }
        
        private:
            bool m_cancel;
            function_type m_callback;
        };
        
        struct Batch
        {
            typedef std::set< Agent * > set_type;
            set_type m_callbacks;
        };
        
    public:
        using typename base_type::object_type;
        
        struct Listener : object_type
        {
            Listener( Agent & );
            Listener(const Listener &) = delete;
            Listener & operator=(const Listener &) = delete;
            
            virtual ~Listener();
            
        private:
            Agent & m_agent;
        };
        
        emitter();
		virtual ~emitter();
        
		Listener * on( event_type, function_type );
        Listener * once( event_type, function_type );

        bool remove_all_listeners();
        bool remove_all_listeners( event_type );
        
        virtual void emit( event_type );
      
	private:
        
        void removeAllListeners();

        void removeListener( Listener );
        
        
       //const Batch listeners( event_type );
        
        Listener addListener( event_type, function_type );
        
        
	//	typedef std::map< key_type, pair< Batch, Batch > > map_type;
    //	map_type m_batches;
    };

}	// om636

#include "emitter.hxx"
#endif // __EMITTER_H__JhLAPnS3Wp842MtFlNU59YkvsoQyIR