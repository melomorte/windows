#include <windows.h>
#include <iostream>

using namespace std;

//event for thread.
HANDLE hEvent;

//timer worker thread,
VOID CALLBACK WaitOrTimerCallback(LPVOID lpParam, BOOLEAN TimerOrWaitFired)
{
    if(TimerOrWaitFired)
    {
        cout << "Called Timer Callback Function..." << endl;
    }
    else
    {
        cout << "Called By Event Function..." << endl;
    }

    //set the event.
    SetEvent(hEvent);
}

int main()
{
    //local variable.
    HANDLE hTimer = NULL;
    HANDLE hTimerQueue = NULL;
    BOOL bCreateTimerQueue;
    BOOL bDeleteTimerQueue;

    //step - 1: event function.
    hEvent = CreateEvent(NULL,
                         FALSE,
                         FALSE,
                         NULL);

    if(NULL == hEvent)
    {
        cout << "create event - failed..." << GetLastError() << endl;
    }
    cout << "create event - sucess..." << endl;

    //step - 2: create the timer queue.
    hTimerQueue = CreateTimerQueue();

    if(NULL == hTimerQueue)
    {
        cout << "create timer queue - failed: " << GetLastError() << endl;
    }
    cout << "create timer queue - sucess..." << endl;

    //step - 3: set a timer.
    bCreateTimerQueue = CreateTimerQueueTimer(&hTimer,
                                              hTimerQueue,
                                              (WAITORTIMERCALLBACK)WaitOrTimerCallback,
                                              NULL,
                                              5000,
                                              0,
                                              0);

    if(0 == bCreateTimerQueue)
    {
        cout << "create timer queue - failed: " << GetLastError() << endl;
    }
    cout << "create timer queue - sucess..." << endl;

    //step - 4:
    cout << "timer is calling..." << endl;

    //step - 5: wait for the timer queue.
    WaitForSingleObject(hEvent, INFINITE);

    //step - 6: close handle.
    CloseHandle(hEvent);

    //step - 7: delete all timer queue
    bDeleteTimerQueue = DeleteTimerQueue(hTimerQueue);

    if(0 == bDeleteTimerQueue)
    {
        cout << "Timer queue delete - failed: " << GetLastError() << endl;
    }
    cout << "Timer queue delete - sucess..." << endl;


    system("pause");
    return 0;
}
