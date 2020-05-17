#include <windows.h>
#include <iostream>

using namespace std;

//global variable
int gcount = 1;
CRITICAL_SECTION cs;

//thread function
DWORD WINAPI ThreadFunEven(LPVOID lpParam)
{
    while(gcount < 10)
    {
        EnterCriticalSection(&cs);
        if(gcount%2==0)
        {
            cout << "even: " << gcount++ << endl;
        }
        LeaveCriticalSection(&cs);
    }
    return 0;
}

DWORD WINAPI ThreadFun0dd(LPVOID lpParam)
{
    while(gcount < 10)
    {
        EnterCriticalSection(&cs);
        if(gcount%2==1)
        {
            cout << "0dd: " << gcount++ << endl;
        }
        LeaveCriticalSection(&cs);
    }
    return 0;
}

int main()
{
    cout << ".......CRITICAL SECTION......." << endl;

    //local variable
    HANDLE hThread, hThread2;

    //step - 1: initialize the CRITICAL SECTION
    InitializeCriticalSection(&cs);

    //step - 2: create thread fun
    hThread = CreateThread(NULL,
                           0,
                           ThreadFunEven,
                           NULL,
                           0,
                           NULL);

    hThread2 = CreateThread(NULL,
                            0,
                            ThreadFun0dd,
                            NULL,
                            0,
                            NULL);

    //step - 3: wait for signaled object
    WaitForSingleObject(hThread, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    //step - 4: closing the handle of thread
    CloseHandle(hThread);
    CloseHandle(hThread2);

    //step - 5: deleting the critical section object
    DeleteCriticalSection(&cs);

    system("pause");
    return 0;
}
