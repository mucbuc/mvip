
namespace om636
{
    namespace complex_private
    {
        template<class> struct not_factored;	// could be unit, unknown
        template<class> struct m_unit;			// -1 or 1 
        template<class> struct factored;		// 
        
        template<class T>
        class complex_subject
            : public T
        {	
            // types
            typedef T subject_type;
            typedef number< complex< subject_type > > num_type;
            typedef abstract_number< num_type > * value_type;
            
        public:			

            // resources
            complex_subject();
            complex_subject(const complex_subject &);
            complex_subject(const subject_type &);
            ~complex_subject();
            complex_subject & operator=(complex_subject); 
            void swap(complex_subject &); 
            
            // policy 
            void on_swap(const value_type &, const value_type &);
        };

        template<class T>
        void swap(complex_subject<T> &, complex_subject<T> &); 

    } 	// complex_private 

    /////////////////////////////////////////////////////////////////////////////////////////////
    // complex<T>
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    typename complex<T>::impl_type * complex<T>::evaluate() const 
    {	return const_cast< complex<T> & >(*this).evaluate();	}

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    typename complex<T>::impl_type * complex<T>::evaluate()
    {
        typedef typename type_at<list_type, 0>::result_type::value_type value_type;
        return & complex_private::factored<num_type>::instance();
    }

    using om636::type_at;

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T> 
    complex<T>::complex()
        : context_type( & complex_private::not_factored<num_type>::instance() )
    {}

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T> 
    complex<T>::complex(const complex & c)
        : context_type( dynamic_cast<const context_type &>(c) )
    {} 

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T> 
    complex<T>::complex(const value_type & c)
        : context_type( & complex_private::not_factored<num_type>::instance(), c)
    {}	

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T> 
    complex<T>::~complex()
    {}

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T> 
    void complex<T>::swap( complex & a )
    {	context_type::swap( a ); }
   
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    typename complex<T>::real_type & complex<T>::real()
    {   return subject_ref()[index<0>()];   }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    const typename complex<T>::real_type & complex<T>::real() const
    {   return subject_ref()[index<0>()];   }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    typename complex<T>::imaginary_type & complex<T>::imaginary()
    {   return subject_ref()[index<1>()];   }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    const typename complex<T>::imaginary_type & complex<T>::imaginary() const
    {   return subject_ref()[index<1>()];   }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    bool complex<T>::equal(const num_type & lhs, const num_type & rhs) const 
    {	return value_ref()->equal(lhs, rhs);	}

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    int complex<T>::sign(const num_type & lhs, const num_type & rhs) const
    {	return value_ref()->sign( lhs, rhs ); 	}

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    int complex<T>::sign(const num_type & n) const 
    {	return value_ref()->sign(n);	}

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void complex<T>::add(num_type & lhs, const num_type & rhs) const
    {	value_ref()->add(lhs, rhs); }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void complex<T>::subtract(num_type & lhs, const num_type & rhs) const 
    {	 value_ref()->subtract(lhs, rhs); }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void complex<T>::mult(num_type & lhs, const num_type & rhs) const 
    {	value_ref()->mult(lhs, rhs); }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void complex<T>::divide(num_type & lhs, const num_type & rhs) const
    {	value_ref()->divide(lhs, rhs); 	}

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void complex<T>::remainder(num_type & lhs, const num_type & rhs) const 
    {	value_ref()->remainder( lhs, rhs ); }
        
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    template<class U>
    const U & complex<T>::identity()
    {
        static U local(1);
        return local;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    template<class U, class V>
    U complex<T>::assign(const V & v)
    {	
    #if 0	
        return T( std::abs(v) > 1 ? v : 1 / v, 1);
    #else	
        #define TYPEAT(i) typename type_at<list_type, i>::result_type
        return U( TYPEAT(0)(v), TYPEAT(1)(1) );
        #undef TYPEAT
    #endif 
    } 

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    template<class U>
    void complex<T>::invert(U & _m)
    {	
        using std::swap;
        swap( _m.real(), _m.imaginary() ); 	
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    template<class U, class V>
    U complex<T>::to_value(const V & _m)
    {
        U result( V::template to_value<U>( _m.real() ) );
        result /= V::template to_value<U>( _m.imaginary() ); 
        return result; 
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void complex<T>::power(T &, const T &)
    {}

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void swap( complex<T> & lhs, complex<T> rhs )
    {	lhs.swap(rhs);	}

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    T & operator>>(T & s, number< complex< U > > & n)
    { 	
        typedef typename type_at<typename complex<U>::list_type, 0>::result_type::value_type value_type;

        if (s)
        {
            value_type temp;
            s >> temp;
            n = number< complex< U > >( temp );
        }

        return s;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U>
    T & operator<<(T & s, const number< complex< U > > & n)
    { 
        typedef typename type_at<typename complex<U>::list_type, 0>::result_type::value_type value_type;
        
        if (s)
            s << n.template to_value<value_type>(); 
        return s; 
    }

    namespace complex_private
    {
        template<class T>
        struct not_factored : public abstract_number< T >
        {
            // types 
            typedef abstract_number<T> base_type;
            typedef typename base_type::value_type value_type; 
           
            static not_factored & instance()
            {
                return singleton<not_factored, default_lifetime<not_factored>, create_new<not_factored> >::instance();
            }
            
            // comparisons
            bool equal(const value_type & lhs, const value_type & rhs) const 
            { 	return true; }
            
            int sign(const value_type & lhs, const value_type & rhs) const
            {   return -1; }
            
            int sign(const value_type & n) const
            {
                return -1; 
            }
            
            // modifiers
            void add(value_type & lhs, const value_type & rhs) const
            {
            }
            
            void subtract(value_type & lhs, const value_type & rhs) const
            {
            }
            
            void mult(value_type & lhs, const value_type & rhs) const
            { 	
            }
            
            void divide(value_type & lhs, const value_type & rhs) const
            { 	
            }
            
            void remainder(value_type &, const value_type &) const
            {}
        }; 

        // m_unit
        template<class T>
        struct m_unit : public abstract_number< T > 
        {
            // types 
            typedef abstract_number<T> base_type;
            typedef typename base_type::value_type value_type; 
            
            static m_unit & instance()
            {
                return singleton<m_unit, default_lifetime<m_unit>, create_new<m_unit> >::instance();
            }
            
            // comparisons
            bool equal(const value_type & lhs, const value_type & rhs) const 
            { 	
                rhs.evaluate();
                return 	lhs.real() == rhs.real() 
                    &&	lhs.imaginary() == rhs.imaginary();
            } 
            
            int sign(const value_type & lhs, const value_type & rhs) const
            {	
                return -1;
            }
            
            int sign(const value_type & n) const
            { 	
                return sign( n.real() );   
            }
                
            // modifiers
            void add(value_type & lhs, const value_type & rhs) const
            {
             }
            
            void subtract(value_type & lhs, const value_type & rhs) const
            {
             }
            
            void mult(value_type & lhs, const value_type & rhs) const
            {	
            }
            
            void divide(value_type & lhs, const value_type & rhs) const
            {	mult(lhs, rhs); }
            
            void remainder(value_type &, const value_type &) const
            {}
        }; 
        
        // 
        template<class T>
        struct factored : public abstract_number< T > 
        {
            // types 
            typedef abstract_number<T> base_type;
            typedef typename base_type::value_type value_type; 
            
            static factored & instance()
            {
                return singleton<factored, default_lifetime<factored>, create_new<factored> >::instance();
            }
            
            // comparisons
            bool equal(const value_type & lhs, const value_type & rhs) const 
            { 
                rhs.evaluate();
                return 		lhs.real() == rhs.real() 
                        && 	lhs.imaginary() == rhs.imaginary();
            }
            
            int sign(const value_type & lhs, const value_type & rhs) const
            { 
                return -1;
            }
            
            int sign(const value_type & n) const 
            {	
                return sign( n.real() ); 
            } 
            
            // modifiers
            void add(value_type & lhs, const value_type & rhs) const
            { 
            }
            
            void subtract(value_type & lhs, const value_type & rhs) const
            {
            }
            
            void mult(value_type & lhs, const value_type & rhs) const
            {
            }
                        
            void divide(value_type & lhs, const value_type & rhs) const 
            {
            }
            void remainder(value_type &, const value_type &) const {}
        }; 

        // subject

        /////////////////////////////////////////////////////////////////////////////////////////////
        // complex_subject<T>
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        complex_subject<T>::complex_subject() 
            : T() 
        {}

        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        complex_subject<T>::complex_subject(const complex_subject & c) 
            : T( dynamic_cast< const subject_type & >(c) ) 
        {}
            
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        complex_subject<T>::complex_subject(const subject_type & c) 
            : T(c) 
        {} 
            
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        complex_subject<T>::~complex_subject() 
        {}

        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        complex_subject<T> & complex_subject<T>::operator=(complex_subject c) 
        {	
            swap(c); 
            return *this; 
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void complex_subject<T>::swap(complex_subject & c) 
        { 	T::swap(c); } 
      
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void swap(complex_subject<T> & lhs, complex_subject<T> & rhs)
        {	lhs.swap( rhs );	}

        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void complex_subject<T>::on_swap(const value_type &, const value_type & )
        {}
    } // complex_private 
}   // om636
