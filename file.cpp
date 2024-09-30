#include "file.h"

namespace NS_FILE
{
	//===================================================
	bool File::SaveToFile(const std::string& filename, const std::string& str_input)
	{
		std::ofstream file_output(filename);
		if (!file_output)
		{
			return false;
		}

		file_output << str_input;		
		file_output.close();
		
		return true;
	}
	//===================================================
}