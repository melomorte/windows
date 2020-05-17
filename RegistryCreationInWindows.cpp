#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    LONG lReg;
    HKEY hKey;
    DWORD dwData = 1234;

    lReg = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
                          TEXT("SOFTWARE\\Test\\Product\\SmartId"),
                          0,
                          NULL,
                          REG_OPTION_NON_VOLATILE,
                          KEY_ALL_ACCESS,
                          NULL,
                          &hKey,
                          NULL);

    lReg = RegSetValueEx(hKey,
                         TEXT("VALUE"),
                         NULL,
                         REG_DWORD,
                         (LPBYTE)&dwData,
                         sizeof(dwData)
                         );

    if(lReg != ERROR_SUCCESS)
    {
        cout << "regCreatKeyEx - failed: " << GetLastError() << endl;
    }else
    {
        cout << "regCreatKeyEx - sucess..." << endl;
        RegCloseKey(hKey);
    }
    system("pause");
    return 0;
}
