namespace om636
{
    // interface.h
    template<class, template<class> class>
    class context;
    
    template<class>
    struct forward_policy;

    // default_subject.h
    namespace default_subject
    {
        template<class> struct policy;
        template<class> struct traits;
    }
}
