#define ERROR_MEMORY_WRITE "Failed writing to memory"
#define ERROR_MEMORY_READ "Unable to read from memory"
#define ERROR_PROCESS "Unable to open process"
#define ERROR_MODULE "Failed opening module"
#define ERROR_NOT_OPEN "Please make sure Dishonored is open"

#define BASEADDR 0x01452DE8
#define OFFSET_MANA 0xA60

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <TlHelp32.h>

const char *winStr = "Dishonored";
const char *exeStr = "Dishonored.exe";

void exit_with_error(char *err, HANDLE *hProcess);