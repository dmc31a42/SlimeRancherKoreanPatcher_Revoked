// SlimeRancherKoreanPatcher_managedCpp.h

#pragma once
#include "..\SlimeRancherKoreanPatcher_cpp\managedPatcher.h"
using namespace System;

namespace SlimeRancherKoreanPatcher_managedCpp {

	public ref class ManagedPatcherWarp
	{
	private:
		std::vector<std::string> Convert(array<String^>^ CShopVal);
		std::vector<int> Convert(array<int>^ CShopVal);
	protected:
		managedPatcher *m_pManagedPatcher;
		// TODO: 여기에 이 클래스에 대한 메서드를 추가합니다.
	public:
		ManagedPatcherWarp(String^ slimeFolderPath, String^ currentDirectory);
		virtual ~ManagedPatcherWarp();

		void FindTextAssetOffs(
			array<String^>^ findResFileName, 
			array<int>^ findResFileNum,
			array<String^>^ fildSharedFileName,
			array<int>^ findSharedFileNum,
			array<String^>^ findGlobalFileName,
			array<int>^ findGlobalFileNum
		);

	};
}
