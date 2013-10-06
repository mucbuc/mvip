/*
	objective: 
		- global access to log stream
		- format log
		- open/close log file

	nice to have feature:
		- stream interface (was wasting too much time implementing)
*/

#ifndef _logger_H_8900700
	#define _logger_H_8900700

#include <om636/lib/toolbag/toolbagfwd.h>

#include <fstream>
#include <iostream>

namespace toolbag
{
	class logger
	{
		// undefined
		logger();
		logger(const logger &);
		logger & operator=(const logger & );
		
		void print_date();
		void print_time();
  		
	public:
		
		// resources
		logger( const char * file_name );
		~logger();

		// acces
		std::ofstream & out();
		const std::ofstream & out() const;
		
	private:
		mutable std::ofstream m_out;
		std::string m_filename;
	};
} //toolbag

//void PostMessageToLocalHost(const char * message);

//#include "logger.hxx"

#endif // _logger_H_8900700	