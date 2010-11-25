#include <windows.h>
#include <setupapi.h>
#include <winioctl.h>

//****************************************************************************
//                             File EWTIOCTL.H
//
//                     IoCtl codes for Ewclid-T driver
//
//            Copyright (c) ComCom Electronics Ltd., 2002-2004.
//                          All rights reserved.
//
//****************************************************************************
//
//  $Archive: /Source/Ewclid-T/Inc/EwtIoctl.h $
// $Workfile: EwtIoctl.h $
//   $Author: Igor $
//     $Date: 5/19/04 4:45p $
//  $Modtime: 4/20/04 6:24p $
// $Revision: 1 $
//
//      $Log: /Source/Ewclid-T/Inc/EwtIoctl.h $
// 
// 1     5/19/04 4:45p Igor
// Initial revision
//
//****************************************************************************

#define FILE_DEVICE_EWCLIDT                 FILE_DEVICE_CONTROLLER
#define IOCTL_EWCLIDT_RESET_ADAPTER         CTL_CODE(FILE_DEVICE_EWCLIDT, 0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_EWCLIDT_READ_SENSOR           CTL_CODE(FILE_DEVICE_EWCLIDT, 0x801, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_EWCLIDT_RELAY_CONTROL         CTL_CODE(FILE_DEVICE_EWCLIDT, 0x802, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_EWCLIDT_POWER_CONTROL         CTL_CODE(FILE_DEVICE_EWCLIDT, 0x803, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_EWCLIDT_DEVICE_INFO           CTL_CODE(FILE_DEVICE_EWCLIDT, 0x804, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_EWCLIDT_RESET_SPI             CTL_CODE(FILE_DEVICE_EWCLIDT, 0x805, METHOD_NEITHER, FILE_ANY_ACCESS)

// READ_SENSOR
// Input:  ULONG Sensor index 0..11
// Output: ULONG Value 12-bit

// RELAY_CONTROL
// Input:  ULONG Relay Index 0..1, BOOL SwitchOn
// Output: None

// POWER_CONTROL
// Input:  BOOL PowerOn
// Output: None

// RESET_ADAPTER
// Input:  None
// Output: None

// DEVICE_INFO
// Input:  None
// Output: EWCLIDT_DEVICE_INFO (see below)

// RESET_SPI
// Input:  None
// Output: None

typedef struct _EWCLIDT_RELAY_CONTROL {
    ULONG   RelayIndex;
    ULONG   SwitchOn;
} EWCLIDT_RELAY_CONTROL, *PEWCLIDT_RELAY_CONTROL;

typedef struct _EWCLIDT_DEVICE_INFO {
    ULONG   NumberOfRelays;
    ULONG   NumberOfSensors;
} EWCLIDT_DEVICE_INFO, *PEWCLIDT_DEVICE_INFO;

extern "C" const GUID __declspec(selectany) InterfaceClassGuidEwclidT =
{0x5528ff87, 0x9f9a, 0x11d6, {0x93, 0x70, 0x00, 0xc0, 0xdf, 0x0f, 0xff, 0xa0}};

//---------------------------------------------------------------------------

HANDLE GetEwclidHandle()
{
 SP_DEVINFO_DATA          sDevInfoData;  // Device info
 sDevInfoData.cbSize     = sizeof(SP_DEVINFO_DATA);

 SP_DEVICE_INTERFACE_DATA sDevItfData;   // Device interface data
 sDevItfData.cbSize      = sizeof(SP_DEVICE_INTERFACE_DATA);

 TCHAR                    tszDevInstId[MAX_INSTRUCTION_LEN];

 REFIID   riidDevItf  = InterfaceClassGuidEwclidT;
 HDEVINFO hDevInfoSet = ::SetupDiGetClassDevs(&riidDevItf, 0, 0, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);

 if (hDevInfoSet != INVALID_HANDLE_VALUE)
   {
    // Enumerate all devices in device info set
    for (DWORD iIndex = 0; ::SetupDiEnumDeviceInfo(hDevInfoSet, iIndex, &sDevInfoData); iIndex++)
       {
        ::SetupDiGetDeviceInstanceId(hDevInfoSet, &sDevInfoData, tszDevInstId, sizeof(tszDevInstId), 0);

        // Retrieve device interface data structure
        if (::SetupDiEnumDeviceInterfaces(hDevInfoSet, &sDevInfoData, &riidDevItf, 0, &sDevItfData))
          {
           // Retrieve symbolic link to device object
           DWORD cbAlloc = 0;
           ::SetupDiGetDeviceInterfaceDetail(hDevInfoSet, &sDevItfData, 0, 0, &cbAlloc, 0);
           if (::GetLastError() == ERROR_INSUFFICIENT_BUFFER)
             {
              PSP_DEVICE_INTERFACE_DETAIL_DATA pDevItfDetData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(cbAlloc);
              pDevItfDetData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
              pDevItfDetData->DevicePath[0] = 0;
              ::SetupDiGetDeviceInterfaceDetail(hDevInfoSet, &sDevItfData, pDevItfDetData, cbAlloc, 0, 0);

              // Finally try to open device object
              return ::CreateFile(pDevItfDetData->DevicePath, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
             }
          }

       }
   }
 return INVALID_HANDLE_VALUE;
}

//---------------------------------------------------------------------------

DWORD GetNumberOfRelays(IN HANDLE hDevice, OUT ULONG* pulNumberOfRelays)
{
    DWORD cb;                               // Number of bytes read (unused)
    DWORD lDosError = NO_ERROR;             // Assume no errors
    EWCLIDT_DEVICE_INFO info;               // Packet

    if (::DeviceIoControl(
            hDevice,
            IOCTL_EWCLIDT_DEVICE_INFO,
            NULL,
            0,
            &info,
            sizeof(info),
            &cb,
            NULL
            ) == FALSE)
        lDosError = ::GetLastError();
    else
        *pulNumberOfRelays = info.NumberOfRelays;
    return lDosError;
}

//---------------------------------------------------------------------------

DWORD RelayControl(IN HANDLE hDevice, IN ULONG ulIndex, IN bool bOn)
{
    DWORD cb;                               // Number of bytes read (unused)
    DWORD lDosError = NO_ERROR;             // Assume no errors
    EWCLIDT_RELAY_CONTROL ctrl;             // Packet
    ctrl.RelayIndex = ulIndex;
    ctrl.SwitchOn   = bOn;

    if (::DeviceIoControl(
            hDevice,
            IOCTL_EWCLIDT_RELAY_CONTROL,
            &ctrl,
            sizeof(ctrl),
            NULL,
            0,
            &cb,
            NULL
            ) == FALSE)
        lDosError = ::GetLastError();
    return lDosError;
}

//---------------------------------------------------------------------------