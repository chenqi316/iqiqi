#pragma once
#include <wtypes.h>
class CommonHelper
{

public:
	static void GetDevicePathName(char* deviceFullPath,char* pathName);
	static void GetDeviceFileName(char* deviceFullPath,char* fileName);
	static void DeleteLocalFolder(char* localPath,int deleteAll = TRUE);
	static int LocalFolderExits(char* localPath);
	static void GetCFString(HANDLE hValue,WCHAR* charstring,UINT charstringLen);
};

