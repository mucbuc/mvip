#include <cassert>
#define ASSERT( pred ) assert( pred )


#include "test.h"

int main(int argc, const char * argv[])
{
    run_calculator_test<void>();
    
    return 0;
}

