/* 
 objective: context policy for lambda architecture
 
 note: 
    i'm starting to think i need to take the container_type to the next level of "model_type", 
 the differnece is that you could something like this with a model. a[ apended( after( yesterday() ) ) ].traverse( f ); 
 i.e incremental view, in terms of siulations it would be age and previous time slice 
 
*/

#ifndef LAMBDA_H__sqIC9DQdhkz1nfOLYW2eiJXH4mFlwV
#define LAMBDA_H__sqIC9DQdhkz1nfOLYW2eiJXH4mFlwV

#include <om636/lambda/lambda_fwd.h>
#include <om636/components/context.h>

namespace om636
{
    template<class T, template<class> class U>
    struct lambda
    : public U< lambda< T, U > >
	{
        // feedback policy
        typedef U< lambda< T, U > > fbp;

        typedef T container_type;
        typedef typename container_type::value_type value_type;
        typedef context< value_type, speed_layer > speed_type;
        typedef context< container_type, serving_layer > serving_type;
        typedef batch_layer< container_type, serving_type > batch_type;
        
        void insert( value_type );
        void process();

        speed_type & speed();
        const speed_type & speed() const;
        
        serving_type & serving();
        const serving_type & serving() const;
    
        batch_type & batch();
        const batch_type & batch() const;
        
    private:
        batch_type m_batch;
        serving_type m_serving;
        speed_type m_speed;
    };
}

#include "lambda.hxx"
#endif // __LAMBDA_H__sqIC9DQdhkz1nfOLYW2eiJXH4mFlwV