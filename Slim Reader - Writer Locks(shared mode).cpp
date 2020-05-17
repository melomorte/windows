#include <windows.h>
#include <iostream>

using namespace std;

//Global variable
condition_variable  cvw;
condition_variable  cvr;
SRWLOCK lock;
int x = 0;
int readercount = 0;


DWORD WINAPI WriteThread(LPVOID lpvoid)
{
    while(1)
    {
        AcquireSRWLockShared(&lock);
        x = x + 5;
        cout << "writer - " << x << endl;
        ReleaseSRWLockShared(&lock);
        WakeConditionVariable(&cvr);
        Sleep(1500);
    }
    return 0;
}

DWORD WINAPI ReadThread(LPVOID lpvoid)
{
    while(1)
    {
        AcquireSRWLockShared(&lock);
        ++readercount;
        if(readercount == 1)
        {
            SleepConditionVariableSRW(&cvw, &lock, INFINITE, CONDITION_VARIABLE_LOCKMODE_SHARED);
        }
        ReleaseSRWLockShared(&lock);

        cout << "reader - " << x << endl;

        AcquireSRWLockShared(&lock);

        --readercount;

        if(readercount == 0)
        {
            TryAcquireSRWLockShared(&lock);
        }

        ReleaseSRWLockShared(&lock);

        Sleep(1500);
    }
    return 0;
}

int main()
{
    //local variable
    HANDLE hWriter;
    HANDLE hReade[2];

    //step - 1: initialize conditional variable for writer and read
    InitializeConditionVariable(&cvw);
    InitializeConditionVariable(&cvr);

    //step - 2: initialize SRW lock
    InitializeSWRLock(&lock);

    //step - 3: Create Writer Thread
    hWriter = CreateThread(NULL,
                           0,
                           &WriteThread,
                           NULL,
                           0,
                           0);

    //step - 4: Create 2 Reader thread
    for(int i = 0; i < 2; i++)
    {
        hRead[i] = CreateThread(NULL,
                                0,
                                &ReadThread,
                                NULL,
                                0,
                                0);
    }

    //step - 5: wake up all conditional variable
    WakeAllConditionVariable(&cvw);
    WakeAllConditionVariable(&cvr);

    //step - 6: wait for single object for  reader and writer
    WaitForSingleObject(hWriter, INFINITE);
    for(int i = 0;i < 2;i++)
    {
        WaitForSingleObject(hRead, INFINITE);
    }

    //step - 7: Close handle for write Thread & read thread
    CloseHandle(hWriter);
    for(int i = 0;i < 2;i++)
    {
        CloseHandle(hRead[i]);
    }


    system("pause");
    return 0;
}
