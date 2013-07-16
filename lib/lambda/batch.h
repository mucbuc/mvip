#ifndef BATCH_H__EL9ysUBcPGz4Jj6oYMRAne2Vx1iFNS
#define BATCH_H__EL9ysUBcPGz4Jj6oYMRAne2Vx1iFNS

#include <om636/lambda/lambda_fwd.h>
#include <om636/containers/pset.h>

namespace om636
{
	template<class T, class U>
	struct batch_layer
	{
        typedef T container_type;
        typedef U serving_type;
        typedef typename container_type::value_type value_type;
        
        virtual void process( serving_type & );
        virtual void insert( value_type );

        container_type & data();
        const container_type & data() const;
        
    private:
        
        container_type m_data;
    };

}	// om636

#include "batch.hxx"
#endif // __BATCH_H__EL9ysUBcPGz4Jj6oYMRAne2Vx1iFNS