
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

typedef struct
{
	unsigned __int64 index;			//0x00 //little-endian //version < 0x0E : only DWORD
	DWORD offs_curFile;				//0x08 //little-endian
	DWORD curFileSize;				//0x0C //little-endian
	DWORD curFileTypeOrIndex;		//0x10 //little-endian //starting with version 0x10, this is an index into the type tree
									//inheritedUnityClass : for Unity classes, this is curFileType; for MonoBehaviours, this is 114
									//version < 0x0B : inheritedUnityClass is DWORD, no scriptIndex exists
	WORD inheritedUnityClass;		//0x14 //little-endian (MonoScript)//only version < 0x10
									//scriptIndex : for Unity classes, this is 0xFFFF; for MonoBehaviours, this is the index of the script in the MonoManager asset
	WORD scriptIndex;				//0x16 //little-endian//only version <= 0x10
	BYTE unknown1;					//0x18 //only 0x0F <= version <= 0x10 //with alignment always a DWORD

	DWORD curFileType;
	QWORD absolutePos;
	//char name[100];
	string name;
} unmanagedMyAssetFileInfo;

class managedPatcher
{
private:
	string _slimeFolderPath;
	string _currentDirectory;
	string resAssetsFileName;
	string sharedAssetsFileName;
	string globalAssetsFileName;
	

public:
	managedPatcher(std::string slimeFolderPath, std::string currentDirectory);
	~managedPatcher();
	vector<unmanagedMyAssetFileInfo> FindAssetOffs(
		vector<string> findResFileName, 
		vector<int> findResFileNum,
		vector<string> findSharedFileName,
		vector<int> findSharedFileNum,
		vector<string> findGlobalFindName,
		vector<int> findGlobalFileNum
	);

	vector<unmanagedMyAssetFileInfo> ScrollAssetFileInfo(
		AssetsFileTable &assetsFileTable,
		vector<string> findFileName,
		vector<int> findFileNum
	);
};


