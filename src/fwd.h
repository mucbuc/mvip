namespace om636
{
    template<class>
    struct forward_policy;

    // default_subject.h
    namespace default_subject
    {
        template<class> struct policy;
        template<class> struct traits;
    }

    // interface.h
    template<class, template<class> class = default_subject::policy>
    class context;
}
