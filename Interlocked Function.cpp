#include <windows.h>
#include <iostream>
#include <intrin.h>

using namespace std;

int main()
{
    volatile LONG a = 777;
    volatile LONG b;

    b = InterlockedAdd(&a, 5);
    cout << "addition: " << b << endl;

    system("pause");
    return 0;
}
