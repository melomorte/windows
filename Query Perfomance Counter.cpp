#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    LARGE_INTEGER StartingTime, EndingTime,DifferenceTime;
    LARGE_INTEGER frequency; //default frequency which is supported by your hw
    QueryPerformanceFrequency(&frequency);

    QueryPerformanceCounter(&StartingTime);
    cout << "hello baby!" << endl;
    QueryPerformanceCounter(&EndingTime);

    DifferenceTime.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
    DifferenceTime.QuadPart = DifferenceTime.QuadPart * 100000;
    DifferenceTime.QuadPart = DifferenceTime.QuadPart / frequency.QuadPart;
    DifferenceTime.QuadPart = DifferenceTime.QuadPart / 1000; //in multi set.

    cout << "Execution Timer: " << DifferenceTime.QuadPart << "ms" << endl;

    system("pause");
    return 0;
}
