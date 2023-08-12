#pragma once

#include <string>
#include <fstream>

namespace GT {

	enum class OpenFileMode : uint32_t
	{
		Input_OPM = 0, Output_OPM = 1
	};
	void OpenFile(std::fstream& file, const std::string& filepathToProject, const std::string& projectName, const std::string& filepathToAdd, const std::string fileName, OpenFileMode openFileMode);

}