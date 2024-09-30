#ifndef TIME_H
#define TIME_H
//#############################################################################


#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

namespace NS_TIME
{
	//===================================================
	class DateTime
	{
		public:
		std::string GetCurrentDateTime(const std::string& format);		// "%Y-%m-%d %H:%M:%S"	
	};	
	//===================================================
}


//#############################################################################
#endif