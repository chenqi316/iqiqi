#include "ConnectHelper.h"
#include <assert.h>

int ConnectHelper::InitAPI()
{
	int result = FALSE;
	int ret_code = 0;

    ret_code = iTunesApi::Init();
	PROCESS_ERROR(ret_code);

	result = TRUE;
Exit0:
	return result;
}

int ConnectHelper::UninitAPI()
{
    iTunesApi::Uninit();
	return TRUE;
}

int ConnectHelper::RegisterOnConnectListener(pConnecttion callback, void* pUserData){
    int result = FALSE;

    PROCESS_ERROR(callback);

    IOSConnect::OnConnect = callback;
    IOSConnect::OnConnectUserData = pUserData;

    result = TRUE;
Exit0:
    return result;
}

int ConnectHelper::RegisterOnDisConnectListener(pConnecttion callback, void* pUserData){
    int result = FALSE;

    PROCESS_ERROR(callback);

    IOSConnect::OnDisConnect = callback;
    IOSConnect::OnDisconnectUserData = pUserData;

    result = TRUE;
Exit0:
    return result;
}

int ConnectHelper::StartListen(){
    int result = FALSE;
    int ret_code = 0;

    PROCESS_ERROR(IOSConnect::OnConnect);
    PROCESS_ERROR(IOSConnect::OnDisConnect);

    HANDLE handle;
    ret_code = iTunesApi::AMDeviceNotificationSubscribe(IOSConnect::DeviceOnConnection,0,0,0,&handle);
    PROCESS_ERROR(!ret_code);

    cout<<"start listen"<<endl;
    result = TRUE;
Exit0:
    return result;
}

int ConnectHelper::DeviceOpen(HANDLE device)
{
    int result = FALSE;
    int ret_code = 0;

    PROCESS_ERROR(device);
    ret_code = iTunesApi::AMDeviceConnect(device);
    PROCESS_ERROR(!ret_code);

    ret_code = iTunesApi::AMDeviceIsPaired(device);
    PROCESS_ERROR(ret_code);

    ret_code = iTunesApi::AMDeviceValidatePairing(device);
    PROCESS_ERROR(!ret_code);

    ret_code = iTunesApi::AMDeviceStartSession(device);
    PROCESS_ERROR(!ret_code);

    result = TRUE;
Exit0:
    return TRUE;
}

int ConnectHelper::DeviceKeepConnect(HANDLE device)
{
    int result = FALSE;
    int ret_code = 0;

    PROCESS_ERROR(device);

    ret_code = iTunesApi::AMDeviceStartSession(device);
    if(ret_code)
    {
        ret_code = iTunesApi::AMDeviceDisconnect(device);
        PROCESS_ERROR(!ret_code);

        ret_code = iTunesApi::AMDeviceConnect(device);
        PROCESS_ERROR(!ret_code);

        ret_code = iTunesApi::AMDeviceIsPaired(device);
        PROCESS_ERROR(ret_code);

        ret_code = iTunesApi::AMDeviceValidatePairing(device);
        PROCESS_ERROR(!ret_code);

        ret_code = iTunesApi::AMDeviceStartSession(device);
        PROCESS_ERROR(!ret_code);
    }

    result = TRUE;
Exit0:
    return TRUE;
}

int ConnectHelper::DeviceClose(HANDLE device)
{
    int result = FALSE;
    PROCESS_ERROR(device);

    iTunesApi::AMDeviceStopSession(device);
    iTunesApi::AMDeviceDisconnect(device);

    result = TRUE;
Exit0:
    return TRUE;
}

int ConnectHelper::GetDeviceInformation(HANDLE device, DeviceProperty* info){
    int result = FALSE;
    int ret_code = 0;

    PROCESS_ERROR(device);
    PROCESS_ERROR(info);

    ret_code = IOSDevice::GetDeviceName(device, info->Name);
    PROCESS_ERROR(ret_code);

    ret_code = IOSDevice::GetDeviceID(device, info->IdentifyNumber);
    PROCESS_ERROR(ret_code);

    ret_code = IOSDevice::GetDeviceProductType(device, info->ProductType);
    PROCESS_ERROR(ret_code);

    ret_code = IOSDevice::GetDeviceSerialNumber(device, info->SerialNumber);
    PROCESS_ERROR(ret_code);

    result = TRUE;
Exit0:
	return TRUE;
}

int ConnectHelper::AFCServiceOpen(HANDLE device, HANDLE& afc_handle){
    int result = FALSE;
    int ret_code = 0;
    HANDLE service_handle;
    HANDLE socket_handle;

    ret_code = iTunesApi::AMDeviceSecureStartService(device, iTunesApi::CFStringMakeConstantString("com.apple.afc"), NULL, &service_handle);
    PROCESS_ERROR(ret_code);

    socket_handle = iTunesApi::AMDServiceConnectionGetSocket(service_handle);
    PROCESS_ERROR(socket_handle);

    ret_code = iTunesApi::AMDServiceConnectionGetSecureIOContext(service_handle);
    PROCESS_ERROR(ret_code);

    ret_code = iTunesApi::AFCConnectionOpen(socket_handle, 0, &afc_handle);
    PROCESS_ERROR(ret_code);

    result = TRUE;
Exit0:
    return TRUE;
}

void ConnectHelper::GetFileInfomation(HANDLE afc_handle, IOSFI* fi,char* path)
{
    IOSFI *fi1,*fi2;
    fi = NULL;
    fi1=fi2=(IOSFI *)malloc(sizeof(IOSFI));
    HANDLE data;

    int ret = iTunesApi::AFCFileInfoOpen(afc_handle, path, &data);
    if (ret ==0 && data!=NULL)
    {
        HANDLE hKey,hValue;
        hKey = hValue = NULL;
        while (iTunesApi::AFCKeyValueRead(data, &hKey, &hValue)==0 &&hKey!=NULL && hValue!=NULL)
        {
            fi1=(IOSFI *)malloc(sizeof(IOSFI));
            strcpy(fi->key,(char *)(hKey));
            strcpy(fi->value,(char*)(hValue));
            if (fi == NULL)
                fi = fi1;
            else
                fi2->next = fi1;
            fi2 = fi1;
        }
    }
}
