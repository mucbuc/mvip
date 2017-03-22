/* 
design:
	multiple calls to detach should be ok (i think, why?)
*/ 

#ifndef PRESENTER_H__3lGF6XdngzyLbrkU7mQVA9ai5u1Tqj
#define PRESENTER_H__3lGF6XdngzyLbrkU7mQVA9ai5u1Tqj

#include <lib/sense/src/subject.h>

namespace om636 
{
	namespace mvip
	{
		template<class T, template<class> class U>
		struct Basic_Presenter
		: safe_subject< basic_subject< T, U > >
		{
			typedef safe_subject< basic_subject< T, U > > base_type;
			using base_type::attach;
			using base_type::detach;
			using typename base_type::observer_type;
			using base_type::observers;
            using typename base_type::context_type;

			virtual ~Basic_Presenter() = default;
		};
	} 	// mvip
}	// om636


#include "presenter.hxx"
#endif // PRESENTER_H__3lGF6XdngzyLbrkU7mQVA9ai5u1Tqj


// template<class T, template<typename> class U> 
// struct Presenter
// {
// 	typedef T model_type; 
// 	typedef U< Presenter > view_type; 

// 	virtual ~Presenter() = default;
	
// 	virtual model_type & model() = 0;
// 	virtual const model_type & model() const = 0; 

// 	virtual void attach( view_type & ) = 0; 
// 	virtual void detach( view_type & ) = 0; 
// };
