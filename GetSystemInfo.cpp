#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
	SYSTEM_INFO sysInfo;
	
	GetSystemInfo(&sysInfo);
	
	cout << "\tHARDWARE INFO" << endl;
	cout << "----------------------------------" << endl;
	
	cout << "processor type: " << sysInfo.dwProcessorType << endl;
	cout << "----------------------------------" << endl;
	
	cout << "page size: " << sysInfo.dwPageSize << endl;
	cout << "----------------------------------" << endl;
	
	cout << "processor mask: " << sysInfo.dwActiveProcessorMask << endl;
	cout << "----------------------------------" << endl;
	
	cout << "processor numbers: " << sysInfo.dwNumberOfProcessors << endl;
	cout << "----------------------------------" << endl;
	
	cout << "allocate granularity: " << sysInfo.dwAllocationGranularity << endl;
	cout << "----------------------------------" << endl; 
	
	return 0;
}
