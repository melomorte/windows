#include <windows.h>
#include <iostream>

using namespace std;

//Global Variable
SRWLOCK lock;
int flag = 0;
int x = 0;

//thread function
DWORD WINAPI WriterThread(LPVOID lpVoid)
{
    while(1)
    {
        AcquireSRWLockExclusive(&lock);
        x = x + 5;
        cout << "Writer - " << x << endl;
        RealeseSRWLockExclusive(&lock);
        Sleep(1500);
    }
    return 0;
}

DWORD WINAPI ReadThread(LPVOID lpVoid)
{
    while(1)
    {
        AcquireSRWLockExclusive(&lock);
        ++flag;
        if(flag == 1)
        {
            cout << "Reader - " << x << endl;
        }
        --flag;
        RealeseSRWLockExclusive(&lock);
        Sleep(1500);
    }
    return 0;
}

int main()
{
    //local variable
    HANDLE hWriter;
    HANDLE hRead;

    //step - 1: initialize SRW lock
    InitializeSRWLock(&lock);

    //step - 2: CreateThread
    hWriter = CreateThread(NULL,
                           0,
                           &WriterThread,
                           NULL,
                           0,
                           0);

    hReader = CreateThread(NULL,
                           0,
                           &ReadThread,
                           NULL,
                           0,
                           0);

    //step - 3: wait for single object
    WaitForSingleObject(hWriter, INFINITE);
    WaitForSingleObject(hReader, INFINITE);

    //step - 4: Close Handle
    CloseHandle(hWriter);
    CloseHandle(hRead);


    system("pause");
    return 0;
}
