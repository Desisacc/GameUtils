#include "gtpch.h"
#include "GT/Utils/FileUtils.h"

#include "GT/Utils/Assert.h"

namespace GT {

	void OpenFile(std::fstream& file, const std::string& filepathToProject, const std::string& projectName, const std::string& filepathToAdd, const std::string fileName, OpenFileMode openFileMode)
	{
		const size_t indexToProjectName = filepathToProject.find(projectName);
		GT::Assert(indexToProjectName != std::string::npos, "The project :{0}, is not in filepath :{1}!", projectName.c_str(), filepathToProject.c_str());

		const std::string filepath =
			filepathToProject.substr(0, indexToProjectName + projectName.length()) + '\\' +
			filepathToAdd + fileName;

		auto openMode = openFileMode == OpenFileMode::Input_OPM ? std::ios::in : std::ios::out;
		file.open(filepath, openMode);
		if (!file.is_open())
			GT::Assert(false, "mapFile could not be opened!");
	}

}