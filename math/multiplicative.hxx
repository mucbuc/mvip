
namespace om636
{
	namespace multiplicative
	{
        // not_factored
        template<class T>
        struct not_factored_state
        : public value_observer< typename T::policy_type >
        {
            // types
            typedef T context_type;
            typedef value_observer< typename T::policy_type > subject_policy;
            
            using subject_policy::evaluate;
            using subject_policy::num_ref;
            using subject_policy::den_ref;
            using subject_policy::state;
            
            
            // comparisons
            bool on_equal(const context_type &, const context_type &) const;
            int on_cmp(const context_type &, const context_type &) const;
            int on_sign(const context_type &) const;
            
            // modifiers
            void on_add(context_type &, const context_type &) const;
            void on_subtract(context_type &, const context_type &) const;
            void on_mult(context_type &, const context_type &) const;
            void on_divide(context_type &, const context_type &) const;
            void on_remainder(context_type &, const context_type &) const;
            void on_inc(context_type &) const;
            void on_dec(context_type &) const;
            void on_invert(context_type &) const;
        };
        
        // m_unit
        template<class T>
        struct unit_state
        : public value_observer< typename T::policy_type >
        {
            // types
            typedef T context_type;
            typedef value_observer< typename T::policy_type > subject_policy;
            
            using subject_policy::not_factored;
            using subject_policy::evaluate;
            using subject_policy::num_ref;
            using subject_policy::den_ref;
            using subject_policy::state;
                        
            // comparisons
            bool on_equal(const context_type &, const context_type &) const;
            int on_cmp(const context_type &, const context_type &) const;
            int on_sign(const context_type &) const;
            
            // modifiers
            void on_add(context_type &, const context_type &) const;
            void on_subtract(context_type &, const context_type &) const;
            void on_mult(context_type &, const context_type &) const;
            void on_divide(context_type &, const context_type &) const;
            void on_remainder(context_type &, const context_type &) const;
            void on_inc(context_type &) const;
            void on_dec(context_type &) const;
            void on_invert(context_type &) const;
        };
        
        // factored
        template<class T>
        struct factored_state
        : public value_observer< typename T::policy_type >
        {
            // types
            typedef T context_type;
            typedef value_observer< typename T::policy_type > subject_policy;
            
            using subject_policy::not_factored;
            using subject_policy::num_ref;
            using subject_policy::den_ref;
            using subject_policy::state;
            using subject_policy::evaluate;
            
            // comparisons
            bool on_equal(const context_type &, const context_type &) const;
            int on_cmp(const context_type &, const context_type &) const;
            int on_sign(const context_type &) const;
            
            // modifiers
            void on_add(context_type &, const context_type &) const;
            void on_subtract(context_type &, const context_type &) const;
            void on_mult(context_type &, const context_type &) const;
            void on_divide(context_type &, const context_type &) const;
            void on_remainder(context_type &, const context_type &) const;
            void on_inc(context_type &) const;
            void on_dec(context_type &) const;
            void on_invert(context_type &) const;
        };
        
#pragma mark - policy
       
        /////////////////////////////////////////////////////////////////////////////////////////////
        // policy< T, U > 
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        template<class V> 
        typename policy<T>::value_type policy<T>::on_init(V & s)
        {
            return std::make_tuple( 0, 1, factored() );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        template<class V, class W>
        typename policy<T>::value_type policy<T>::on_init(V & s, const W & init)
        {
            using std::make_tuple;
            
            if (init != 0)
            {
                return make_tuple( init, 1, not_factored() );
            }
            return on_init( s );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        typename policy<T>::numerator_type & policy<T>::num_ref(context_type & t)
        {   return std::get<0>(t.value_ref());  }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        const typename policy<T>::numerator_type & policy<T>::num_ref(const context_type & t)
        {   return std::get<0>(t.value_ref());  }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        typename policy<T>::denumerator_type & policy<T>::den_ref(context_type & t)
        {   return std::get<1>(t.value_ref());  }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        const typename policy<T>::denumerator_type & policy<T>::den_ref(const context_type & t)
        {   return std::get<1>(t.value_ref());  }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        typename policy<T>::observer_type * & policy<T>::state(context_type & t)
        {   return std::get<2>(t.value_ref());  }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        typename policy<T>::observer_type * policy<T>::state(const context_type & t)
        {   return std::get<2>(t.value_ref());  }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        typename policy<T>::observer_type * policy<T>::evaluate(context_type & value)
        {
            if (num_ref(value) != 0)
            {
                using om636::sign;
                
                bool n_neg( sign( num_ref(value) ) == -1 );
                bool d_neg( sign( den_ref(value) ) == -1 );
                
                num_ref(value) = n_neg ? -num_ref(value) : num_ref(value);
                den_ref(value) = d_neg ? -den_ref(value) : den_ref(value);
                
                auto _gcd = gcd( num_ref(value), den_ref(value) );
           
                num_ref( value ) /= _gcd;
                den_ref( value ) /= _gcd;
                
                if (!n_neg == d_neg)
                    num_ref(value) = -num_ref(value);
            
                if (num_ref(value) == den_ref(value))
                    state( value ) = unit();
                else
                    state( value ) = factored();
            }
            else
                state( value ) = factored();
            
            return state( value );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        typename policy<T>::observer_type * policy<T>::evaluate(const context_type & value)
        {   return evaluate( const_cast< context_type & >(value ) );   }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        template<class V>
        V policy<T>::to_value( const context_type & t )
        {
            V result( t.template converter<V>( num_ref( t ) ) );
            result /= t.template converter<V>( den_ref( t ) );
            return result;
        }
                
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        typename policy<T>::observer_type * policy<T>::not_factored()
        {
            typedef not_factored_state<context_type> state_type;
            return & singleton<state_type, default_lifetime<state_type>, create_new<state_type> >::instance();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        typename policy<T>::observer_type * policy<T>::unit()
        {
            typedef unit_state<context_type> state_type;
            return & singleton<state_type, default_lifetime<state_type>, create_new<state_type> >::instance();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        typename policy<T>::observer_type * policy<T>::factored()
        {
            typedef factored_state<context_type> state_type;
            return & singleton<state_type, default_lifetime<state_type>, create_new<state_type> >::instance();
        }

#pragma mark - not_factored_state
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // not_factored_state
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        bool not_factored_state<T>::on_equal(const context_type & lhs, const context_type & rhs) const
        {   return evaluate( lhs )->on_equal(lhs, rhs);  }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        int not_factored_state<T>::on_cmp(const context_type & lhs, const context_type & rhs) const
        { 	return evaluate( lhs )->on_cmp(lhs, rhs);	}
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        int not_factored_state<T>::on_sign(const context_type & n) const
        { 	return evaluate( n )->on_sign( n ); }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void not_factored_state<T>::on_add(context_type & lhs, const context_type & rhs) const
        {   return evaluate( lhs )->on_add( lhs, rhs ); }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void not_factored_state<T>::on_subtract(context_type & lhs, const context_type & rhs) const
        {   return evaluate( lhs )->on_subtract( lhs, rhs ); }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void not_factored_state<T>::on_mult(context_type & lhs, const context_type & rhs) const
        {
            num_ref( lhs ) *= num_ref( rhs );
            den_ref( lhs ) *= den_ref( rhs );
        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void not_factored_state<T>::on_divide(context_type & lhs, const context_type & rhs) const
        {
            num_ref( lhs ) *= den_ref( rhs ); 
            den_ref( lhs ) *= num_ref( rhs );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void not_factored_state<T>::on_remainder(context_type & lhs, const context_type & rhs) const
        {}
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void not_factored_state<T>::on_inc(context_type & n) const
        {   num_ref(n) += den_ref(n);    }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void not_factored_state<T>::on_dec(context_type & n) const
        {   num_ref(n) -= den_ref(n);   }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void not_factored_state<T>::on_invert(context_type & n) const
        {
            std::swap( num_ref(n), den_ref(n) );
        }

#pragma mark - unit_state
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // unit_state
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        bool unit_state<T>::on_equal(const context_type & lhs, const context_type & rhs) const
        {
            evaluate( rhs );
            return num_ref(lhs) == num_ref(rhs) && den_ref(lhs) == den_ref(rhs);
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        int unit_state<T>::on_cmp(const context_type & lhs, const context_type & rhs) const
        {
            using om636::sign;
            return sign( lhs ) * cmp( den_ref(rhs), num_ref(rhs) );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        int unit_state<T>::on_sign(const context_type & n) const
        { 	return om636::sign( num_ref( n ) ); }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void unit_state<T>::on_add(context_type & lhs, const context_type & rhs) const
        {
            const int & _sign( om636::sign( num_ref( lhs ) ) );
            
            num_ref(lhs) = den_ref(rhs);
            if (_sign > 0)
                num_ref(lhs) += num_ref(rhs);
            else if (_sign < 0)
                num_ref(lhs) -= num_ref(rhs);
        
            den_ref(lhs) = den_ref(rhs);
            state( lhs ) = not_factored();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void unit_state<T>::on_subtract(context_type & lhs, const context_type & rhs) const
        {
            num_ref(lhs) += den_ref( rhs );
            den_ref(lhs) += num_ref( rhs );

            const int & _sign( om636::sign( num_ref( lhs ) ) );
            
            num_ref(lhs) = den_ref(rhs);
            if (_sign > 0)
                num_ref(lhs) -= num_ref( rhs );
            else if (_sign < 0)
                num_ref(lhs) += num_ref( rhs );
            
            den_ref(lhs) = den_ref( rhs );
            state( lhs ) = not_factored();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void unit_state<T>::on_mult(context_type & lhs, const context_type & rhs) const
        {
            const int & _sign( om636::sign( num_ref(lhs) ) );
            if (_sign > 0)
                num_ref(lhs) = num_ref( rhs );
            else if (_sign < 0)
                num_ref(lhs) = -num_ref( rhs );
            
            den_ref(lhs) = den_ref(rhs);
            state( lhs ) = not_factored();
        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void unit_state<T>::on_divide(context_type & lhs, const context_type & rhs) const
        { 	on_mult(lhs, rhs); }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void unit_state<T>::on_remainder(context_type & lhs, const context_type & rhs) const
        {}
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void unit_state<T>::on_inc(context_type & n) const
        {
            num_ref(n) += den_ref(n);
            state(n) = not_factored();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void unit_state<T>::on_dec(context_type & n) const
        {
            num_ref(n) = 0;
            state(n) = not_factored();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void unit_state<T>::on_invert(context_type & n) const
        {
            std::swap( num_ref(n), den_ref(n) );
        }

#pragma mark - factored_state
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // factored_state
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        bool factored_state<T>::on_equal(const context_type & lhs, const context_type & rhs) const
        {
            evaluate(rhs);
            return num_ref(lhs) == num_ref( rhs ) && den_ref(lhs) == den_ref(rhs);
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        int factored_state<T>::on_cmp(const context_type & lhs, const context_type & rhs) const
        {
            evaluate(rhs);
            if (on_equal(lhs, rhs))
                return 0;
            else if (num_ref(lhs) * den_ref(rhs) > num_ref( rhs ) * den_ref(lhs))
                return 1;
            return -1;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        int factored_state<T>::on_sign(const context_type & n) const
        { 	 return om636::sign( num_ref( n ) );  }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void factored_state<T>::on_add(context_type & lhs, const context_type & rhs) const
        {
            evaluate(rhs);
            
            if (den_ref(lhs) == den_ref(rhs))
                num_ref(lhs) += num_ref( rhs );
            else
            {
                num_ref(lhs) *= den_ref(rhs);
                num_ref(lhs) += num_ref( rhs ) * den_ref(lhs);
                den_ref(lhs) *= den_ref(rhs);
            }
            state( lhs ) = not_factored();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void factored_state<T>::on_subtract(context_type & lhs, const context_type & rhs) const
        {
            evaluate(rhs);
            
            if (den_ref(lhs) == den_ref(rhs))
                num_ref(lhs)  -= num_ref( rhs );
            else
            {
                num_ref(lhs) *= den_ref(rhs);
                num_ref(lhs) -= num_ref(rhs) * den_ref(lhs);
                den_ref(lhs) *= den_ref(rhs);
            }
            state( lhs ) = not_factored();
        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void factored_state<T>::on_mult(context_type & lhs, const context_type & rhs) const
        {
            num_ref(lhs) *= num_ref(rhs);
            den_ref(lhs) *= den_ref(rhs);
            state( lhs ) = not_factored();
        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void factored_state<T>::on_divide(context_type & lhs, const context_type & rhs) const
        {
            num_ref(lhs) *= den_ref(rhs);
            den_ref(lhs) *= num_ref(rhs);
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void factored_state<T>::on_remainder(context_type & lhs, const context_type & rhs) const
        {    }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void factored_state<T>::on_inc(context_type & n) const
        {
            num_ref(n) += den_ref(n);
            state(n) = not_factored();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void factored_state<T>::on_dec(context_type & n) const
        {
            num_ref(n) -= den_ref(n);
            state(n) = not_factored();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void factored_state<T>::on_invert(context_type & n) const
        {
            std::swap( num_ref(n), den_ref(n) );
        }

#pragma mark - non members

    } // multiplicative
    
}   // om636
        
