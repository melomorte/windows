#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int criar()
{

    STARTUPINFO startInfo = {0};

    PROCESS_INFORMATION processInfo = {0};

    BOOL bSucces = CreateProcess(TEXT("C:\\windows\\notepad.exe"),
                                 NULL,
                                 NULL,
                                 NULL,
                                 FALSE,
                                 NULL,
                                 NULL,
                                 NULL,
                                 &startInfo,
                                 &processInfo);

    if(bSucces){
        cout << "process started" << endl;
        cout << "process ID:\t" << processInfo.dwProcessId;
    }
    else{
        cout << "error to start the process" << GetLastError() << endl;
    }

    cin.get();

return 0;
}

int main()
{
    //ShowWindow(NULL ,SW_HIDE);
    criar();
    //ShowWindow(NULL , SW_RESTORE);

    return 0;
}
