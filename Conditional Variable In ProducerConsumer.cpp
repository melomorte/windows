#include <windows.h>
#include <iostream>

using namespace std;

CRITICAL_SECTION cs;
CONDITION_VARIABLE cv;
int buffer = 0;
int max_itens[20];

DWORD WINAPI ProducerThread(LPVOID lpParam)
{
    for(int i = 0;i <= 20; i++)
    {

        EnterCriticalSection(&cs);

        while(buffer == 20)
        {
            SleepConditionVariableCS(&cv,
                                    &cs,
                                    INFINITE);
        }
        buffer++;

        cout << "Producer: " << buffer << endl;

        Sleep(2000);

        WakeConditionVariable(&cv);

        LeaveCriticalSection(&cs);
    }
    return 0;
}

DWORD WINAPI ConsumerThread(LPVOID lpParam)
{
    for(int i = 0;i <= 20; i++)
    {

        EnterCriticalSection(&cs);

        while(buffer == 0)
        {
            SleepConditionVariableCS(&cv,
                                    &cs,
                                    INFINITE);
        }

        cout << "Consumer: " << buffer << endl;

        WakeConditionVariable(&cv);

        LeaveCriticalSection(&cs);
    }
    return 0;
}

int main()
{
    //handle for thread
    HANDLE hProducer, hConsumer;

    //initialize critical section
    InitializeCriticalSection(&cs);

    //step - 1: initialize conditional variable
    InitializeConditionVariable(&cv);

    //Producer;
    hProducer = CreateThread(NULL,
                             0,
                             &ProducerThread,]
                             NULL,
                             0,
                             0);

    if(hProducer == NULL)
    {
        cout << "Create Thread - Producer - failed..." << endl;
    }
    cout << "Create Thread - Producer - sucess..." << endl;

    //Consumer;
    hConsumer = ConsumerThread(NULL,
                               0,
                               &ConsumerThread,
                               NULL,
                               0,
                               0);

    if(hConsumer == NULL)
    {
        cout << "Create Thread - Consumer - failed..." << endl;
    }
    cout << "Create Thread - Consumer - sucess..." << endl;

    //step - 3: Wake all condition variable;
    WakeAllConditionVariable(&cv);

    //step - 4: wait for single object for thread
    WaitForSingleObject(hProducer, INFINITE);
    WaitForSingleObject(hConsumer, INFINITE);

    return 0;
}
