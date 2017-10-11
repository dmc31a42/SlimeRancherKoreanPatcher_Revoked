
#include <iostream>
#include <vector>
#include "stdafx.h"
#include "managedPatcher.h"

using namespace std;

managedPatcher::managedPatcher(string slimeFolderPath, string currentDirectory)
	:_slimeFolderPath(slimeFolderPath),
	_currentDirectory(currentDirectory),
	resAssetsFileName("\\resources.assets"),
	sharedAssetsFileName("\\sharedassets0.assets"),
	globalAssetsFileName("\\globalgamemanagers.assets")	
{
}


managedPatcher::~managedPatcher()
{
}

vector<unmanagedMyAssetFileInfo> managedPatcher::FindAssetOffs(
	vector<string> findResFileName,
	vector<int> findResFileNum,
	vector<string> findSharedFileName,
	vector<int> findSharedFileNum,
	vector<string> findGlobalFindName,
	vector<int> findGlobalFileNum
)
{
	FILE *pResAssetsFile = fopen((_slimeFolderPath + resAssetsFileName).c_str(), "rb");
	FILE *pSharedAssetsFile = fopen((_slimeFolderPath + sharedAssetsFileName).c_str(), "rb");
	FILE *pGlobalAssetsFile = fopen((_slimeFolderPath + globalAssetsFileName).c_str(), "rb");
	AssetsFile resAssetsFile(AssetsReaderFromFile, (LPARAM)pResAssetsFile);
	AssetsFile sharedAssetsFile(AssetsReaderFromFile, (LPARAM)pSharedAssetsFile);
	AssetsFile globalAssetsFile(AssetsReaderFromFile, (LPARAM)pGlobalAssetsFile);
	AssetsFileTable resAssetsFileTable(&resAssetsFile);
	AssetsFileTable sharedAssetsFileTable(&sharedAssetsFile);
	AssetsFileTable globalAssetsFileTable(&globalAssetsFile);

	vector<string> ExtractedResFileName;
	vector<string> ExtractedSharedFileName;
	vector<string> ExtractedGlobalFilename;

	vector<int> findResFileID;
	vector<int> findSharedFileID;
	vector<int> findGlobalFileID;

	vector<unmanagedMyAssetFileInfo> resAssetFileInfos = 
		ScrollAssetFileInfo(resAssetsFileTable, findResFileName, findResFileNum);
	vector<unmanagedMyAssetFileInfo> sharedAssetFileInfos =
		ScrollAssetFileInfo(sharedAssetsFileTable, findSharedFileName, findSharedFileNum);
	vector<unmanagedMyAssetFileInfo> globalAssetFileInfos =
		ScrollAssetFileInfo(globalAssetsFileTable, findGlobalFindName, findGlobalFileNum);
	cout << "test" << endl;

	return vector<unmanagedMyAssetFileInfo>();
}

vector<unmanagedMyAssetFileInfo> managedPatcher::ScrollAssetFileInfo(
	AssetsFileTable &assetsFileTable,
	vector<string> findFileName,
	vector<int> findFileNum
)
{
	vector<unmanagedMyAssetFileInfo> assetFileInfos;
	for (unsigned int i = 1; i <= assetsFileTable.assetFileInfoCount; i++)
	{
		AssetFileInfoEx* tempAssetFileInfoEx = assetsFileTable.getAssetInfo(i);
		unmanagedMyAssetFileInfo tempMyAssetFileInfo;
		tempMyAssetFileInfo.absolutePos = tempAssetFileInfoEx->absolutePos;
		tempMyAssetFileInfo.curFileSize = tempAssetFileInfoEx->curFileSize;
		tempMyAssetFileInfo.curFileType = tempAssetFileInfoEx->curFileType;
		tempMyAssetFileInfo.curFileTypeOrIndex = tempAssetFileInfoEx->curFileTypeOrIndex;
		tempMyAssetFileInfo.index = tempAssetFileInfoEx->index;
		tempMyAssetFileInfo.inheritedUnityClass = tempAssetFileInfoEx->inheritedUnityClass;
		tempMyAssetFileInfo.name = tempAssetFileInfoEx->name;
		tempMyAssetFileInfo.offs_curFile = tempAssetFileInfoEx->offs_curFile;
		tempMyAssetFileInfo.scriptIndex = tempAssetFileInfoEx->scriptIndex;
		tempMyAssetFileInfo.unknown1 = tempAssetFileInfoEx->unknown1;
		assetFileInfos.push_back(tempMyAssetFileInfo);
	}
	return assetFileInfos;
}