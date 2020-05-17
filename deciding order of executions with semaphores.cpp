#include <windows.h>
#include <iostream>

using namespace std;

//FUNCTIONS DECLARED.
//void tError(HANDLE);
//void sError(HANDLE);

//global handle for semaphore.
HANDLE hSemaphore1;
HANDLE hSemaphore2;
HANDLE hSemaphore3;

//all thread functions.
DWORD WINAPI ThreadFun1(LPVOID lpParam)
{
    WaitForSingleObject(hSemaphore2, INFINITE);
    cout << "Thread - 1" << endl;
    ReleaseSemaphore(hSemaphore3, 1, 0);
    return 0;
}

DWORD WINAPI ThreadFun2(LPVOID lpParam)
{
    WaitForSingleObject(hSemaphore1, INFINITE);
    cout << "Thread - 2" << endl;
    ReleaseSemaphore(hSemaphore2, 1, 0);
    return 0;
}

DWORD WINAPI ThreadFun3(LPVOID lpParam)
{
    WaitForSingleObject(hSemaphore3, INFINITE);
    cout << "Thread - 3" << endl;
    return 0;
}

DWORD WINAPI ThreadFun4(LPVOID lpParam)
{
    cout << "thread - 4" << endl;
    ReleaseSemaphore(hSemaphore1, 1, 0);
    return 0;
}

int main()
{
    //handle for threads.
    HANDLE hThread1;
    HANDLE hThread2;
    HANDLE hThread3;
    HANDLE hThread4;

    //step - 1: Create 3 semaphores.
    //semaphore 1
    hSemaphore1 = CreateSemaphore(NULL,     //security attributes.
                                  0,        //initial count.
                                  1,        //max count.
                                  NULL);    //semaphore name.

    //cout << "Create Semaphore: 1";
    //tError(hSemaphore1);

    //semaphore 2.
    hSemaphore2 = CreateSemaphore(NULL,     //security attributes.
                                  0,        //initial count.
                                  1,        //max count.
                                  NULL);    //semaphore name.

    //cout << "Create Semaphore: 1";
    //tError(hSemaphore1);

    //semaphore 3.
    hSemaphore3 = CreateSemaphore(NULL,     //security attributes.
                                  0,        //initial count.
                                  1,        //max count.
                                  NULL);    //semaphore name.

    //cout << "Create Semaphore: 1";
    //tError(hSemaphore1);

    //create threads.
    //thread - 1;
    hThread1 = CreateThread(NULL,       //security attributes.
                            0,          //stack size.
                            &ThreadFun1,//thread start function.
                            NULL,       //thread parameter.
                            0,          //creation flag.
                            0);         //thread ID.

    //cout << "Create Thread: 1";
    //tError(hThread1);

    //thread - 2;
    hThread2 = CreateThread(NULL,       //security attributes.
                            0,          //stack size.
                            &ThreadFun2,//thread start function.
                            NULL,       //thread parameter.
                            0,          //creation flag.
                            0);         //thread ID.

    //cout << "Create Thread: 2";
    //tError(hThread2);

    //thread - 3;
    hThread3 = CreateThread(NULL,       //security attributes.
                            0,          //stack size.
                            &ThreadFun3,//thread start function.
                            NULL,       //thread parameter.
                            0,          //creation flag.
                            0);         //thread ID.

    //cout << "Create Thread: 3";
    //tError(hThread3);

    //thread - 4;
    hThread4 = CreateThread(NULL,       //security attributes.
                            0,          //stack size.
                            &ThreadFun4,//thread start function.
                            NULL,       //thread parameter.
                            0,          //creation flag.
                            0);         //thread ID.

    //cout << "Create Thread: 4";
    //tError(hThread4);

    //step - 3: wait for single object.
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);
    WaitForSingleObject(hThread3, INFINITE);
    WaitForSingleObject(hThread4, INFINITE);

    //step - 5: close handle.
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    CloseHandle(hThread3);
    CloseHandle(hThread4);

    //Close handle for all semaphores.
    CloseHandle(hSemaphore1);
    CloseHandle(hSemaphore2);
    CloseHandle(hSemaphore3);


    system("pause");
    return 0;
}

//void tError(HANDLE)
//{
//    //local variable.
//    HANDLE hThread;
//
//    if(hThread == NULL)
//    {
//        cout << " - faied: " << GetLastError() << endl;
//    }
//    else
//    {
//        cout << "- sucess..." << endl;
//    }
//}
//
//void sError(HANDLE)
//{
//    //local variable.
//    HANDLE hSemaphore;
//
//    if(NULL == hSemaphore)
//    {
//        cout << "- sucess..." << endl;
//    }
//    else
//    {
//        cout << " - faied: " << GetLastError() << endl;
//    }
//}
