#include <windows.h>
#include <tchar.h>
#include <iostream>

using namespace std;

int main()
{
    //local variable.
    DWORD dGetTempPath = 0;
    UINT uTempFileName = 0;
    TCHAR tTempPath[MAX_PATH];
    TCHAR tTempFile[MAX_PATH];

    //step - 1: get temp file path.
    dGetTempPath = GetTempPath(MAX_PATH, tTempPath);

    if(0 == dGetTempPath)
    {
        cout << "Get Temp File Path - failed: " << GetLastError() << endl;
    }
    cout << "Get Temp File Path - sucess..." << endl;

    //step - 2: generate a temporary file name.
    uTempFileName = GetTempFileName(tTempPath,
                                    TEXT("MELOMORTE"),
                                    0,
                                    tTempFile);

    if(0 == uTempFileName)
    {
        cout << "Temp File Name - failed: " << GetLastError() << endl;
    }
    cout << "Temp File Name - sucess..." << endl;


    system("pause");
    return 0;
}
