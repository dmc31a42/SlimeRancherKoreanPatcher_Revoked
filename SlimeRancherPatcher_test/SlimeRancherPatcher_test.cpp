// SlimeRancherPatcher_test.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
#define _ITERATOR_DEBUG_LEVEL 0
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <io.h>

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
		str.erase(0,1);
	if (str[str.length()-1] == '"' || str[str.length()-1] == '\'')
		str.erase(str.length()-1,1);
	return str;
}

int filesize(const char* str)
{
	FILE* fpin = fopen(str, "r");
	fseek(fpin, 0L, SEEK_END);
	int fileLen = ftell( fpin );
	fseek(fpin, 0L, SEEK_SET);
	fclose(fpin);
	return fileLen;
}

int filesize(FILE* file)
{
	fseek(file, 0L, SEEK_END);
	int fileLen = ftell( file );
	fseek(file, 0L, SEEK_SET);
	return fileLen;
}

int FindPathID(string str)
{
	std::size_t foundUnderBar = str.find_last_of('_');
	std::size_t foundDot = str.find_last_of('.');
	string ID_string = str.substr(foundUnderBar+1,foundDot-foundUnderBar-1);
	return std::stoi(ID_string);
}

int main(int argc, char* argv[])
{	
	string assetsFileName;
	string patchListFileName;

	if(argc == 1 || argc == 2)
	{
		cout << "command Line : SlimeRancherPatcher.exe fileName.assets patchFileList.txt" << endl;
		cout << endl;

		cout << "[Manual Mode]" << endl;
		cout << "Input .assets File Path to patch (*.assets) : " << endl;
		getline(cin,assetsFileName);
		cout << "Input patch resources file list text File Path (*.text) : " << endl;
		getline(cin,patchListFileName);
	}
	if(argc == 3)
	{
		assetsFileName = argv[1];
		patchListFileName = argv[2];
	}
	assetsFileName = removeQMark(assetsFileName);
	patchListFileName = removeQMark(patchListFileName);

	ifstream ifsPatchListFile(patchListFileName);
	std::vector<string> patchFileName;

	if(!ifsPatchListFile.is_open())
	{
		cout << "cannot open patchFileList text file" << endl;
		cout << "Exit" << endl;
		return 0;
	}

	cout << "Patch File List : " << endl;

	std::vector<FILE*> pPatchFile;
	while(!ifsPatchListFile.eof())
	{
		string temp;
		FILE *pTempPatchFile = NULL;
		ifsPatchListFile >> temp;
		patchFileName.push_back(temp);
		cout << patchFileName[patchFileName.size()-1] << endl;
		pTempPatchFile = fopen(temp.c_str(), "rb");
		if (pTempPatchFile == NULL)
		{
			cout << "cannot open patch file : " << temp << endl;
			cout << "Exit" << endl;
			fclose(pTempPatchFile);
			for(int i=0 ; i<pPatchFile.size() ; i++)
			{
				fclose(pPatchFile[i]);
			}
			return 0;
		}
		pPatchFile.push_back(pTempPatchFile);
	}
	ifsPatchListFile.close();
	
	char backupFileName[255];
	for(unsigned int i=0 ;;i++)
	{
		sprintf(backupFileName,".bak%04d",i);
		int accessResult = access((assetsFileName+backupFileName).c_str(),00);
		if (accessResult == -1)
		{
			break;
		}
	}
	rename(assetsFileName.c_str(),(assetsFileName+backupFileName).c_str());
	int tempAccessResult = access((assetsFileName+backupFileName).c_str(),00);
	if (tempAccessResult == 0)
	{
		cout << "backup file rename success" << endl;
	}
	else
	{
		cout << "backup file rename failed" << endl;
		cout << "Exit" << endl;
		rename((assetsFileName+backupFileName).c_str(),assetsFileName.c_str());
		for(unsigned int i=0 ; i<pPatchFile.size() ; i++)
		{
			fclose(pPatchFile[i]);
		}
		return 0;

	}

	FILE *pAssetsFile = fopen((assetsFileName+backupFileName).c_str(), "rb");
    AssetsFile assetsFile(AssetsReaderFromFile, (LPARAM)pAssetsFile); // I tried &AssetsReaderFromFile too since I'm not sure what's right here but it makes no difference
    AssetsFileTable assetsFileTable(&assetsFile);
	

	std::vector<AssetsReplacer*> replacors;
	std::vector<AssetFileInfoEx*> assetsFileInfos;

	for(unsigned int i=0 ; i<patchFileName.size() ; i++)
	{
		int tempPathID = FindPathID(patchFileName[i]);
		assetsFileInfos.push_back(assetsFileTable.getAssetInfo(tempPathID)); // I know the ID - no need to search
		replacors.push_back(MakeAssetModifierFromFile(0, (*assetsFileInfos[i]).index, (*assetsFileInfos[i]).curFileType, (*assetsFileInfos[i]).inheritedUnityClass,
		   pPatchFile[i], 0, (QWORD)filesize(pPatchFile[i]))); // I expect that the size parameter refers to the file size but I couldn't check this until now
	}
    FILE *pOutputFile = fopen((assetsFileName).c_str(), "wb"); // Output in a temp-file and replace the original one afterwards since the original file should be locked right now
    assetsFile.Write(AssetsWriterToFile, (LPARAM)pOutputFile, 0, replacors.data(),replacors.size(), 0);

    fclose(pAssetsFile);
	for(unsigned int i=0 ; i<pPatchFile.size() ; i++)
	{
		fclose(pPatchFile[i]);
	}
    fclose(pOutputFile);

	cout << "Slime Rancher Korean Translation Patch Complete. Exit" << endl;
    return 0;
}

