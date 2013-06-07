#include <cassert>
#define ASSERT( arg ) assert( arg )

#include "test.h"

int main( int argc, char * argv[] )
{
  run_math_test<void>();
  return 0;
}
