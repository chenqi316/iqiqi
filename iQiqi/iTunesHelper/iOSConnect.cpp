#pragma once
#include "iOSConnect.h"
#include "ConnectHelper.h"
#include "iOSDevice.h"

pConnecttion IOSConnect::OnConnect = NULL;
pConnecttion IOSConnect::OnDisConnect = NULL;
void* IOSConnect::OnConnectUserData;
void* IOSConnect::OnDisconnectUserData;

void IOSConnect::DeviceOnConnection(DeviceConnectInfo* info)
{
	if (info->state == STATE_CONNECT)
	{
		if (IOSDevice::IsValid(info->hDevice))
		{
			OnConnect(info->hDevice, OnConnectUserData);
		}
		return;
	}
	else if (info->state == STATE_DISCONNECT)
	{
		OnDisConnect(info->hDevice, OnDisconnectUserData);
	}
}
