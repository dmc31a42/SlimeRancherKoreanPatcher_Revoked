// SlimeRancherKoreanPatcher_managedCpp.h

#pragma once
#include "..\SlimeRancherKoreanPatcher_cpp\managedPatcher.h"
using namespace System;

namespace SlimeRancherKoreanPatcher_managedCpp {

	public ref class ManagedPatcherWarp
	{
	protected:
		managedPatcher *m_pManagedPatcher;
		// TODO: ���⿡ �� Ŭ������ ���� �޼��带 �߰��մϴ�.
	public:
		ManagedPatcherWarp(String^ slimeFolderPath, String^ currentDirectory);
		virtual ~ManagedPatcherWarp();

	};
}
