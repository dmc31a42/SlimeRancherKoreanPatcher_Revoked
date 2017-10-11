#include "stdafx.h"
#include "managedPatcher.h"
#include <iostream>
#include <vector>
using namespace std;

managedPatcher::managedPatcher(string slimeFolderPath, string currentDirectory)
	:_slimeFolderPath(slimeFolderPath),
	_currentDirectory(currentDirectory),
	resAssetsFileName("resources.assets"),
	sharedAssetsFileName("sharedassets0.assets"),
	globalAssetsFileName("globalgamemanagers.assets"),
	pResAssetsFile(fopen((slimeFolderPath + resAssetsFileName).c_str(), "rb")),
	resAssetsFile(AssetsReaderFromFile, (LPARAM)pResAssetsFile),
	resAssetsFileTable(&resAssetsFile),
	pSharedAssetsFile(fopen((slimeFolderPath + sharedAssetsFileName).c_str(), "rb")),
	sharedAssetsFile(AssetsReaderFromFile, (LPARAM)pSharedAssetsFile),
	sharedAssetsFileTable(&sharedAssetsFile),
	pGlobalAssetsFile(fopen((slimeFolderPath + globalAssetsFileName).c_str(), "rb")),
	globalAssetsFile(AssetsReaderFromFile, (LPARAM)pGlobalAssetsFile),
	globalAssetsFileTable(&globalAssetsFile)
{
	cout << _slimeFolderPath << endl;
	cout << _currentDirectory << endl;
}


managedPatcher::~managedPatcher()
{
}

void managedPatcher::FindAssetOffs(
	vector<string> findResFileName,
	vector<int> findResFileNum,
	vector<string> findSharedFileName,
	vector<int> findSharedFileNum,
	vector<string> findGlobalFindName,
	vector<int> findGlobalFileNum
)
{
	
}
