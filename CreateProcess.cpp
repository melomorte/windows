#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    HANDLE hProcess;
    HANDLE hThread;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD dwProcessId = 0;
    DWORD dwThreadId = 0;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&si, sizeof(pi));

    BOOL bCreateaprocess;

    bCreateaprocess = CreateProcess(TEXT("C:\\windows\\notepad.exe"),
                                    NULL,
                                    NULL,
                                    NULL,
                                    FALSE,
                                    NULL,
                                    NULL,
                                    NULL,
                                    &si,
                                    &pi);

    if(bCreateaprocess == FALSE)
    {
        cout << "CreatProcess - failed: " << GetLastError() << endl;
    }else
    {
        cout << "CreatProcess - sucess..." << endl;
        cout << "process ID: " << pi.dwProcessId << endl;
        cout << "thread ID: " << pi.dwThreadId << endl;
        //cout << "GetProcessId -> " << GetProcessId(pi.hProcess) << endl;
       // cout << "GetThreadId -> " << GetThreadId(pi.hThread) << endl;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);


    system("pause");
    return 0;
}
