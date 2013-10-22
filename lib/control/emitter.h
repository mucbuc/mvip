/*

 */

#ifndef emitter_H__JhLAPnS3Wp842MtFlNU59YkvsoQyIR
#define EMITTER_H__JhLAPnS3Wp842MtFlNU59YkvsoQyIR

#include <map>
#include <set>
#include <memory>
#include <mutex>
#include <algorithm>

#include <om636/lib/containers/queue.h>

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
        typedef om636::queue< std::function<void()> > queue_type;
        
        struct Agent
        {
            Agent( function_type );
            void cancel();
            bool is_canceled();
            function_type callback();
        
        private:
            bool m_cancel;
            function_type m_callback;
        };
        
        typedef std::set< Agent * > batch_type;
        typedef std::map< event_type, batch_type > map_type;
        
        static void include( batch_type &, batch_type & );
        static void process( batch_type & );
        
        template<typename W>
        static void process( batch_type &, W );
        
        static void remove_all( batch_type & );
        static void remove_all( map_type & );
        
        void pop_events( std::function<void()> ); 
        
        map_type m_repeaters, m_singles;
        queue_type m_queue;
        bool m_traversing;
        
        typedef std::mutex mutex_type;
        mutex_type m_mutex;
        
    public:
        
        using typename base_type::object_type;
        
        struct Listener : base_type::object_type
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

        void remove_all_listeners();
        void remove_all_listeners( event_type );
        
        void emit( event_type );
    
        template< typename W >
        void emit( event_type, W );
    };

}	// om636

#include "emitter.hxx"
#endif // __EMITTER_H__JhLAPnS3Wp842MtFlNU59YkvsoQyIR