//ATENÇÃO:POSSUI ERROS QUE SERÃO CORRIGIDOS EM BREVE.
//WARNING: IT HAS ERRORS THAT WILL BE CORRECTED SOON.

#include <windows.h>
#include <iostream>
#include <tlhelp32.h> //snapshot.
#include <string>

using namespace std;

int main()
{
    cout << "................................................................." << endl;
    cout << "......................LIST OF PROCESS............................" << endl;

    //local variable.
    HANDLE hSnapShot = INVALID_HANDLE_VALUE;
    PROCESSENTRY32 ProcessInfo = {0};//process entry structure.
    ProcessInfo.dwSize = sizeof(PROCESSENTRY32);
    int count = 0;

    //step - 1: create tool help 32 snapshot function.
    hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, 0);

    if(INVALID_HANDLE_VALUE == hSnapShot)
    {
        cout << "Create tool help snapshot - Failed: " << GetLastError() << endl;
    }
    cout << "Create tool help snapshot - sucess..." << endl;

    //step - 2: process 32 next function.
    while(Process32Next(hSnapShot, &ProcessInfo)== FALSE)
    {
        cout << ".........................." << endl;
        cout << "\t Process NO: " << ++count << endl;
        cout << ".........................." << endl;
        cout << "NO. of Thread: " << ProcessInfo.cntThreads << endl;
        cout << "NO. of Thread: " << ProcessInfo.dwSize << endl;
        cout << "PRIORITY: " << ProcessInfo.pcPriClassBase << endl;
        wcout << "EXECUTE: " << ProcessInfo.szExeFile << endl;
        cout << "PPID: " << ProcessInfo.th32ParentProcessID << endl;
        cout << "PID: " << ProcessInfo.th32ProcessID << endl;
    }

    //step - 3: Close handle function.
    CloseHandle(hSnapShot);
    cout << "................................................................." << endl;


    system("pause");
    return 0;
}
