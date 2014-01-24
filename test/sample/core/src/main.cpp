#include <om636/src/core/assert.h>

int main( int argc, char * argv[] )
{
	int i = 44;

	ASSERT( i == 44 )( i );
  	return 0;
}
