
#include <om636/lib/control/emitter.h>

#include <cassert>
#include <string>
#include <iostream>


template<typename T>
struct test_emitter_policy
{
    struct test_base
    {
        virtual ~test_base() {
            destructor_called = true;
        }
        
        static bool destructor_called;
    };
    
    typedef test_base object_type;
};

template<typename T>
bool test_emitter_policy<T>::test_base::destructor_called( false );

void check_destructor() {

    using namespace std;
    using namespace om636;
    typedef function<void()> function_type;
    typedef emitter< string, function_type , test_emitter_policy > emitter_type;
    typedef typename emitter_type::Listener listener_type;
    
    emitter_type e;
    
    {
        listener_type l( e.on( string(""), function_type() ));
    }
    
    assert( listener_type::destructor_called );
    cout << "emitter: destructor test passed" << endl;
}

int main() {
    
    using namespace std;
    using namespace om636;
    
    check_destructor();
    return 0;
}


