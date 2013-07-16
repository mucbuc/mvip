#ifndef LAMBDA_FWD_H__GzE18nvZyhQmq7oVL5NHJ63bdIucK0
#define LAMBDA_FWD_H__GzE18nvZyhQmq7oVL5NHJ63bdIucK0

#include <ctime>
#include <stdint.h>

namespace om636
{
    // batch.h
	template<class, class> struct batch_layer;

    // fact.h
    template<typename T, typename U = int32_t, typename V = time_t> class fact;
    
    // serving.h
	template<class> struct serving_layer; 
	template<class> struct batch_view;
		
    // speed.h
	template<class> struct speed_layer; 
	template<class> struct real_time_view;
    
    // query.h
    struct query;
    
    // lambda.h
    template<class, template<class> class> class lambda;
}

#endif // LAMBDA_FWD_H__GzE18nvZyhQmq7oVL5NHJ63bdIucK0