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
		// TODO: ���⿡ �� Ŭ������ ���� �޼��带 �߰��մϴ�.
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
