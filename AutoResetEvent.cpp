#include <windows.h>
#include <iostream>
#include <stdio.h> //only sound: beep

using namespace std;

//global variable
HANDLE hEvent;

//thread fun
DWORD WINAPI ThreadFun(LPVOID lpParam)
{
    HANDLE hOpenEvent;
    hOpenEvent = OpenEvent(EVENT_ALL_ACCESS,
                           FALSE,
                           TEXT("my event"));

    if(hOpenEvent == FALSE)
    {
        cout << "Open Event - failed: " << endl;
    }
    cout << "Open Event - sucess..." << endl;

    for(int i = 1; i <= 2; i++)
    {
        WaitForSingleObject(hEvent, INFINITE);
        cout << "got: " << i << endl;
    }

    cout << "Thread - 1: running..." << endl;
    return 0;
}

DWORD WINAPI ThreadFun2(LPVOID lpParam)
{
    cout << "Thread - 2: running..." << endl;

    for(int i = 1; i <= 2; i++)
    {
        SetEvent(hEvent);
        Sleep(2000);
        putchar(7); //beep
    }
    return 0;
}

int main()
{
    cout << "......AUTO RESET......" << endl;
    cout << endl;

    HANDLE hThread, hThread2;
    DWORD ThreadID1, ThreadID2;

    //step - 1: create an event
    hEvent = CreateEvent(NULL,
                         FALSE,
                         FALSE,
                         TEXT("my event"));

    if(hEvent == NULL)
    {
        cout << "Create Event - failed: " << endl;
    }
    cout << "Create Event - sucess..." << endl;

    //step - 2: create thread - 1;
    hThread = CreateThread(NULL,
                           0,
                           ThreadFun,
                           NULL,
                           0,
                           &ThreadID1);

    if(hThread == NULL)
    {
        cout << "Create Thread - 1: failed! " << endl;
    }
    cout << "Create Thread - 1: sucess..." << endl;

    //step - 2.2: create thread - 2;
    hThread2 = CreateThread(NULL,
                           0,
                           ThreadFun2,
                           NULL,
                           0,
                           &ThreadID2);

    if(hThread2 == NULL)
    {
        cout << "Create Thread - 2: failed! " << endl;
    }
    cout << "Create Thread - 2: sucess..." << endl;

    //step - 3: wait for single object;
    WaitForSingleObject(hThread, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    //step - 4: close handle;
    CloseHandle(hThread);
    CloseHandle(hThread2);

    //step - 5: close handle for an event;
    CloseHandle(hEvent);


    system("pause");
    return 0;
}
