#pragma once
#include <string>
#include <vector>

#include "AssetsTools\defines.h"
#include "AssetsTools\AssetsFileFormat.h"
#include "AssetsTools\AssetsFileReader.h"
#include "AssetsTools\AssetsFileTable.h"
#include "AssetsTools\AssetsBundleFileFormat.h"
#include "AssetsTools\ClassDatabaseFile.h"
using namespace std;

class managedPatcher
{
private:
	string _slimeFolderPath;
	string _currentDirectory;
	string resAssetsFileName;
	string sharedAssetsFileName;
	string globalAssetsFileName;
	FILE *pResAssetsFile;
	FILE *pSharedAssetsFile;
	FILE *pGlobalAssetsFile;
	AssetsFile resAssetsFile;
	AssetsFile sharedAssetsFile;
	AssetsFile globalAssetsFile;
	AssetsFileTable resAssetsFileTable;
	AssetsFileTable sharedAssetsFileTable;
	AssetsFileTable globalAssetsFileTable;

public:
	managedPatcher(std::string slimeFolderPath, std::string currentDirectory);
	~managedPatcher();
	void FindAssetOffs(
		vector<string> findResFileName, 
		vector<int> findResFileNum,
		vector<string> findSharedFileName,
		vector<int> findSharedFileNum,
		vector<string> findGlobalFindName,
		vector<int> findGlobalFileNum
	);
};

