#pragma warning(disable : 4996)

#define WINVER 0x0A00

#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

using namespace std;


#define MAX_KEY_LENGTH 255
#define INFO_BUFFER_SIZE 32767
#define BUFSIZE MAX_PATH
#define FILESYSNAMEBUFSIZE MAX_PATH
int main()
{
    //punkt1
    OSVERSIONINFO osvi;
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);
    printf("Version OS: %i.%i\n\n", osvi.dwMajorVersion, osvi.dwMinorVersion);

    //punk2
    TCHAR szPath[_MAX_PATH] = { 0 };
    UINT iRet = GetSystemDirectory(szPath, _MAX_PATH);
    printf("Result %d\n", iRet);
    char buffer[256];
    DWORD size = 256;
    GetComputerNameA(buffer, &size);
    printf("%s\n", buffer);
    GetUserNameA(buffer, &size);
    printf("%s\n", buffer);

    //punkt4
    char buffer[MAX_PATH + 1];
    DWORD  CBufLen = MAX_PATH;
    char buff1[MAX_PATH + 1];
    CHAR VolumeName[MAX_PATH];
    __int64 total, available, free;


    HANDLE search = FindFirstVolumeA(VolumeName, BUFSIZE);
    printf("\n      %s", VolumeName);

    do {
        printf("\n      %s", buff1);
        GetVolumePathNamesForVolumeNameA(buff1, buffer, CBufLen, &CBufLen);
        char* path = buffer;
        printf("\npath: %s", path);
        GetDiskFreeSpaceExA(buffer, (PULARGE_INTEGER)&available, (PULARGE_INTEGER)&total, (PULARGE_INTEGER)&free);
        printf("\nsize: %ll  bytes ", total);
        printf("\nFree space: %ll  bytes\n", available);

    } while (FindNextVolumeA(search, buff1, BUFSIZE));
    FindVolumeClose(search);

    //punkt5
    DWORD dwSize;
    TCHAR szName[MAX_KEY_LENGTH];
    LPSTR lpValueName;
    HKEY hKey;
    DWORD dwIndex = 0;
    DWORD retCode;
    DWORD BufferSize = 8192;
    TCHAR PerfData[MAX_KEY_LENGTH];
    DWORD cbData = BufferSize;

    (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
        0, KEY_ALL_ACCESS, &hKey);
    printf("\n1.5.  Startup commands:\n");
    while (1) {
        dwSize = sizeof(szName);
        retCode = RegEnumValue(hKey, dwIndex, szName, &dwSize, NULL, NULL, NULL, NULL);
        if (retCode == ERROR_SUCCESS)
        {
            RegQueryValueEx(hKey, szName, NULL, NULL, (LPBYTE)PerfData, &cbData);
            printf("      %d: %s:  %s\n", dwIndex + 1, szName, PerfData);
            dwIndex++;
        }
        else break;
    }

    RegCloseKey(hKey);
    return 0;
}
