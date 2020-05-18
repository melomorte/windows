#include <windows.h>
#include <iostream>
#include <winbase.h>

using namespace std;

//global variable.
HANDLE hOpenThread1, hOpenThread2;
DWORD dwThreadID1;
DWORD dwThreadID2;

//Thread function.
DWORD WINAPI ThreadFun1(LPVOID lpParam)
{
    if(dwThreadID1 == GetCurrentThreadId())
    {
        cout << "Thread - 1: running..." << endl;
    }

    return 0;
}

DWORD WINAPI ThreadFun2(LPVOID lpParam)
{
    if(dwThreadID2 == GetCurrentThreadId())
    {
        cout << "Thread - 2: running..." << endl;
    }

    return 0;
}

int main()
{
    //Local Variable.
    HANDLE hThread1, hThread2;
    int ThreadPriority1, ThreadPriority2;
	
    //step - 1: create thread function for thread1.
    hThread1 = CreateThread(NULL,
                            0,
                            &ThreadFun1,
                            NULL,
                            0,
                            &dwThreadID1);

    //step - 2: OpenThread function.
    hOpenThread1 = OpenThread(THREAD_SET_INFORMATION,
                              FALSE,
                              dwThreadID1);

    if(NULL == hOpenThread1)
    {
        cout << "OpenThread - Failed: " << GetLastError() << endl;
    }
    cout << "OpenThread - sucess..." << endl;

    //step - 3: set thread function.
    SetThreadPriority(hOpenThread1 ,-1);

    //step - 4: create thread function for thread2.
    hThread2 = CreateThread(NULL,
                            0,
                            &ThreadFun2,
                            NULL,
                            0,
                            &dwThreadID2);

    //step - 5: OpenThread function.
    hOpenThread2 = OpenThread(THREAD_SET_INFORMATION,
                              FALSE,
                              dwThreadID2);

    if(NULL == hOpenThread2)
    {
        cout << "OpenThread2 - Failed: " << GetLastError() << endl;
    }
    cout << "OpenThread2 - sucess..." << endl;

    //step - 6: set thread function.
    SetThreadPriority(hOpenThread2 , 2);

    //delay.
    Sleep(1000);

    //step - 7: get the thread.
    ThreadPriority1 = GetThreadPriority(hThread1);
    ThreadPriority1 = GetThreadPriority(hThread2);

    //step - 8: wait for single objects.
    WaitForSingleObject(hOpenThread1, INFINITE);
    WaitForSingleObject(hOpenThread2, INFINITE);


    cout << "1st - " << ThreadPriority1 << endl;
    cout << "2st - " << ThreadPriority2 << endl;

    //step - 9: close handle.
    CloseHandle(hOpenThread1);
    CloseHandle(hOpenThread2);

    system("pause");
    return 0;
}
