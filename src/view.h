#ifndef VIEW_H__0qpIVawxhQjit7UC6ES3oWvKnMAJOf
#define VIEW_H__0qpIVawxhQjit7UC6ES3oWvKnMAJOf

namespace om636
{
	namespace mvip
	{
		template<class T>
		struct basic_view 
		{
			virtual ~basic_view() = default;
		};
	}	// mvip
}	// om636

#include "view.hxx"
#endif // VIEW_H__0qpIVawxhQjit7UC6ES3oWvKnMAJOf


/*
	template<class T>
	struct basic_view 
	{
		typedef T presenter_type; 
		typedef model_type; 

		basic_view(presenter_type &); 
		virtual ~basic_view() = default;

		presenter_type & presenter_ref(); 
		const presenter_type & presenter_ref() const;

		model_type & model(); 
		const model_type & model() const; 

	private: 

		presenter_type & m_presenter;
	};

	void render();
	void simulate(); 
	void touch();

template<class T>
struct view
{
	typedef T presenter_type; 
	virtual ~view() = default;
};
*/ 
