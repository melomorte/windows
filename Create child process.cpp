#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    //local variable.
    HANDLE hProcess = 0;    //handle for process.
    HANDLE hThread = 0;     //Handle for thread.
    STARTUPINFO si;         //startup
    PROCESS_INFORMATION pi; //startup info
    DWORD dwProcessID = 0;
    DWORD dwThreadID = 0;
    BOOL bProcess;

    //step - 1: filling the memory block.
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));

    //step - 2: CreateProcess.
    bProcess = CreateProcess(TEXT("C:\\caminho\\CreateProcess.exe"), //name of application.
                             NULL,
                             NULL,
                             NULL,
                             FALSE,
                             0,
                             NULL,
                             NULL,
                             &si,
                             &pi);

    //step - 3: checking process has create or not.

    if(bProcess == FALSE)
    {
        cout << "Create Process - Failed: " << GetLastError() << endl;
    }
    cout << "Create Process - sucess..." << endl;

    //step -4: print he process and thread id.
    cout << "process ID: " << pi.dwProcessId << endl;
    cout << "process ID: " << pi.dwThreadId << endl;

    //step - 5: wait for single object.
    WaitForSingleObject(pi.hProcess, INFINITE);


    //step - 6: close handle.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    system("pause");
    return 0;
}
