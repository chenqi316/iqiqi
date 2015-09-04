#pragma once
#include "iTunesApi.h"

class IOSDevice
{
public:
	IOSDevice(void);
	~IOSDevice(void);

	static int IsValid(HANDLE hDevice);

	static int GetCharProperty(HANDLE hDevice, WCHAR* cProperty, char* propertyName);
	static int GetDeviceName(HANDLE hDevice, WCHAR* wcName);
	static int GetDeviceID(HANDLE hDevice, WCHAR* wcDeviceID);
	static int GetDeviceProductType(HANDLE hDevice, WCHAR* wcProductType);
	static int GetDeviceSerialNumber(HANDLE hDevice, WCHAR* wcDeviceSerialNumber);
};

