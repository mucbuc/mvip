#ifndef PERSISTANT_H_INCLUDE_GUARD_543543HHGH
	#define PERSISTANT_H_INCLUDE_GUARD_543543HHGH

#include <om636/create/singleton.h>

#include <fstream>
#include <sstream>

namespace om636
{
    template<class T> 
    class persistant_raw
    {
    public:
        
        // types
        typedef T storage_type; 
        typedef typename storage_type::iterator iterator; 
     
        const storage_type & storage() const;
        storage_type & storage();

        persistant_raw();
        virtual ~persistant_raw();
    
    protected:
        
        void read(const char *);
        void write(const char *);
        
    private:

        storage_type m_storage;
        
        // undefined
        persistant_raw( const persistant_raw & );
        persistant_raw & operator=(persistant_raw);
    };
    
    template<class T>
    class persistant
    : public persistant_raw< T >
    {
    public:
        typedef persistant_raw< T > base_type;
        
        persistant();
        virtual ~persistant();
        
        void open( const char * );
    
    private:
        using base_type::read;
        using base_type::write;
        
        std::string m_path;
    };
    
}   // om636

#include "persistant.hxx"

#endif // __PERSISTANT_H_INCLUDE_GUARD_543543HHGH
