// 기본 DLL 파일입니다.

#include "stdafx.h"
#include <stdlib.h>
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

}