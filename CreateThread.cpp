#include <windows.h>
#include <iostream>

using namespace std;

DWORD WINAPI threadFun(LPVOID lpParam)
{
    cout << "thread running..." << endl;
}

int main()
{
    HANDLE hThread;
    DWORD threadID;

    hThread = CreateThread(NULL,
                           0,
                           threadFun,
                           NULL,
                           0,
                           &threadID);

    if(hThread == NULL)
    {
        cout << "CreateThread - error: " << GetLastError << endl;
    }else
    {
        cout << "CreateThread - sucess..." << endl;
        cout << "threadID: " << threadID << endl;
        CloseHandle(hThread);
    }

    system("pause");
    return 0;
}
