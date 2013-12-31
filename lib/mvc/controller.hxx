template<typename T, template<typename> typename U>
basic_controller<T, U>::basic_controller( const model_type & m )
: m_views()
, m_model( m )
{}

template<typename T, template<typename> typename U>
void basic_controller<T, U>::attach( const view_type & v )
{
	registration_policy::attach( v, m_views );
} 

template<typename T, template<typename> typename U>
void basic_controller<T, U>::detach( const view_type & v )
{
	registration_policy::detach( v, m_views );
}

template<typename T, template<typename> typename U>
void basic_controller<T, U>::write( const model_type & m )
{
	dispatch_polcicy::write( m_model, m, views );
}

template<typename T, template<typename> typename U>
auto basic_controller<T, U>::read() -> const model_type &
{
	return dispatch_polcicy::read( m_model, views );
}
	