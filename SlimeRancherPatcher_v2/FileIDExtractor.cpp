// SlimeRancherPatcher_test.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
#define _ITERATOR_DEBUG_LEVEL 0
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <io.h>
#include <direct.h>

#include "AssetsTools\defines.h"
#include "AssetsTools\AssetsFileFormat.h"
#include "AssetsTools\AssetsFileReader.h"
#include "AssetsTools\AssetsFileTable.h"
#include "AssetsTools\AssetsBundleFileFormat.h"
#include "AssetsTools\ClassDatabaseFile.h"

using namespace std;

string removeQMark(string str)
{
	if (str[0] == '"' || str[0] == '\'')
		str.erase(0, 1);
	if (str[str.length() - 1] == '"' || str[str.length() - 1] == '\'')
		str.erase(str.length() - 1, 1);
	return str;
}

int main(int argc, char* argv[])
{	
	string assetsFolderName;
	if (argc != 2)
		/*{
			cout << "command Line : SlimeRancherPosExtractor.exe \"FolderName\"" << endl;
			cout << endl;

			cout << "[Manual Mode]" << endl;
			cout << "Input FolderPath Path to patch : " << endl;
			getline(cin, assetsFolderName);

		}*/
	{
		char strBuffer[_MAX_PATH] = { 0, };

		char *pstrBuffer = NULL;
		pstrBuffer = getcwd(strBuffer, _MAX_PATH);
		assetsFolderName = strBuffer;
		assetsFolderName += "\\..\\..\\";
	}
	else
	{
		assetsFolderName = argv[1];
	}
	assetsFolderName = removeQMark(assetsFolderName);
	if (assetsFolderName[assetsFolderName.length() - 1] != '\\') {
		assetsFolderName += "\\";
	}
	string resAssetsFileName = "resources.assets";
	FILE *pResAssetsFile = fopen((assetsFolderName+resAssetsFileName).c_str(), "rb");
	AssetsFile resAssetsFile(AssetsReaderFromFile, (LPARAM)pResAssetsFile); // I tried &AssetsReaderFromFile too since I'm not sure what's right here but it makes no difference
	AssetsFileTable resAssetsFileTable(&resAssetsFile);

	const int findResLength = 10;
	string findResFileName[findResLength] = { "achieve", "actor", "exchange", "global", "keys", "mail", "pedia", "range", "tutorial", "ui" };
	int findResFileNum[findResLength] = { 2, 1, 3, 0, 1, 0, 2, 4, 1, 1};
	int findResFileID[findResLength] = {};
		
	vector<string> resFileName;

	for (int i = 1; i <= resAssetsFileTable.assetFileInfoCount; i++)
	{
		AssetFileInfoEx* tempAssetFileInfoEx = resAssetsFileTable.getAssetInfo(i);
		resFileName.push_back(tempAssetFileInfoEx->name);
	}

	for (int i = 0; i < findResLength; i++)
	{
		int pos = 0;
		for (int j = 0; j <= findResFileNum[i]; j++)
		{
			bool tempbool = true;
			while(tempbool)
			{
				if (resFileName[pos] == findResFileName[i])
				{
					tempbool = false;
				}
				pos++;
			}
		}
		findResFileID[i] = pos;
	}
	string res = "";
	for (int i = 0; i < findResLength; i ++)
	{
		res += findResFileName[i] + ":" + to_string((long long)findResFileID[i]) + "\r\n";
	}



	string sharedAssetsFileName = "sharedassets0.assets";
	FILE *pSharedAssetsFile = fopen((assetsFolderName + sharedAssetsFileName).c_str(), "rb");
	AssetsFile sharedAssetsFile(AssetsReaderFromFile, (LPARAM)pSharedAssetsFile); // I tried &AssetsReaderFromFile too since I'm not sure what's right here but it makes no difference
	AssetsFileTable sharedAssetsFileTable(&sharedAssetsFile);

	const int findSharedLength = 3;
	string findSharedFileName[findSharedLength] = {"OpenSans-Semibold SDF Material","OpenSans SDF Atlas", "TMP_SDF-Mobile"};
	int findSharedFileNum[findSharedLength] = {0,0,0};
	int findSharedFileID[findSharedLength] = {};

	vector<string> sharedFileName;

	for (int i = 1; i <= sharedAssetsFileTable.assetFileInfoCount; i++)
	{
		AssetFileInfoEx* tempAssetFileInfoEx = sharedAssetsFileTable.getAssetInfo(i);
		sharedFileName.push_back(tempAssetFileInfoEx->name);
	}

	for (int i = 0; i < findSharedLength; i++)
	{
		int pos = 0;
		for (int j = 0; j <= findSharedFileNum[i]; j++)
		{
			bool tempbool = true;
			while (tempbool)
			{
				if (sharedFileName[pos] == findSharedFileName[i])
				{
					tempbool = false;
				}
				pos++;
			}
		}
		findSharedFileID[i] = pos;
	}
	for (int i = 0; i < findSharedLength; i++)
	{
		res += findSharedFileName[i] + ":" + to_string((long long)findSharedFileID[i]) + "\r\n";
	}

	string globalAssetsFileName = "globalgamemanagers.assets";
	FILE *pGlobalAssetsFile = fopen((assetsFolderName + globalAssetsFileName).c_str(), "rb");
	AssetsFile globalAssetsFile(AssetsReaderFromFile, (LPARAM)pGlobalAssetsFile); // I tried &AssetsReaderFromFile too since I'm not sure what's right here but it makes no difference
	AssetsFileTable globalAssetsFileTable(&globalAssetsFile);

	const int findGlobalLength = 1;
	string findGlobalFileName[findGlobalLength] = {"TMP_FontAsset"};
	int findGlobalFileNum[findGlobalLength] = { 0};
	int findGlobalFileID[findGlobalLength] = {0};

	vector<string> globalFileName;

	for (int i = 1; i <= globalAssetsFileTable.assetFileInfoCount; i++)
	{
		AssetFileInfoEx* tempAssetFileInfoEx = globalAssetsFileTable.getAssetInfo(i);
		globalFileName.push_back(tempAssetFileInfoEx->name);
	}

	for (int i = 0; i < findGlobalLength; i++)
	{
		int pos = 0;
		for (int j = 0; j <= findGlobalFileNum[i]; j++)
		{
			bool tempbool = true;
			while (tempbool)
			{
				if (globalFileName[pos] == findGlobalFileName[i])
				{
					tempbool = false;
				}
				pos++;
			}
		}
		findGlobalFileID[i] = pos;
	}
	for (int i = 0; i < findGlobalLength; i++)
	{
		res += findGlobalFileName[i] + ":" + to_string((long long)findGlobalFileID[i]) + "\r\n";
	}
	ofstream OutputFile;
	OutputFile.open("FileID.txt", ios::trunc);
	OutputFile << res;
	OutputFile.close();
	cout << res;
	//getchar();
	return 0;
}