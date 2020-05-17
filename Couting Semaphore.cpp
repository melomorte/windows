#include <windows.h>
#include <iostream>

using namespace std;

HANDLE hSemaphore;

DWORD WINAPI ThreadFun()
{
    DWORD dwWaitResult;
    BOOL bCondition = TRUE;
    while(bCondition)
    {
        dwWaitResult = WaitForSingleObject(hSemaphore, INFINITE);
        switch(dwWaitResult)
        {
        case WAIT_OBJECT_0:
            cout << "ThreadID - " << GetCurrentThreadId() << endl;
            bCondition = FALSE;

            Sleep(5000);

            ReleaseSemaphore(hSemaphore, 1 ,0);
            break;
        case WAIT_TIMEOUT:
            cout << "Wait Timeout ThreadID - " << GetCurrentThreadId() << endl;
            break;
        default:
            break;
        }
    }
    return 0;
}

int main()
{
    //local variable.
    HANDLE hThread[8];
    DWORD ThreadID;

    //step - 1: create counting semaphore.
    hSemaphore = CreateSemaphore(NULL,
                                 5,
                                 5,
                                 NULL);

    if(hSemaphore == NULL)
    {
        cout << "create semaphore - failed: " << endl;
    }
    cout << "create semaphore - sucess..." << endl;

    //step - 2: Create 8 Threads.
    for(size_t i = 0;i < 8; i++)
    {
        hThread[i] = CreateThread(NULL,
                                  0,
                                  &ThreadFun,
                                  NULL,
                                  0,
                                  &ThreadID);
    }

    //step - 3: wait for all threads to terminate.
    WaitForMultipleObjects(8, hThread, TRUE, INFINITE);

    //step - 4: close handle for thread.
    for(size_t i = 0;i < 8; i++)
    {
        CloseHandle(hThread[i]);
    }

    //step - 5: close for semaphore.
    CloseHandle(hSemaphore);


    system("pause");
    return 0;
}
