#include <windows.h>
#include <iostream>

using namespace std;

HANDLE hMutex;
int gcount = 1;

DWORD WINAPI threadFun(LPVOID lpParam)
{
    while(gcount < 10)
    {
        WaitForSingleObject(hMutex, INFINITE);
        if(gcount%2 == 0)
        {
            cout << "thread - " << gcount++ << endl;
        }
        ReleaseMutex(hMutex);
    }
    //cout << "thread running" << endl;
    return 0;
}

DWORD WINAPI threadFun2(LPVOID lpParam)
{
    while(gcount < 10)
    {
        WaitForSingleObject(hMutex, INFINITE);
        if(gcount%2 == 1)
        {
            cout << "thread2 - " << gcount++ << endl;
        }
        ReleaseMutex(hMutex);
    }
    //cout << "thread2 running" << endl;
    return 0;
}

int main()
{
    HANDLE hThread, hThread2;

    hMutex = CreateMutex(  NULL,
                           FALSE,
                           NULL);

    hThread = CreateThread(NULL,
                           0,
                           threadFun,
                           NULL,
                           0,
                           NULL);

    hThread2 = CreateThread(NULL,
                           0,
                           threadFun2,
                           NULL,
                           0,
                           NULL);

    CloseHandle(hThread);
    CloseHandle(hThread2);


    system("pause");
    return 0;
}
