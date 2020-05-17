#include <windows.h>
#include <iostream>

using namespace std;

//global handle for semaphore.
HANDLE hSemaphore;

//global variable.
int a, b, c;

//thread functions.
DWORD WINAPI InputFun(LPVOID lpParam)
{
    cout << "Enter first no: " << endl;
    cin >> a;
    cout << "Enter second no: " << endl;
    cin >> b;

    Sleep(200);
    ReleaseSemaphore(hSemaphore, 1, 0);
    return 0;
}

DWORD WINAPI OutputFun(LPVOID lpParam)
{
    WaitForSingleObject(hSemaphore, INFINITE);
    c = a + b;
    cout << "Addition - " << c << endl;
    Beep(1200,300);
    return 0;
}

int main()
{
    //Local variable.
    HANDLE hThread1;
    HANDLE hThread2;

    //step - 1: Create Semaphore.
    hSemaphore = CreateSemaphore(NULL,  //security attributes.
                                 0,     //no signaled state.
                                 1,     //max count.
                                 NULL); //

    if(NULL == hSemaphore)
    {
        cout << "Create Semaphore - Failed: " << GetLastError() << endl;
    }
    cout << "Create Semaphore - Sucess..." << endl;

    //step - 2.1: Create Thread - 1.
    hThread1 = CreateThread(NULL,    //security attributes.
                            0,       //stack size.
                            &InputFun,  //start function.
                            NULL,    //thread parameter.
                            0,       //create flags.
                            0);      //thread ID.

    //step - 2.2: Create Thread - 2.
    hThread2 = CreateThread(NULL,    //security attributes.
                            0,       //stack size.
                            &OutputFun,  //start function.
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

    system ("pause");
    return 0;
}
