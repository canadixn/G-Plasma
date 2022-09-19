#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

// Global variables
HANDLE hProc;
DWORD pID;

bool attachProc(char* procName) {
	PROCESSENTRY32 procEntry32;

	// Defining the size so we can populate it
	procEntry32.dwSize = sizeof(PROCESSENTRY32);

	// Taking a snapshot of all processes running
	auto hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	// Conditional Failure if unable to take snapshots
	if (hProcSnap == INVALID_HANDLE_VALUE) {
		std::cout << "Failed to take snapshot of process!" << std::endl;
		return false;
	}

	while (Process32Next(hProcSnap, &procEntry32)) {
		std::cout << procEntry32.szExeFile << std::endl;

		if (!strcmp(procName, procEntry32.szExeFile)) {
			std::cout << "Found process " << procEntry32.szExeFile << " with process ID " << procEntry32.th32ProcessID << std::endl;
			std::cout << "Hi, thanks for utilizing this hack. This will give you infinite ammo for your Plasma Gun and Infinite Currency. If you want to contribute, explore the code, or report issues, please the Github repo: https://github.com/canadixn/G-Plasma." << std::endl;
			std::cout << "Most of all, have fun! :)" << std::endl;
			hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procEntry32.th32ProcessID);
			pID = procEntry32.th32ProcessID;

			if (hProc == NULL) {
				std::cout << "Failed getting handle to process." << std::endl;
			}

			CloseHandle(hProcSnap);
			return true;
		}
	}
}

template <class dataType>
void wpm(dataType valToWrite, DWORD addressToWrite) {
	WriteProcessMemory(hProc, (PVOID)addressToWrite, &valToWrite, sizeof(dataType), 0);
}

template <class dataType>
dataType rpm(DWORD addressToRead) {
	dataType rpmBuffer;
	ReadProcessMemory(hProc, (PVOID)addressToRead, &rpmBuffer, size(dataType), 0);
	return rpmBuffer;
}

int main() {
	// Infinite Plasma Gun Ammo
	DWORD plasmaGunInfiniteAmmoAddr1 = 0x0845B9DC;
	DWORD plasmaGunInfiniteAmmoAddr2 = 0x0853D74C;

	// Infinite Currency
	DWORD InfiniteCurrencyAddr1 = 0x51439C;
	DWORD InfiniteCurrencyAddr2 = 0x0845BA68;
	DWORD InfiniteCurrencyAddr3 = 0x51444C;

	attachProc((char*)"GForce.exe");

	while (true) {

		// Plasma Gun
		wpm<int>(999, plasmaGunInfiniteAmmoAddr1);
		wpm<int>(999, plasmaGunInfiniteAmmoAddr2);

		// Currency
		wpm<int>(9999, InfiniteCurrencyAddr1);
		wpm<int>(9999, InfiniteCurrencyAddr2);
		wpm<int>(9999, InfiniteCurrencyAddr3);
	}


}