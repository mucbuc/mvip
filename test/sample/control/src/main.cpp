#include <cassert>
#define ASSERT( pred ) assert( pred )

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

void check_emitter() {

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

void check_add_while_traverse()
{
    using namespace std;
    using namespace om636;
    typedef function<void()> function_type;
    typedef emitter< string, function_type , test_emitter_policy > emitter_type;
    typedef typename emitter_type::object_type object_type;
    typedef typename emitter_type::Listener listener_type;
    
    emitter_type e;
    bool second_called( 0 );
    string event("e");
    std::unique_ptr< object_type > l( e.on( event, [&]() {
        e.on( "e", [&]() {
            second_called = 1;
        } );
    } ) );
    e.emit( event );
    
    assert( !second_called );
    e.emit( event );
    assert( second_called );
}

void check_emit_while_emit()
{
    using namespace std;
    using namespace om636;
    typedef function<void()> function_type;
    typedef emitter< string, function_type , test_emitter_policy > emitter_type;
    typedef typename emitter_type::object_type object_type;
    typedef typename emitter_type::Listener listener_type;
    
    size_t counter(0);
    
    emitter_type e;
    string event("e");
    e.once( event, [&](){
        ++counter;
        e.emit( event );
    });
    
    e.emit( event );

    assert( counter == 1 );
}

void check_emit_with_args()
{
    using namespace std;
    using namespace om636;
    typedef function<void(int)> function_type;
    typedef emitter< string, function_type , test_emitter_policy > emitter_type;
    typedef typename emitter_type::object_type object_type;
    typedef typename emitter_type::Listener listener_type;
    
    emitter_type e;
    bool test_passed(0);
    string event("e");
    
    e.once( event, [&](int i){
        assert( i == 99 );
        test_passed = 1;
    } );
    
    e.emit( event, 99 ); 
    
    assert( test_passed );
}

int main() {

    check_emitter();
    check_add_while_traverse();
    check_emit_while_emit();
    check_emit_with_args();
    return 0;
}


