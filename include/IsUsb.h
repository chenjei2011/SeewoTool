#include <windows.h>
#include <setupapi.h>
#include <cfgmgr32.h>
#include <initguid.h>
#include <devguid.h>
#include <iostream>
#pragma comment(lib, "setupapi.lib")
#pragma comment(lib, "cfgmgr32.lib")

// ---------- 下面是你之前给的 IsUsb 实现 ----------
static bool IsUsbDisk(wchar_t letter)
{
    wchar_t vol[8] = L"\\\\.\\X:";
    vol[4] = letter;
    HANDLE h = CreateFileW(vol, 0, FILE_SHARE_READ | FILE_SHARE_WRITE,
                           nullptr, OPEN_EXISTING, 0, nullptr);
    if (h == INVALID_HANDLE_VALUE) return false;
    STORAGE_PROPERTY_QUERY q{};
    q.PropertyId = StorageDeviceProperty;
    q.QueryType  = PropertyStandardQuery;
    BYTE buf[1024] = {};
    DWORD read = 0;
    bool usb = false;
    if (DeviceIoControl(h, IOCTL_STORAGE_QUERY_PROPERTY,
                        &q, sizeof(q), buf, sizeof(buf), &read, nullptr)) {
        auto* devDesc = (STORAGE_DEVICE_DESCRIPTOR*)buf;
        if (devDesc->BusType == BusTypeUsb) usb = true;
    }
    CloseHandle(h);
    return usb;
}

inline bool IsUsb()
{
    wchar_t drives[256];
    DWORD len = GetLogicalDriveStringsW(_countof(drives), drives);
    if (len == 0) return false;
    for (const wchar_t* p = drives; *p; p += wcslen(p) + 1) {
        wchar_t letter = p[0];
        UINT type = GetDriveTypeW(p);
        if (type == DRIVE_REMOVABLE && IsUsbDisk(letter))
            return true;
    }
    return false;
}
// ---------- IsUsb 结束 ----------

// 自动打开盘符
void OpenDrive(char letter)
{
    char path[8] = { letter, ':', '\\', '\0' };
    ShellExecuteA(nullptr, "open", path, nullptr, nullptr, SW_SHOWNORMAL);
    printf("已自动打开 U 盘 %c:\\\n", letter);
}

// 返回当前第一个 U 盘盘符，没有返回 0
char FirstUsbLetter()
{
    wchar_t drives[256];
    if (!GetLogicalDriveStringsW(_countof(drives), drives)) return 0;
    for (const wchar_t* p = drives; *p; p += wcslen(p) + 1) {
        wchar_t letter = p[0];
        if (GetDriveTypeW(p) == DRIVE_REMOVABLE && IsUsbDisk(letter))
            return (char)letter;
    }
    return 0;
}