
#include <om636/lib/control/emitter.h>

#include <cassert>
#include <string>
#include <iostream>


struct test_base
{
    virtual ~test_base() {
        destructor_called = true;
    }
    
    static bool destructor_called;
};

bool test_base::destructor_called( false );

template<typename T>
struct test_emitter_policy
{
    typedef test_base object_type;
};

void nop() {}

void check_destructor() {

    using namespace std;
    using namespace om636;
    typedef emitter< string, function<void()> , test_emitter_policy > emitter_type;
    typedef typename emitter_type::Listener listener_type;
    
    emitter_type e;
    
    {
        listener_type l( e.on( string(""), nop ));
    }
    
    assert( test_base::destructor_called );
    cout << "destructor test passed" << endl;
}

int main() {
    
    using namespace std;
    using namespace om636;
    
    check_destructor();
    return 0;
}


