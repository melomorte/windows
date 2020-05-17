#include <windows.h>
#include <iostream>

using namespace std;

//Global Handle for Semaphore.
HANDLE hSemaphore;

//Thread Function.
DWORD WINAPI myFun(LPVOID lpParam)
{
    WaitForSingleObject(hSemaphore, INFINITE);
    cout << "CRITICAL SECTION" << endl;
    cout << "----------------" << endl;
    ReleaseSemaphore(hSemaphore, 1, 0);
    return 0;
}

int main()
{
    //local variable.
    HANDLE hThread1;
    HANDLE hThread2;

    //step - 1: Create Semaphore.
    hSemaphore = CreateSemaphore(NULL,  //security attributes.
                                 1,     //initial state.
                                 1,     //no of resources.
                                 NULL); //

    if(NULL == hSemaphore)
    {
        cout << "Create Semaphore - Failed: " << GetLastError() << endl;
    }
    cout << "Create Semaphore - Sucess..." << endl;

    //step - 2.1: Create Thread - 1.
    hThread1 = CreateThread(NULL,    //security attributes.
                            0,       //stack size.
                            &myFun,  //start function.
                            NULL,    //thread parameter.
                            0,       //create flags.
                            0);      //thread ID.

    //step - 2.2: Create Thread - 2.
    hThread2 = CreateThread(NULL,    //security attributes.
                            0,       //stack size.
                            &myFun,  //start function.
                            NULL,    //thread parameter.
                            0,       //create flags.
                            0);      //thread ID.

    if((hThread1 == NULL)&&(hThread2 == NULL))
    {
        cout << "thread1 and thread2 - Failed: " << GetLastError() << endl;
    }
    cout << "Create Thread1 and Thread2 - Sucess...\n" << endl;

    //step - 3: wait for single object.
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    //step - 4: close handle for thread.
    CloseHandle(hThread1);
    CloseHandle(hThread2);

    //step - 5: close handle for semaphore.
    CloseHandle(hSemaphore);

    system("pause");
    return 0;
}
