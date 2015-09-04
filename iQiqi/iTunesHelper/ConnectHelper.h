#pragma once

#include "iOSConnect.h"
#include "iTunesApi.h"
#include "iOSDevice.h"

namespace ConnectHelper {
    int InitAPI();
    int UninitAPI();

    int RegisterOnConnectListener(pConnecttion callback, void* pUserData);
    int RegisterOnDisConnectListener(pConnecttion callback, void* pUserData);
    int StartListen();

    int DeviceOpen(HANDLE device);
    int DeviceKeepConnect(HANDLE device);
    int DeviceClose(HANDLE device);
    int GetDeviceInformation(HANDLE device, DeviceProperty* info);
    int AFCServiceOpen(HANDLE device, HANDLE& afc_handle);
    void GetFileInfomation(HANDLE afc_handle, IOSFI* fi,char* path);
};
