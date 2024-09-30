#include "time.h"

namespace NS_TIME
{	
	//===================================================
	std::string DateTime::GetCurrentDateTime(const std::string& format)
	{
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_c), format.c_str());
    return oss.str();
	}	
	
	//===================================================
}

