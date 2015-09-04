#include <stdlib.h>
#include "iOSDevice.h"
#include "CommonHelper.h"

int IOSDevice::IsValid(HANDLE device){
    int result = FALSE;
    int ret_code = 0;

    device = iTunesApi::AMDeviceRetain(device);
    PROCESS_ERROR(device);

    ret_code = iTunesApi::AMDeviceConnect(device);
    PROCESS_ERROR(!ret_code);

    ret_code = iTunesApi::AMDeviceIsPaired(device);
    PROCESS_ERROR(ret_code);

    ret_code = iTunesApi::AMDeviceValidatePairing(device);
    PROCESS_ERROR(!ret_code);

    ret_code = iTunesApi::AMDeviceStartSession(device);
    PROCESS_ERROR(!ret_code);

    WCHAR wcSerialNumber[MAX_PATH];
    IOSDevice::GetDeviceSerialNumber(device,wcSerialNumber);

    ret_code = iTunesApi::AMDeviceStopSession(device);
    PROCESS_ERROR(!ret_code);

    ret_code = iTunesApi::AMDeviceDisconnect(device);
    PROCESS_ERROR(!ret_code);

    ret_code = iTunesApi::AMDeviceGetInterfaceType(device);
    PROCESS_ERROR(ret_code);


    result = TRUE;
Exit0:
    return result;
}

int IOSDevice::GetCharProperty(HANDLE hDevice, WCHAR* value, char* name)
{
    int result = FALSE;
    int ret_code = 0;

    HANDLE handle_result;
    HANDLE cf_name = iTunesApi::CFStringMakeConstantString(name);
    handle_result = iTunesApi::AMDeviceCopyValue(hDevice, NULL, cf_name);
    PROCESS_ERROR(handle_result)

    CommonHelper::GetCFString(handle_result, value, MAX_PATH);
    result = TRUE;
Exit0:
    return result;
}
int IOSDevice::GetDeviceName(HANDLE hDevice, WCHAR* wcName)
{
    return GetCharProperty(hDevice, wcName, "DeviceName");
}
int IOSDevice::GetDeviceID(HANDLE hDevice, WCHAR* wcDeviceID)
{
    return GetCharProperty(hDevice, wcDeviceID, "UniqueDeviceID");
}
int IOSDevice::GetDeviceProductType(HANDLE hDevice, WCHAR* wcProductType)
{
    return GetCharProperty(hDevice, wcProductType, "ProductType");
}
int IOSDevice::GetDeviceSerialNumber(HANDLE hDevice, WCHAR* wcDeviceSerialNumber)
{
    return GetCharProperty(hDevice,  wcDeviceSerialNumber, "SerialNumber");
}
