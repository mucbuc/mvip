#include <om636/lib/toolbag/logger.h>
#include <sstream>

namespace toolbag
{
	static logger gtester( "test_log.txt" ); 
    
    using namespace std;
	
	void logger::print_date()
	{
		time_t now = time(0);
	    struct tm* tm = localtime(&now);
		
		m_out 	<< "date: " << tm->tm_year + 1900  
				<< "." << tm->tm_mon + 1 
				<< "." << tm->tm_mday << std::endl;
	}

	void logger::print_time()
	{
    	time_t now = time(0);
	    struct tm* tm = localtime(&now);
		
		m_out 	<< "time: " << tm->tm_hour
				<< ":" << tm->tm_min
				<< ":" << tm->tm_sec 
				<< " clock: " << clock() << std::endl;
	}
	
	logger::logger( const char * file_name )
		: m_out( file_name, std::ios_base::app )
		, m_filename( file_name )
	{	
		//ASSERT( bool( m_out ) );
		print_date();
		print_time();
		m_out << "opened log file: " << m_filename << std::endl;
	
        stringstream temp;
        temp << "opened log file: " << m_filename;// << std::endl; 
        
      //  PostMessageToLocalHost( temp.str().c_str() );  
       // PostMessageToLocalHost( "hello" ); 
    }	

	logger::~logger()
	{ 	
		print_time();
		m_out << "closing log file: " << m_filename << std::endl;
	            
        //PostMessageToLocalHost( "logger::~logger()" );     
        
        m_out.close();
	}

	std::ofstream & logger::out() 
	{ 	return m_out; 	}

	const std::ofstream & logger::out() const
	{ 	return m_out; 	}
    
} // toolbag
