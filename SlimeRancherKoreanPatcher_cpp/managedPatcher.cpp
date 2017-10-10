#include "stdafx.h"
#include "managedPatcher.h"
#include <iostream>


managedPatcher::managedPatcher(std::string slimeFolderPath, std::string currentDirectory)
	:_slimeFolderPath(slimeFolderPath), _currentDirectory(currentDirectory)
{
	std::cout << _slimeFolderPath << std::endl;
	std::cout << _currentDirectory << std::endl;
}


managedPatcher::~managedPatcher()
{
}
