#ifndef UTIL__INCLUDE_GUARD__
#define UTIL__INCLUDE_GUARD__

#include <iostream>
#include <ctime>
#include <map>

#define PROFILING_ENABLED false 

namespace toolbag
{
    using namespace std;
    
	class timer
	{
		clock_t sInitial, sSum;
		bool paused;

	public:

		timer(bool p = false)
			: paused( p )
		{	reset(); 	}

		timer( const timer& c )
			: sSum ( c.sSum )
			, sInitial( c.sInitial )
			, paused( c.paused )
		{}

		void reset()
		{
			sInitial = clock();
			sSum = 0;
		}
		
		void pause()
		{
			if (!paused)
			{
				sSum += clock() - sInitial;
				paused = true;
			}
		}
				
		void resume()
		{
			if (paused)
			{
				sInitial = clock();
				paused = false;
			}
		}
		clock_t value() const
		{	
			return sSum + (paused ? 0 : clock() - sInitial); 
		}
	};



#if PROFILING_ENABLED

	class scope_sample;

	class scope_profile
	{
		friend class scope_sample;

		const char* name;
		unsigned hits;
		timer total, sub_total;
		std::map<const char*, timer> sub_scopes;

		void dump()
		{
			cout << "============================================================" << endl 
			<< 	"	scope		: " << name << endl 
			<< 	"	hits		: " << hits << endl 
			<< 	"	total time	: " << total.value() << endl;
			if (sub_scopes.size())
			{
				cout 
				<< 	" 	sub scope time 	: " << sub_total.value() << endl
				<< 	" 	sub scope count : " << sub_scopes.size() << endl;
				for (	std::map<const char*, timer>::iterator i( sub_scopes.begin() ); 
						i != sub_scopes.end(); 
						i++ )
				{
					cout << "	'" << (*i).first << 
					"' time	: " << (*i).second.value() << endl;
				}
			}
			cout << "============================================================" << endl;
		}

		public:
		scope_profile( const char* n )
			: name( n )
			, hits( 0 )
			, sub_total( true )
			, total( false )
		{}

		~scope_profile()
		{ 	dump(); }	
		};

		class scope_sample
		{
			scope_profile* super_scope;
			static scope_profile* current_scope;
			timer total;

		public:
			scope_sample( scope_profile& p )
				: super_scope( current_scope )
			{
				current_scope = &p;
				current_scope->total.resume();
				
				if (super_scope)
				{
					super_scope->sub_scopes[ current_scope->name ].resume();
					super_scope->sub_total.resume();
				}
			}

			~scope_sample()
			{
				if (super_scope)
				{
					super_scope->sub_scopes[ current_scope->name ].pause();
					super_scope->sub_total.pause();
				}

				current_scope->total.pause();
				current_scope->hits++;
				current_scope = super_scope;
			}
		};

	scope_profile* scope_sample::current_scope = NULL;

	#define SAMPLE_SCOPE( msg ) \
		static toolbag::scope_profile profile( msg ); \
		toolbag::scope_sample temp( profile )

	#define SAMPLE_FUNCTION	\
		static toolbag::scope_profile profile( __PRETTY_FUNCTION__ ); \
		toolbag::scope_sample temp( profile )
#else
	
	#define SAMPLE_SCOPE( msg )
	#define SAMPLE_FUNCTION

#endif 

}

#endif // __UTIL__INCLUDE_GUARD__