#pragma once
#include "defines.h"
#include "AssetsFileFormat.h"
#include "AssetsBundleFileFormat.h"
#include "AssetsFileReader.h"

enum BundleReplacementType
{
	BundleReplacement_AddOrModify,
	BundleReplacement_Rename,
	BundleReplacement_Remove
};
class BundleReplacer
{
	public:
		virtual BundleReplacementType GetType() = 0;
		virtual ~BundleReplacer()
			#ifndef ASSETSTOOLS_EXPORTS
			= 0
			#endif
			;
		
		virtual unsigned int GetBundleListIndex() = 0; //use only if there are multiple entries with the name, is -1 if unknown

		//The name of the entry (before ANY rename)
		virtual const char *GetOriginalEntryName() = 0;
		virtual const char *GetEntryName() = 0;
		//returns -1 if the original entry data should be used; 
		//DO NOT rely on the value returned : some modifiers can't easily calculate the target size, so 0 is returned
		virtual QWORD GetSize() = 0;

		virtual bool Init(class AssetsBundleFile *pBundleFile, 
			AssetsFileReader entryReader, LPARAM entryReaderPar, 
			QWORD entryPos, QWORD entrySize) = 0;
		virtual void Uninit() = 0;

		//should allow writes multiple times (although probably not used)
		virtual QWORD Write(QWORD pos, AssetsFileWriter writer, LPARAM writerPar) = 0;

		//writes a binary representation of the replacer
		virtual QWORD WriteReplacer(QWORD pos, AssetsFileWriter writer, LPARAM writerPar) = 0;

		//if true, this is an .assets file (at least I don't think there are any "serialized" files that aren't .assets)
		virtual bool HasSerializedData() = 0;
};

//use NULL for newName to keep the old name

ASSETSTOOLS_API BundleReplacer *ReadBundleReplacer(QWORD &pos, AssetsFileReader reader, LPARAM readerPar, bool prefReplacerInMemory = false);
ASSETSTOOLS_API BundleReplacer *MakeBundleEntryRemover(const char *name, bool hasSerializedData,
	unsigned int bundleListIndex = (unsigned int)-1);
ASSETSTOOLS_API BundleReplacer *MakeBundleEntryRenamer(const char *oldName, const char *newName, bool hasSerializedData,
	unsigned int bundleListIndex = (unsigned int)-1);
ASSETSTOOLS_API BundleReplacer *MakeBundleEntryModifier(const char *oldName, const char *newName, bool hasSerializedData,
	AssetsFileReader reader, LPARAM readerPar, cbFreeReaderResource freeReaderCallback, QWORD size, QWORD readerPos=0, 
	size_t copyBufferLen=0,
	unsigned int bundleListIndex = (unsigned int)-1);
ASSETSTOOLS_API BundleReplacer *MakeBundleEntryModifierFromMem(const char *oldName, const char *newName, bool hasSerializedData,
	void *pMem, size_t size,
	unsigned int bundleListIndex = (unsigned int)-1,
	cbFreeMemoryResource freeResourceCallback = NULL);
ASSETSTOOLS_API BundleReplacer *MakeBundleEntryModifierFromAssets(const char *oldName, const char *newName, 
	AssetsFile *pAssetsFile, AssetsReplacer **pReplacers, size_t replacerCount, DWORD fileId,
	unsigned int bundleListIndex = (unsigned int)-1);
ASSETSTOOLS_API void FreeBundleReplacer(BundleReplacer *pReplacer);