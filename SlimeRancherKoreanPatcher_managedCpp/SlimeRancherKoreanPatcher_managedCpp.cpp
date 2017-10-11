// 기본 DLL 파일입니다.

#include "stdafx.h"
#include <stdlib.h>
#include <vector>
#include "SlimeRancherKoreanPatcher_managedCpp.h"

using namespace System::Runtime::InteropServices;

namespace SlimeRancherKoreanPatcher_managedCpp
{
	ManagedPatcherWarp::ManagedPatcherWarp(String^ slimeFolderPath, String^ currentDirectory)
	{
		/*cli::pin_ptr<const wchar_t> tempSlimeFolderPath = PtrToStringChars(slimeFolderPath);
		cli::pin_ptr<const wchar_t> tempCurrentDirectory = PtrToStringChars(currentDirectory); // i cannot do this way */  
		IntPtr pDataPtr1 = Marshal::StringToHGlobalAnsi(slimeFolderPath);
		char* charPtrSlimeFolderPath = (char*)pDataPtr1.ToPointer();
		IntPtr pDataPtr2 = Marshal::StringToHGlobalAnsi(currentDirectory);
		char* charPtrCurrentDirectory = (char*)pDataPtr2.ToPointer();
		m_pManagedPatcher = new managedPatcher(charPtrSlimeFolderPath, charPtrCurrentDirectory);
	}

	ManagedPatcherWarp::~ManagedPatcherWarp()
	{
		if (m_pManagedPatcher)
		{
			delete m_pManagedPatcher;
			m_pManagedPatcher = 0;
		}
	}

	array<myAssetFileInfo^>^ ManagedPatcherWarp::FindAssetOffs(
		array<String^>^ findResFileName,
		array<int>^ findResFileNum,
		array<String^>^ fildSharedFileName,
		array<int>^ findSharedFileNum,
		array<String^>^ findGlobalFileName,
		array<int>^ findGlobalFileNum
	)
	{
		/*std::vector<std::string> cFindResFileName;
		std::vector<int> cFindResFileNum;
		std::vector<std::string> cFindSharedFileName;
		std::vector<int> cFindSharedFileNum;
		std::vector<std::string> cFindGlobalFileName;
		std::vector<int> cFileGlobalFileName;*/
		
		vector<unmanagedMyAssetFileInfo> tempAssetFileInfos = 
		m_pManagedPatcher->FindAssetOffs(
			Convert(findResFileName),
			Convert(findResFileNum),
			Convert(fildSharedFileName),
			Convert(findSharedFileNum),
			Convert(findGlobalFileName),
			Convert(findGlobalFileNum)
			);
		array<myAssetFileInfo^>^ res = gcnew array<myAssetFileInfo^>(tempAssetFileInfos.size());
		for (int i = 0; i < tempAssetFileInfos.size(); i++)
		{
			myAssetFileInfo^ tempMyAssetFileInfo;
			tempMyAssetFileInfo->absolutePos = tempAssetFileInfos[i].absolutePos;
			tempMyAssetFileInfo->curFileSize = tempAssetFileInfos[i].curFileSize;
			tempMyAssetFileInfo->curFileType = tempAssetFileInfos[i].curFileType;
			tempMyAssetFileInfo->curFileTypeOrIndex = tempAssetFileInfos[i].curFileTypeOrIndex;
			tempMyAssetFileInfo->index = tempAssetFileInfos[i].index;
			tempMyAssetFileInfo->inheritedUnityClass = tempAssetFileInfos[i].inheritedUnityClass;
			String^ tempName = Marshal::PtrToStringAnsi((IntPtr)(char *)tempAssetFileInfos[i].name.c_str());
			tempMyAssetFileInfo->name = tempName;
			tempMyAssetFileInfo->offs_curFile = tempAssetFileInfos[i].offs_curFile;
			tempMyAssetFileInfo->scriptIndex = tempAssetFileInfos[i].scriptIndex;
			tempMyAssetFileInfo->unknown1 = tempAssetFileInfos[i].unknown1;
			res[i] = tempMyAssetFileInfo;
		}
		return res;
	}

	std::vector<std::string> ManagedPatcherWarp::Convert(array<String^>^ CShopVal)
	{
		std::vector<std::string> CppVal;
		for (int i = 0; i < CShopVal->Length; i++)
		{
			CppVal.push_back(
				(char *)Marshal::StringToHGlobalAnsi(CShopVal[i]).ToPointer()
			);
		}
		return CppVal;
	}

	std::vector<int> ManagedPatcherWarp::Convert(array<int>^ CShopVal)
	{
		std::vector<int> CppVal;
		for (int i = 0; i < CShopVal->Length; i++)
		{
			int temp = CShopVal[i];
			CppVal.push_back(temp);
		}
		return CppVal;
	}

}