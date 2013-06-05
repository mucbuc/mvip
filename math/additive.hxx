
namespace om636
{
    namespace additive
    {
        // unknown_state
        template<class T>
        struct unknown_state
        : public value_observer< typename T::policy_type >
        {
            // types
            typedef T context_type;
            typedef value_observer< typename T::policy_type > subject_policy;
            using subject_policy::unknown;
            using subject_policy::zero;
            using subject_policy::negative;
            using subject_policy::evaluate;
            using subject_policy::pos_ref;
            using subject_policy::neg_ref;
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
        
        // zero_state
        template<class T>
        struct zero_state
        : public value_observer< typename T::policy_type >
        {
            // types
            typedef T context_type;
            typedef value_observer< typename T::policy_type > subject_policy;
            using subject_policy::unknown;
            using subject_policy::zero;
            using subject_policy::positive;
            using subject_policy::negative;
            using subject_policy::evaluate;
            using subject_policy::pos_ref;
            using subject_policy::neg_ref;
            using subject_policy::on_swap; 
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
        
        // positive_state
        template<class T>
        struct positive_state
        : public value_observer< typename T::policy_type >
        {
            // types
            typedef T context_type;
            typedef value_observer< typename T::policy_type > subject_policy;
            using subject_policy::unknown;
            using subject_policy::zero;
            using subject_policy::negative;
            using subject_policy::evaluate;
            using subject_policy::pos_ref;
            using subject_policy::neg_ref;
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
        
        // negative_state
        template<class T>
        struct negative_state
        : public value_observer< typename T::policy_type >
        {
            // types
            typedef T context_type;
            typedef value_observer< typename T::policy_type > subject_policy;
            using subject_policy::unknown;
            using subject_policy::zero;
            using subject_policy::positive;
            using subject_policy::negative;
            using subject_policy::evaluate;
            using subject_policy::pos_ref;
            using subject_policy::neg_ref;
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

        #pragma mark - policy
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // policy<T>
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        template<class V>
        typename policy<T>::value_type policy<T>::on_init(V &)
        {
            return std::make_tuple( 0, 0, zero() );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        template<class V, class W>
        typename policy<T>::value_type policy<T>::on_init(V & s, const W & init)
        {
            using std::make_tuple;
            
            if (init > 0)
                return make_tuple( init, 0, positive() );
            else if (init < 0)
                return make_tuple( 0, -init, negative() );
            return on_init(s);
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        template<class V>
        V policy<T>::to_value(const context_type & t)
        {
            const int & _sign( sign(t) );
            if (_sign == 1)
                return t.template converter<V>( pos_ref( t ) );
            if (_sign == -1)
                return -t.template converter<V>( neg_ref( t ) );
            return 0;
        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        typename policy<T>::positive_type & policy<T>::pos_ref(context_type & t)
        {   return std::get<0>(t.value_ref());  }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        const typename policy<T>::positive_type & policy<T>::pos_ref(const context_type & t)
        {   return std::get<0>(t.value_ref());  }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        typename policy<T>::negative_type & policy<T>::neg_ref(context_type & t)
        {   return std::get<1>(t.value_ref());  }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        const typename policy<T>::negative_type & policy<T>::neg_ref(const context_type & t)
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
            if (pos_ref(value) == neg_ref( value ))
            {
                pos_ref(value) = neg_ref(value) = 0;
                state(value) = zero();
            }
            else if (pos_ref(value) > neg_ref(value))
            {
                pos_ref(value) -= neg_ref(value);
                neg_ref(value) = 0;
                state(value) = positive();
            }
            else
            {
                neg_ref(value) -= pos_ref(value);
                pos_ref(value) = 0;
                state(value) = negative();
            }
            
            return state(value);
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        typename policy<T>::observer_type * policy<T>::evaluate(const context_type & value)
        {   return evaluate( const_cast< context_type & >(value ) );   }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        typename policy<T>::observer_type * policy<T>::unknown()
        {
            typedef unknown_state<context_type> state_type;
            return & singleton<state_type, default_lifetime<state_type>, create_new<state_type> >::instance();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        typename policy<T>::observer_type * policy<T>::zero()
        {
            typedef zero_state<context_type> state_type;
            return & singleton<state_type, default_lifetime<state_type>, create_new<state_type> >::instance();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        typename policy<T>::observer_type * policy<T>::positive()
        {
            typedef positive_state<context_type> state_type;
            return & singleton<state_type, default_lifetime<state_type>, create_new<state_type> >::instance();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        typename policy<T>::observer_type * policy<T>::negative()
        {
            typedef negative_state<context_type> state_type;
            return & singleton<state_type, default_lifetime<state_type>, create_new<state_type> >::instance();
        }
        
#pragma mark - unknown_state
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // unknown_state
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        bool unknown_state<T>::on_equal(const context_type & lhs, const context_type & rhs) const
        {   return evaluate( lhs )->on_equal(lhs, rhs);  }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        int unknown_state<T>::on_cmp(const context_type & lhs, const context_type & rhs) const
        { 	return evaluate( lhs )->on_cmp(lhs, rhs);	}
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        int unknown_state<T>::on_sign(const context_type & n) const
        { 	return evaluate( n )->on_sign( n ); }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void unknown_state<T>::on_add(context_type & lhs, const context_type & rhs) const
        {
            pos_ref(lhs) += pos_ref( rhs );
            neg_ref(lhs) += neg_ref( rhs );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void unknown_state<T>::on_subtract(context_type & lhs, const context_type & rhs) const
        {
            pos_ref(lhs) += neg_ref( rhs );
            neg_ref(lhs) += pos_ref( rhs );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void unknown_state<T>::on_mult(context_type & lhs, const context_type & rhs) const
        {   evaluate( lhs )->on_mult(lhs, rhs); }

        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void unknown_state<T>::on_divide(context_type & lhs, const context_type & rhs) const
        { 	evaluate( lhs )->on_divide(lhs, rhs); }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void unknown_state<T>::on_remainder(context_type & lhs, const context_type & rhs) const
        { 	evaluate( lhs )->on_remainder(lhs, rhs); }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void unknown_state<T>::on_inc(context_type & n) const
        {   ++pos_ref(n);    }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void unknown_state<T>::on_dec(context_type & n) const
        {   ++neg_ref(n);   }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void unknown_state<T>::on_invert(context_type & n) const
        {   std::swap( pos_ref(n), neg_ref(n) );  }
        
        #pragma mark - zero_state
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // zero_state
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        bool zero_state<T>::on_equal(const context_type & lhs, const context_type & rhs) const
        {   return ! sign( rhs );    }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        int zero_state<T>::on_cmp(const context_type & lhs, const context_type & rhs) const
        { 	return - sign( rhs );	}
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        int zero_state<T>::on_sign(const context_type &) const
        { 	return 0; }

        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void zero_state<T>::on_add(context_type & lhs, const context_type & rhs) const
        {   lhs = rhs;  }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void zero_state<T>::on_subtract(context_type & lhs, const context_type & rhs) const
        {
            lhs = rhs;
            state( lhs )->on_invert( lhs );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void zero_state<T>::on_mult(context_type & lhs, const context_type & rhs) const
        {}
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void zero_state<T>::on_divide(context_type & lhs, const context_type & rhs) const
        {}
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void zero_state<T>::on_remainder(context_type & lhs, const context_type & rhs) const
        {}
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void zero_state<T>::on_inc(context_type & n) const
        {
            ++pos_ref(n);
            state(n) = positive();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void zero_state<T>::on_dec(context_type & n) const
        {
            ++neg_ref(n);
            state(n) = negative();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void zero_state<T>::on_invert(context_type &) const
        {}
        
        #pragma mark positive_state
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // positive_state
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        bool positive_state<T>::on_equal(const context_type & lhs, const context_type & rhs) const
        {
            if (sign(rhs) > 0)
            {
                evaluate( lhs );
                evaluate( rhs );
                return pos_ref(lhs) == pos_ref( rhs );
            }
            return 0;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        int positive_state<T>::on_cmp(const context_type & lhs, const context_type & rhs) const
        {
            if (sign(rhs) > 0)
            {
                evaluate( lhs );
                evaluate( rhs );
                if (pos_ref(lhs) == pos_ref( rhs ))
                    return 0;
                else if (pos_ref(lhs) > pos_ref( rhs ))
                    return 1;
                return -1;
            }
            return 1;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        int positive_state<T>::on_sign(const context_type & n) const
        { 	return 1; }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void positive_state<T>::on_add(context_type & lhs, const context_type & rhs) const
        {
            const int & _sign( sign(rhs) );
            
            if (_sign)
            {
                if (_sign < 0)
                    state(lhs) = unknown();
                pos_ref(lhs) += pos_ref( rhs );
                neg_ref(lhs) += neg_ref( rhs );
            }
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void positive_state<T>::on_subtract(context_type & lhs, const context_type & rhs) const
        {
            const int & _sign( sign(rhs) );
            
            if (_sign)
            {
                if (_sign > 0)
                    state(lhs) = unknown();
                pos_ref( lhs ) += neg_ref( rhs );
                neg_ref( lhs ) += pos_ref( rhs );
            }
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void positive_state<T>::on_mult(context_type & lhs, const context_type & rhs) const
        {
            const int & _sign( sign(rhs) );
            if (_sign > 0)
            {
                evaluate( lhs );
                evaluate( rhs );
                pos_ref(lhs) *= pos_ref( rhs );
            }
            else if (_sign < 0)
            {
                neg_ref(lhs) = pos_ref(lhs) * neg_ref( rhs );
                pos_ref(lhs) = 0;
                state(lhs) = negative();
            }
            else
            {
                pos_ref(lhs) = 0;
                state(lhs) = zero();
            }
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void positive_state<T>::on_divide(context_type & lhs, const context_type & rhs) const
        {
            const int & _sign( sign(rhs) );
            
            ASSERT( _sign );
            
            if (_sign > 0)
            {
                evaluate(lhs);
                evaluate(rhs);
                pos_ref(lhs) /= pos_ref( rhs );
            }
            else if (_sign < 0)
            {
                neg_ref(lhs) = pos_ref(lhs) / neg_ref( rhs );
                pos_ref(lhs) = 0;
                state(lhs) = negative();
            }
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void positive_state<T>::on_remainder(context_type & lhs, const context_type & rhs) const
        {
            const int & _sign( sign(rhs) );
            
            ASSERT( _sign );
            
            if (_sign > 0)
            {
                evaluate(lhs);
                evaluate(rhs);
                
                ASSERT( pos_ref( rhs ) > 0 );
                
                pos_ref(lhs) %= pos_ref( rhs );
                state(lhs) = unknown();
            }
            else if (_sign < 0)
            {
                neg_ref(lhs) = pos_ref(lhs) % neg_ref( rhs );
                pos_ref(lhs) = 0;
                state(lhs) = negative();
            }
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void positive_state<T>::on_inc(context_type & n) const
        {
            ++pos_ref(n);
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void positive_state<T>::on_dec(context_type & n) const
        {
            state(n) = unknown();
            --pos_ref(n);
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void positive_state<T>::on_invert(context_type & n) const
        {
            std::swap( pos_ref(n), neg_ref(n) );
            state(n) = negative();
        }
        
        #pragma mark negative_state
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        // negative_state
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        bool negative_state<T>::on_equal(const context_type & lhs, const context_type & rhs) const
        {
            if (sign(rhs) < 0)
            {
                evaluate(lhs);
                evaluate(rhs);
                return neg_ref(lhs) == neg_ref( rhs );
            }
            return 0; 
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        int negative_state<T>::on_cmp(const context_type & lhs, const context_type & rhs) const
        {
            if (sign(rhs) < 0)
            {
                evaluate(lhs);
                evaluate(rhs);
                if (neg_ref(lhs) == neg_ref( rhs ))
                    return 0;
                else if (neg_ref(lhs) < neg_ref( rhs ))
                    return -1;
                return 1;
            }
            return -1;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        int negative_state<T>::on_sign(const context_type & n) const
        { 	return -1; }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void negative_state<T>::on_add(context_type & lhs, const context_type & rhs) const
        {
            const int & _sign( sign(rhs) );
            if (_sign)
            {
                if (_sign > 0)
                    state( lhs ) = unknown();
                
                pos_ref(lhs) += pos_ref( rhs );
                neg_ref(lhs) += neg_ref( rhs );
            }
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void negative_state<T>::on_subtract(context_type & lhs, const context_type & rhs) const
        {
            const int & _sign( sign(rhs) );
            if (_sign)
            {
                if (_sign < 0)
                    state(lhs) = unknown();
                
                pos_ref(lhs) += pos_ref( rhs );
                neg_ref(lhs) += neg_ref( rhs );
            }
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void negative_state<T>::on_mult(context_type & lhs, const context_type & rhs) const
        {
            const int & _sign( sign(rhs) );
            if (_sign)
            {
                evaluate(lhs);
                evaluate(rhs);
                
                if (_sign < 0)
                {
                    pos_ref(lhs) = neg_ref(lhs) * neg_ref( rhs );
                    neg_ref(lhs) = 0;
                    state(lhs) = positive();
                }
                else if (_sign > 0)
                {
                    neg_ref(lhs) *= pos_ref( rhs );
                    pos_ref(lhs) = 0;
                    state(lhs) = negative();
                }
            }
            else
                state( lhs ) = zero();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void negative_state<T>::on_divide(context_type & lhs, const context_type & rhs) const
        {
            const int & _sign( sign(rhs) );
            
            ASSERT( _sign );
            
            evaluate( lhs );
            evaluate( rhs );
            
            if (_sign < 0)
            {
                pos_ref(lhs) = neg_ref(lhs) / neg_ref( rhs );
                neg_ref(lhs) = 0;
                state(lhs) = positive();
            }
            else if (_sign > 0)
            {
                neg_ref(lhs) /= pos_ref( rhs );
                pos_ref(lhs) = 0;
                state(lhs) = negative();
            }
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void negative_state<T>::on_remainder(context_type & lhs, const context_type & rhs) const
        {
            int _sign( sign(rhs) );
            
            ASSERT( _sign );
            
            evaluate(lhs);
            evaluate(rhs);
            
            if (_sign < 0)
            {
                pos_ref(lhs) = neg_ref(lhs) % neg_ref( rhs );
                neg_ref(lhs) = 0;
                state(lhs) = positive();
            }
            else if (_sign > 0)
            {
                neg_ref(lhs) %= pos_ref( rhs );
                pos_ref(lhs) = 0;
                state(lhs) = negative();
            }
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void negative_state<T>::on_inc(context_type & n) const
        {
            state(n) = unknown();
            --neg_ref(n);
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void negative_state<T>::on_dec(context_type & n) const
        {
            ++neg_ref(n);
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void negative_state<T>::on_invert(context_type & n) const
        {
            std::swap( pos_ref(n), neg_ref(n) );
            state(n) = positive();
        }
        
    }   // additive
        
}   // om636
