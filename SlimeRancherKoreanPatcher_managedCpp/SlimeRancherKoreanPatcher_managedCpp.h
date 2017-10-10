// SlimeRancherKoreanPatcher_managedCpp.h

#pragma once
#include "..\SlimeRancherKoreanPatcher_cpp\managedPatcher.h"
using namespace System;

namespace SlimeRancherKoreanPatcher_managedCpp {

	public ref class ManagedPatcherWarp
	{
	protected:
		managedPatcher *m_pManagedPatcher;
		// TODO: 여기에 이 클래스에 대한 메서드를 추가합니다.
	public:
		ManagedPatcherWarp(String^ slimeFolderPath, String^ currentDirectory);
		virtual ~ManagedPatcherWarp();

	};
}
