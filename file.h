#ifndef FILE_H
#define FILE_H
//#############################################################################


#include <iostream>
#include <fstream>
#include <string>

namespace NS_FILE
{
	//===================================================
	class File
	{
		public:
		bool SaveToFile(const std::string& filename, const std::string& data);
	};	
	//===================================================
}


//#############################################################################
#endif