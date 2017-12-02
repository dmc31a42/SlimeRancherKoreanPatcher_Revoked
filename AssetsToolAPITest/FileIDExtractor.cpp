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
#include <map>

#include "AssetsTools\defines.h"
#include "AssetsTools\AssetsFileFormat.h"
#include "AssetsTools\AssetsFileReader.h"
#include "AssetsTools\AssetsFileTable.h"
#include "AssetsTools\AssetTypeClass.h"
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


	string resAssetsFileName = "sharedassets0.assets";
	FILE *pResAssetsFile = fopen((assetsFolderName+resAssetsFileName).c_str(), "rb");
	AssetsFile resAssetsFile(AssetsReaderFromFile, (LPARAM)pResAssetsFile); // I tried &AssetsReaderFromFile too since I'm not sure what's right here but it makes no difference
	AssetsFileTable resAssetsFileTable(&resAssetsFile);

	ClassDatabaseFile* classDatabaseFile = new ClassDatabaseFile;
	string databaseFileName = "D:\\Documents\\Visual Studio 2017\\Projects\\SlimeRancherPatcher_test\\SlimeRancherKoreanPatcher\\AssetsToolAPITest\\U5.6.0f3.dat";
	FILE *pFclassDatabaseFile = fopen(databaseFileName.c_str(), "rb");
	classDatabaseFile->Read(AssetsReaderFromFile, (LPARAM)pFclassDatabaseFile);
	map<int, unsigned int> findByClassID;
	for (int i= 0 ; i < classDatabaseFile->classes.size(); i++)
	{
		int classId = classDatabaseFile->classes[i].classId;
		findByClassID.insert(map<int, unsigned int>::value_type(classId, i));
		switch(classId)
		{
			case 49:
			case 28:
			case 4:
			case 0x98:
				cout << "classDatabaseFile.classes[" << i << "].classId : " << classDatabaseFile->classes[i].classId << endl;
				break;
		}
		//cout << "classDatabaseFile.classes[" << i << "] : " << classDatabaseFile->classes[i].name.GetString() << endl;
		AssetTypeTemplateField *tempAssetTypeTemplateField = new AssetTypeTemplateField;
		tempAssetTypeTemplateField->FromClassDatabase(classDatabaseFile, &classDatabaseFile->classes[i], (DWORD)0);
		const char* tempStr = tempAssetTypeTemplateField->type;
		//if(tempStr)
		//	cout << "tempAssetTypeTemplateField->type(" << i << ")" << tempStr << endl;
	}
	/*
	classDatabaseFile.classes[191].classId : 49
	classDatabaseFile.classes[193].classId : 28
	classDatabaseFile.classes[197].classId : 4
	*/

	const int findResLength = 10;
	string findResFileName[findResLength] = { "achieve", "actor", "exchange", "global", "keys", "mail", "pedia", "range", "tutorial", "ui" };
	int findResFileNum[findResLength] = { 2, 1, 3, 0, 1, 0, 2, 4, 1, 1};
	int findResFileID[findResLength] = {};
		
	vector<string> resFileName;

	for (int i = 586; i <= resAssetsFileTable.assetFileInfoCount; i++)
	{
		AssetFileInfoEx* tempAssetFileInfoEx = resAssetsFileTable.getAssetInfo(i);
		AssetsFileReader reader;
		LPARAM readerPar;
		//cout << "curFileSize : " << tempAssetFileInfoEx->curFileSize << endl;
		//cout << "absolutePos : " << tempAssetFileInfoEx->absolutePos << endl;
		//cout << "curFileType : " << hex << showbase << tempAssetFileInfoEx->curFileType << endl;
		cout << dec;
		AssetTypeTemplateField *tempAssetTypeTemplateField = new AssetTypeTemplateField;
		tempAssetTypeTemplateField->FromClassDatabase(classDatabaseFile, &classDatabaseFile->classes[findByClassID[tempAssetFileInfoEx->curFileType]],(DWORD)0);
		//tempAssetTypeTemplateField->name = "Base";
		//tempAssetTypeTemplateField->type = "UInt8";
		//tempAssetTypeTemplateField->valueType = ValueType_UInt8;
		//tempAssetTypeTemplateField->hasValue = true;
		/*tempAssetTypeTemplateField->name = "Base";
		tempAssetTypeTemplateField->type = "TypelessData";
		tempAssetTypeTemplateField->valueType = ValueType_None;
		tempAssetTypeTemplateField->childrenCount = 1;
		AssetTypeTemplateField *m_RawData = new AssetTypeTemplateField;
		tempAssetTypeTemplateField->children = m_RawData;
		m_RawData->name = "m_RawData";
		m_RawData->type = "vector";
		m_RawData->valueType = ValueType_None;
		m_RawData->childrenCount = 1;
		AssetTypeTemplateField *m_Array = new AssetTypeTemplateField;
		m_RawData->children = m_Array;
		m_Array->name = "Array";
		m_Array->type = "Array";
		m_Array->isArray = true;
		m_Array->align = true;
		m_Array->childrenCount = 1;
		AssetTypeTemplateField *TemplateData = new AssetTypeTemplateField;
		m_Array->children = TemplateData;
		TemplateData->name = "data";
		TemplateData->type = "UInt8";
		TemplateData->hasValue = true;*/

		////TypeField_07 *typeField_07;
		//const char baseChar[255] = "Base";
		//const char UInt8Char[255] = "UInt8";
		//TypeField_07 *baseField_07 = new TypeField_07;
		//memcpy(&baseField_07->name, baseChar, 255);
		//memcpy(&baseField_07->type, UInt8Char, 255);
		//baseField_07->size = tempAssetFileInfoEx->curFileSize;
		////typeField_07->size = tempAssetFileInfoEx->curFileSize;
		//tempAssetTypeTemplateField->From07(baseField_07);
		AssetTypeInstance tempAssetTypeInstance((DWORD)1, &tempAssetTypeTemplateField, AssetsReaderFromFile, (LPARAM)pResAssetsFile, (bool)resAssetsFile.header.endianness,tempAssetFileInfoEx->absolutePos);
		AssetTypeValueField *pBase = tempAssetTypeInstance.GetBaseField();
		if (pBase)
		{
			AssetTypeValueField *pm_Name = pBase->Get("m_Name");
			if (pm_Name && pm_Name->IsDummy() == false)
			{
				cout << pm_Name->GetValue()->AsString() << endl;
			}
			// https://github.com/DerPopo/UABE/issues/58#event-731969592
			//cout << "pBase->Get(\"Array\")->Get((unsigned int)0UL) : " << pBase->Get("Array")->Get((unsigned int)0UL) << endl;
			//cout << "pBase->Get(\"m_Name\")->GetValue()->AsString() : " << pBase->Get("m_Name")->GetValue()->AsString() << endl;
			//AssetTypeByteArray *tempAssetTypeByteArray =  pBase->GetValue()->AsByteArray();
			/*cout << "tempAssetTypeByteArray->size : " << tempAssetTypeByteArray->size << endl;
			for (int j = 0; j < tempAssetTypeByteArray->size; j++)
			{
				cout << tempAssetTypeByteArray->data[j];
			}
			cout << endl;*/
			//AssetTypeByteArray *tempAssetTypeByteArray = pBase->GetValue()->AsByteArray();
			//cout << "tempAssetTypeByteArray->size : " << tempAssetTypeByteArray->size << endl;
			/*int m_PathID = pBase->Get("m_Script")->Get("m_PathID")->GetValue()->AsUInt64();
			if(m_PathID == 1299 || m_PathID == 139)
				cout << "m_PathID : " << i << " PPtr<MonoScript> m_PathID : " << m_PathID << endl;*/
		}
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

	const int findSharedLength = 2;
	string findSharedFileName[findSharedLength] = {"OpenSans-Semibold SDF Material","OpenSans SDF Atlas"};
	int findSharedFileNum[findSharedLength] = {0,0};
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