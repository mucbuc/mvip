/*
    similar to observer but few different constraits:
 
 1. a listener can be detached at any moment. (this makes map a bit cumbersome because the container has to be modifiable while traversal)
 2. no assumption can be made about the order of listeners updated 
 3.
 
 
 
 
 1. all attached observers must be updated (except for counter_subject)
 2. all detached observers must not be updated
 3. observers receive updates in the order that they where attached
 4. an observer can be detached multiple times
 */

#ifndef EMITTER_H__JhLAPnS3Wp842MtFlNU59YkvsoQyIR
#define EMITTER_H__JhLAPnS3Wp842MtFlNU59YkvsoQyIR

#include <map>
#include <vector> 

namespace om636
{
    template<class T, class U, template<class> class V>
	class EventEmitter
    : private V< EventEmitter<T, U, V> > 
	{
        typedef T event_type;
        typedef U function_type;
    
        struct Listener
        {
            Listener( function_type, EventEmitter & );
            ~Listener();
            
            void operator()() const;
            void operator()();
            
        private:
            
            function_type m_call;
            EventEmitter * m_emitter;
            
            Listener( const Listener & ) = delete;
            Listener & operator=(const Listener &) = delete;
        };
        
    public:
		
        EventEmitter();
		virtual ~EventEmitter();
		virtual void emit( event_type ); 
	
		Listener * on( event_type, function_type );
        Listener * addListener( event_type, function_type );
        Listener * once( event_type, function_type );
        
        void removeListener( event_type, Listener * );
        void removeListener( Listener * );
        void removeAllListeners();
        
        std::vector< Listener * > listeners( event_type );
        
	private:
    
#if 0
        typedef std::map< key_type, U > id_map_type;
     	typedef std::map< event_type, id_map_type > map_type;
        typedef typename map_type::iterator iterator;
        map_type m_listeners;
#endif 
    };
/*

problem: 
	each element in U needs to be paired with a keytype. key_type is currently hardcoded
	to be the memory adress of the listener (this should be a policy, ok for now). so what i need is: 
	
	tuple< map< listener *, U<0> >, map< listener *, U<1> >, map< listener *, U<2> >.... U<N> >
	
	then when destroying listeners i need to search each map in the tuple for the listener.
option: 
	instead of storing an emitter reference in the listener and having it do all the work, templatize
	the listener to access the container directly and erase itself. but is dangerous, the emitter knows 
	what state the containers are in, if traversing or not. the listener and container don't know 
	anything. the design should be a hierarchy of observer patters. 
	
missing counter part: 
	the sujbect: 
	
class subject
{
	add( listener * )	
	remove( listener * ); 
	traverse(); 
}; 		

then the whole thing turns into

tuple< subject< U<0> >, subject< U<1> >, subject< U<2> >.... U<N> > 

and the "on" registration function dispatches to the correct subject, which from then on will never 
be explicitly refrenced by the client. the whole thing seems to be similar/layer higher to the observer
pattern. the main difference is that the callback can be any object and the listener only determines the 
life time of the callback. the observer on the other hand requires a derived object with a specific
interface. 



maybe todo: 
- at listener destruction the user could provide an optional short cut, the type of call back, 
 	which could help the lookup. 
	
- implement alternative identification policy. not based on pointer??? 
	
//	i need to associate each handler with a key_type
//	if U is tuple then i need to asociate 

design: 
	count handles to abstract_listener and delete event_handler if refcount == 0 
usage: 

1 ) 
	emitter< std::string, std::tuple< loki::functor, my_functor, void(*)() > > a;
	
	a.on( "error", & global_exit ); 						
	a.emit( "error ); 	// ==> nothing happens. & global_exit already got "popped". 
	
	auto listener = a.on( "error", & global_exit ); 
	a.emit( "error ); 	// ==> this time calls global_exit.
	
	a.on( "error", functor( & local::exit, local_obj ) ); 
	

2) 
	emitter< std::string, std::tuple< loki::functor, my_functor, void(*)() > > a;
	
	void func()
	{
		listener out( a.on( "error", & global_exit ) ); 

		...
		
		a.emit( "error" );	// ==> global_exit 	
		
	}	


*/ 
	
	
}	// om636

#include "emitter.hxx"
#endif // __EMITTER_H__JhLAPnS3Wp842MtFlNU59YkvsoQyIR