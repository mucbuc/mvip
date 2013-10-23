//
//  main.cpp
//  lambda
//
//  Created by markymark on 3/17/13.
//  Copyright (c) 2013 markymark. All rights reserved.
//


#include <cassert>
#define ASSERT( pred ) assert( pred )

#include "test_query.h"

#include <om636/lib/components/subject.h>
#include <om636/lib/containers/pset.h>
#include <om636/lib/lambda/lambda.h>
#include <om636/lib/lambda/query.h>
#include <om636/lib/lambda/fact.h>

#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <future>

template<typename T> struct tester
{
    om636::test_query< T > * m_query;
    
    void on_speed_insert_done( const T & l )
    {
        
        for (auto i( m_query->data().begin() ), e( m_query->data().end() ); i != e; ++i)
        {
            if (i->data() == "hello")
            {
                std::cout << "lambda test passed" << std::endl;
                return;
            }
        }
    
        ASSERT( !"lambda failed" );
    }
};


int main(int argc, const char * argv[])
{
    using namespace std;
    using namespace om636;
    
    typedef fact< string > data_type;
    typedef lambda< pset< data_type >, tester > lambda_type;
    
    lambda_type l;
    test_query< lambda_type > q( l );
    
    l.m_query = & q; 
    
    data_type s;
    s.data() = "hello";
    l.insert( s );
    
    std::async( & lambda_type::process, & l );
    
    return 0;
}