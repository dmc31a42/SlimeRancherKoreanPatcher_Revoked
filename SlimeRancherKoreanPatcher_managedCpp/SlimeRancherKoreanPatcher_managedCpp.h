// SlimeRancherKoreanPatcher_managedCpp.h

#pragma once
#include "..\SlimeRancherKoreanPatcher_cpp\managedPatcher.h"
#include <list>
using namespace System;

namespace SlimeRancherKoreanPatcher_managedCpp {
	public ref struct myAssetFileInfo
	{
	public:
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
		String^ name;
	};

	public ref class ManagedPatcherWarp
	{
	private:
		static std::vector<std::string> Convert(array<String^>^ CShopVal);
		static std::vector<int> Convert(array<int>^ CShopVal);
	protected:
		managedPatcher *m_pManagedPatcher;

		// TODO: 여기에 이 클래스에 대한 메서드를 추가합니다.
	public:
		ManagedPatcherWarp(String^ slimeFolderPath, String^ currentDirectory);
		virtual ~ManagedPatcherWarp();

		array<myAssetFileInfo^>^ FindAssetOffs(
			array<String^>^ findResFileName, 
			array<int>^ findResFileNum,
			array<String^>^ fildSharedFileName,
			array<int>^ findSharedFileNum,
			array<String^>^ findGlobalFileName,
			array<int>^ findGlobalFileNum
		);
	};

	
}
