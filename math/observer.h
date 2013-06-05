#ifndef OBSERVER_H__I0WfEMGNJgydS3rDPBO9CuwlVFqoiT
#define OBSERVER_H__I0WfEMGNJgydS3rDPBO9CuwlVFqoiT

namespace om636
{
	namespace math
	{
		template<class T>
		struct observer
		{
			// types
			typedef T context_type;
			
			virtual ~observer();
			
			// comparisons
			virtual bool on_equal(const context_type &, const context_type &) const = 0;
			virtual int on_cmp(const context_type &, const context_type &) const = 0;
			virtual int on_sign(const context_type &) const = 0;
			
			// modifiers
			virtual bool on_swap(context_type &, context_type &) const = 0;
			virtual void on_add(context_type &, const context_type &) const = 0;
			virtual void on_subtract(context_type &, const context_type &) const = 0;
			virtual void on_mult(context_type &, const context_type &) const = 0;
			virtual void on_divide(context_type &, const context_type &) const = 0;
			virtual void on_remainder(context_type &, const context_type &) const = 0;
			virtual void on_inc(context_type &) const = 0;
			virtual void on_dec(context_type &) const = 0;
			virtual void on_invert(context_type &) const = 0;
		};
	}	// math
}	// om636

#include <om636/math/observer.hxx>

#endif // __OBSERVER_H__I0WfEMGNJgydS3rDPBO9CuwlVFqoiT