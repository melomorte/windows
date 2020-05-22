#include <windows.h>
#include <iostream>

using namespace std;

//global handle for semaphore and mutex.
HANDLE hSemaphore;
HANDLE hMutex;

int i = 0;

//Thread function.
DWORD WINAPI MyThread(LPVOID lpParam)
{
    while(i < 20)
    {
        WaitForSingleObject(hSemaphore, INFINITE);
        WaitForSingleObject(hMutex, INFINITE); //mutex lock

        cout << "count = " << ++i << endl;
        ReleaseMutex(hMutex);                  //mutex unlock.
        ReleaseSemaphore(hSemaphore, 1, 0);
        Sleep(2000);
    }
    return 0;
}

int main()
{
    //local variable.
    HANDLE hThread1;
    HANDLE hThread2;

    //step - 1: create semaphore.
    hSemaphore = CreateSemaphore(NULL,
                                 2,
                                 2,
                                 NULL);

    if(NULL == hSemaphore)
    {
        cout << "Semaphore creation - failed: " << GetLastError() << endl;
    }
    cout << "Semaphore creation - sucess..." << endl;

    //step - 2: Mutex creation.

    if(NULL == hMutex)
    {
        cout << "create mutex - failed: " << GetLastError() << endl;
    }
    cout << "create mutex - sucess..." << endl;

    //step - 3: create thread.
    hThread1 = CreateThread(NULL,
                            0,
                            &MyThread,
                            NULL,
                            0,
                            0);

    hThread2 = CreateThread(NULL,
                            0,
                            &MyThread,
                            NULL,
                            0,
                            0);

    //step - 4: wait for single object.
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    //step - 5: close handle.
    CloseHandle(hThread1);
    CloseHandle(hThread2);

    //step - 6: close handle for mutex.
    CloseHandle(hMutex);

    //step - 7: close handle for semaphore.
    CloseHandle(hSemaphore);

    system("pause");
    return 0;
}
