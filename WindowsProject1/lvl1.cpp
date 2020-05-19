//#include <windows.h>
//#include <iostream>
//
//DWORD WINAPI ThreadFunc(void*)
//{
//	std::cout << GetKeyboardType(2);
//	return 0;
//}
//
//void main()
//{
//	HANDLE hThread;
//	DWORD IDThread;
//	hThread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, &IDThread);
//	WaitForSingleObject(hThread, INFINITE);
//	CloseHandle(hThread);
//}