#include "dishonored_trainer.hpp"

using namespace std;

void exit_with_error(char *err, HANDLE *hProcess)
{
	cout << "[!] " << err << endl;
	CloseHandle(hProcess);
	cin.get();
	exit(1);
}

#pragma comment(lib, "user32.lib")
int main()
{
	HWND dWin = FindWindow(0, _T(winStr));
	HANDLE hProcess;
	DWORD pid;
    int canRead;
    int canWrite;

	cout << ">> Searching for " << winStr << " window\n";
	if (!dWin)
		exit_with_error(ERROR_NOT_OPEN, &hProcess);

	// save pid
	GetWindowThreadProcessId(dWin, &pid);

	// try to open the process
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (!hProcess)
		exit_with_error(ERROR_PROCESS, &hProcess);

	DWORD BaseAddr;
	DWORD mana;
	unsigned int addMana = 100;

	// read base addr into BaseAddr
	canRead = ReadProcessMemory(hProcess, (void*)BASEADDR, &BaseAddr, 4, NULL);
	if (!canRead)
		exit_with_error(ERROR_MEMORY_READ, &hProcess);

	while(1) {
		// infinite mana
		canRead = ReadProcessMemory(hProcess, (void*)(BaseAddr+OFFSET_MANA), &mana, sizeof(mana), NULL);
		if (!canRead)
			exit_with_error(ERROR_MEMORY_READ, &hProcess);

		if (mana < 100) {
			canWrite = WriteProcessMemory(hProcess, (void*)(BaseAddr+OFFSET_MANA), &addMana, sizeof(addMana), NULL);
			if (!canWrite)
				exit_with_error(ERROR_MEMORY_WRITE, &hProcess);
		}

		Sleep(500);
	}

	CloseHandle(hProcess);
	return 0;
}