#include <cassert>
#include <string>
#include <iostream>

#include <om636/lib/control/emitter.h>

template<typename T>
struct test_emitter_policy
{
    struct test_base
    {
        virtual ~test_base() {
            destructor_called = true;
        }
        
        static bool destructor_called;
        static bool processor_called;
    };
    
    typedef test_base object_type;
};

template<typename T>
bool test_emitter_policy<T>::test_base::destructor_called( false );

template<typename T>
bool test_emitter_policy<T>::test_base::processor_called( false );

void check_destructor() {

    using namespace std;
    using namespace om636;
    typedef function<void()> function_type;
    typedef emitter< string, function_type , test_emitter_policy > emitter_type;
    typedef typename emitter_type::object_type object_type;
    typedef typename emitter_type::Listener listener_type;
    
    emitter_type e;
    
    {
        string event("e");
        std::unique_ptr< object_type > l( e.on( event, [&](){
            listener_type::processor_called = 1;
        } ) );
        e.emit( event );
    }
    
    assert( listener_type::destructor_called && listener_type::processor_called );
    cout << "emitter test passed" << endl;
}

int main() {
    
    check_destructor();
    return 0;
}


