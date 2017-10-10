#pragma once
#include <string>
class managedPatcher
{
private:
	std::string _slimeFolderPath;
	std::string _currentDirectory;
public:
	managedPatcher(std::string slimeFolderPath, std::string currentDirectory);
	~managedPatcher();
};

