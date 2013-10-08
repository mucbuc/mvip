#include <cassert>
#define ASSERT( pred ) assert( pred )

#include <om636/lib/containers/stack.h>
#include <iostream>
#include <fstream>

#include "test.h"

int main(int argc, const char * argv[])
{
    
    using namespace std;
    using namespace om636;
    
    check_stack_locks<size_t>();
    check_queue_locks<size_t>();
    check_pset<void>();
    
    return 0;
}

