// TEST PROJECT FILEMAPPING BY GAZIZ RAZHAPOV - VISUAL STUDIO 2013 ULTIMATE
// INCLUDES
#include <iostream>
#include <windows.h>

struct FileMapping 
{
	HANDLE hFile;
	HANDLE hMapping;
	size_t fsize;
	unsigned char* dataPtr;
};

// Create filemap
FileMapping *FileMappingCreate(const char *cFname)
{
	HANDLE hFile = CreateFile((LPWSTR)cFname, GENERIC_READ, 0, nullptr, OPEN_EXISTING, 
		                      FILE_ATTRIBUTE_NORMAL, nullptr);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::cerr << "ERROR - create file! \n";
		return nullptr;
	}

	DWORD dwFileSize = GetFileSize(hFile, nullptr);
	if (dwFileSize == INVALID_FILE_SIZE)
	{
		std::cerr << "ERROR - GetFileSize!\n";
		CloseHandle(hFile);
		return nullptr;
	}

	HANDLE hMapping = CreateFileMapping(hFile, nullptr, PAGE_READONLY, 0, 0, nullptr);
	if (hMapping == nullptr) 
	{
		std::cerr << "ERROR - CreateFileMapping! \n";
		CloseHandle(hFile);
		return nullptr;
	}

	unsigned char *cDataPtr = (unsigned char*)MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, dwFileSize);
	if (cDataPtr == nullptr)
	{
		std::cerr << "ERROR - MapViewOfFile! \n";
		CloseHandle(hMapping);
		CloseHandle(hFile);
		return nullptr;
	}

	FileMapping* mapping = (FileMapping*)malloc(sizeof(FileMapping));
	if (mapping == nullptr) 
	{
		std::cerr << "ERROR - malloc failed \n";
		UnmapViewOfFile(cDataPtr);
		CloseHandle(hMapping);
		CloseHandle(hFile);
		return nullptr;
	}

	mapping->hFile = hFile;
	mapping->hMapping = hMapping;
	mapping->dataPtr = cDataPtr;
	mapping->fsize = (size_t)dwFileSize;

	return mapping;
}

// Close filemap
void FileMappingClose(FileMapping *_fMapping)
{
	UnmapViewOfFile(_fMapping->dataPtr);
	CloseHandle(_fMapping->hMapping);
	CloseHandle(_fMapping->hFile);
	free(_fMapping);
}

// Get pointer to filemap
unsigned char* FileMappingGetPointer(FileMapping *_fMapping) 
{
	return _fMapping->dataPtr;
}

// Get size filemap
unsigned int FileMappingGetSize(FileMapping *_fMapping)
{
	return (unsigned int)_fMapping->fsize;
}

int main()
{
	FileMapping *ptrFmap = FileMappingCreate("test...");
	FileMappingClose(ptrFmap);
	system("pause");
	return 0;
}