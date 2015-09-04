#pragma once
#include "iOSDef.h"

//LoadFunctions
#define LOAD_LIBRARY_API(lib_hmodule, fun_pointer, fun_type, fun_name)  \
	fun_pointer = (fun_type)GetProcAddress(lib_hmodule, fun_name); \
	PROCESS_ERROR(fun_pointer);

//Function name
//am functions
typedef int (*func_AMRestoreRegisterForDeviceNotifications)(
	void (*callback_dfu_connect)(DeviceConnectInfo* state),
	void (*callback_recovery_connect)(DeviceConnectInfo* state),
	void (*callback_dfu_disconnect)(DeviceConnectInfo* state),
	void (*callback_recovery_disconnect)(DeviceConnectInfo* state),
	UINT unknow1,
	UINT unknow2
	);
typedef		int			(*func_AMDServiceConnectionSend)(HANDLE conn, char* data, UINT len);
typedef		int			(*func_AMDServiceConnectionReceive)(HANDLE conn, char* data, UINT* len);
typedef		void		(*func_AMDServiceConnectionInvalidate)(HANDLE conn);
typedef		int			(*func_AMDeviceGetInterfaceType)(HANDLE handle);
typedef		HANDLE		(*func_AMDeviceRetain)(HANDLE handle);
typedef		int			(*func_AMDeviceNotificationSubscribe)(void (*callback)(DeviceConnectInfo* state), UINT uint1, UINT uint2, UINT uint3, HANDLE *notify);
typedef		int			(*func_AMDeviceConnect)(HANDLE handle);
typedef		HANDLE		(*func_AMDeviceCopyDeviceIdentifier)(HANDLE handle);
typedef		int			(*func_AMDeviceDisconnect)(HANDLE handle);
typedef		int			(*func_AMDeviceIsPaired)(HANDLE handle);
typedef		int			(*func_AMDeviceValidatePairing)(HANDLE handle);
typedef		int			(*func_AMDeviceStartSession)(HANDLE handle);
typedef		int			(*func_AMDeviceStopSession)(HANDLE handle);
typedef		int			(*func_AMDeviceSetValue)(HANDLE handle, HANDLE cfstring1, HANDLE cfstring2);
typedef		HANDLE		(*func_AMDeviceCopyValue)(HANDLE handle, HANDLE cfstring1, HANDLE cfstring2);

typedef     int         (*func_AMDeviceSecureStartService)(HANDLE devici_handle, HANDLE service_name, UINT *uint,HANDLE* service_handle);
typedef     HANDLE      (*func_AMDServiceConnectionGetSocket)(HANDLE service_handle);
typedef     int         (*func_AMDServiceConnectionGetSecureIOContext)(HANDLE service_handle);

//afc functions
typedef     int         (*func_AFCConnectionOpen)(HANDLE socket_handle, UINT time_out, HANDLE* connection_handle);
typedef     int         (*func_AFCFileInfoOpen)(HANDLE conn, char* path, HANDLE* data);
typedef     int         (*func_AFCKeyValueRead)(HANDLE data, HANDLE* key, HANDLE* value);

typedef     int         (*func_AFCDirectoryOpen)(HANDLE conn, char *path, HANDLE* directory);
typedef     int         (*func_AFCFileRefOpen)(HANDLE conn, char *path, unsigned long long int mode, HANDLE ref);
typedef     int         (*func_AFCFileRefRead)(HANDLE conn, HANDLE ref, void *buf, unsigned int *len);
typedef     int         (*func_AFCFileRefClose)(HANDLE conn, HANDLE ref);

//cf functions
typedef		HANDLE		(*func_CFStringMakeConstantString)(char* data);
//cf functions
typedef		int         (*func_CFStringGetCString)(HANDLE cfstring, WCHAR* byteString, UINT len, UINT encode);
typedef		int  		(*func_CFGetTypeID)(HANDLE type);
typedef		int 		(*func_CFStringGetTypeID)();
typedef		int 		(*func_CFStringGetLength)(HANDLE hStr);


class iTunesApi
{
public:
    iTunesApi(void){};
    ~iTunesApi(void){};

public:
    static HMODULE _iTunes_mobile_device_dll;
    static HMODULE _core_function_dll;
public:
	static UINT Init();
	static int Uninit();
public:
	//am
	static func_AMRestoreRegisterForDeviceNotifications AMRestoreRegisterForDeviceNotifications;
	static func_AMDServiceConnectionSend AMDServiceConnectionSend;
	static func_AMDServiceConnectionReceive AMDServiceConnectionReceive;
	static func_AMDeviceGetInterfaceType AMDeviceGetInterfaceType;
	static func_AMDServiceConnectionInvalidate AMDServiceConnectionInvalidate;
	static func_AMDeviceRetain AMDeviceRetain;
	static func_AMDeviceNotificationSubscribe AMDeviceNotificationSubscribe;
	static func_AMDeviceConnect AMDeviceConnect;
	static func_AMDeviceCopyDeviceIdentifier AMDeviceCopyDeviceIdentifier;
	static func_AMDeviceDisconnect AMDeviceDisconnect;
	static func_AMDeviceIsPaired AMDeviceIsPaired;
	static func_AMDeviceValidatePairing AMDeviceValidatePairing;
	static func_AMDeviceStartSession AMDeviceStartSession;
	static func_AMDeviceStopSession AMDeviceStopSession;
	static func_AMDeviceSetValue AMDeviceSetValue;
	static func_AMDeviceCopyValue AMDeviceCopyValue;
    static func_AMDeviceSecureStartService AMDeviceSecureStartService;
    static func_AMDServiceConnectionGetSocket AMDServiceConnectionGetSocket;
    static func_AMDServiceConnectionGetSecureIOContext AMDServiceConnectionGetSecureIOContext;

    //afc
    static func_AFCConnectionOpen AFCConnectionOpen;
    static func_AFCFileInfoOpen AFCFileInfoOpen;
    static func_AFCKeyValueRead AFCKeyValueRead;

    static func_AFCDirectoryOpen AFCDirectoryOpen;
    static func_AFCFileRefOpen AFCFileRefOpen;
    static func_AFCFileRefRead AFCFileRefRead;
    static func_AFCFileRefClose AFCFileRefClose;

	//cfstring
	static func_CFStringMakeConstantString CFStringMakeConstantString;
	//cf
	static func_CFStringGetCString CFStringGetCString;
	static func_CFGetTypeID CFGetTypeID;
	static func_CFStringGetTypeID CFStringGetTypeID;
	static func_CFStringGetLength CFStringGetLength;
};
