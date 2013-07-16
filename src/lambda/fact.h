#ifndef FACT_H__LI9K3dOVQCSmq2pPcebrA6o5f7y8jx
#define FACT_H__LI9K3dOVQCSmq2pPcebrA6o5f7y8jx

#include <om636/lambda/lambda_fwd.h>

namespace om636
{
    template<typename T, typename U, typename V>
    class fact
    {
    public:  
        typedef T data_type;
        typedef U id_type;
        typedef V time_type;
        
        fact();
        ~fact(); 

    	const time_type & time() const;
    	time_type & time();
        
    	const id_type & id() const;
        id_type & id();
        
    	const data_type & data() const;
        data_type & data();
        
        bool operator<(const fact &) const; 
        
    private: 
    	time_type m_time; 
    	id_type m_id; 
    	data_type m_data; 
    };
    
	template<typename S, typename T, typename U, typename V> 
	S & operator>>(S &, fact< T, U, V > & ); 
	
	template<typename S, typename T, typename U, typename V> 
	S & operator<<(S &, const fact< T, U, V > & ); 

}   // om636

#include "fact.hxx"
#endif // FACT_H__LI9K3dOVQCSmq2pPcebrA6o5f7y8jx