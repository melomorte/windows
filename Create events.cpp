#include <windows.h>
#include <iostream>

using namespace std;

//global variables
HANDLE hEvent;

//thread fun
DWORD WINAPI ThreadFun1(LPVOID lpParam)
{
    WaitForSingleObject(hEvent, INFINITE);
    cout << "Thread - 1: running..." << endl;
    Beep(823,500); //make a beep - 823 = hertz, 500 = milliseconds.
    return 0;
}

DWORD WINAPI ThreadFun2(LPVOID lpParam)
{
    cout << "Thread - 2: running..." << endl;
    SetEvent(hEvent);
    return 0;
}

int main()
{
    HANDLE hThread, hThread2;
    DWORD ThreadID1, ThreadID2;

    //step - 1: create an event
    hEvent = CreateEvent(NULL,
                         FALSE,
                         FALSE,
                         TEXT("my event"));

    if(hEvent == NULL)
    {
        cout << "Create event - failed: " << endl;
    }
    cout << "Create event - sucess..." << endl;

    //step - 2: create thread
    hThread = CreateThread(NULL,
                           0,
                           ThreadFun1,
                           NULL,
                           0,
                           &ThreadID1);

    if(hThread == NULL)
    {
        cout << "Create thread - failed: " << endl;
    }
    cout << "Create thread - sucess..." << endl;

    hThread2 = CreateThread(NULL,
                           0,
                           ThreadFun2,
                           NULL,
                           0,
                           &ThreadID2);

    if(hThread2 == NULL)
    {
        cout << "Create thread 2 - failed: " << endl;
    }
    cout << "Create thread 2 - sucess..." << endl;

    //step - 3: wait for single object
    WaitForSingleObject(hThread, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    //step - 4: Close Handle
    CloseHandle(hThread);
    CloseHandle(hThread2);

    //step - 5: Close Handle for ahn event
    CloseHandle(hEvent);


    system("pause");
    return 0;
}
