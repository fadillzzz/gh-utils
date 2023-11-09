#include "../pch.h"
#include "proc.h"

DWORD GetProcId(const wchar_t* procName)
{
	DWORD procId = 0;
	HANDLE handleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (handleSnapshot != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		while (Process32Next(handleSnapshot, &procEntry))
		{
			if (_wcsicmp(procEntry.szExeFile, procName) == 0)
			{
				procId = procEntry.th32ProcessID;
				break;
			}
		}
	}

	CloseHandle(handleSnapshot);

	return procId;
}

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* moduleName)
{
	uintptr_t address = 0;

	HANDLE handleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);

	if (handleSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 moduleEntry;

		moduleEntry.dwSize = sizeof(moduleEntry);

		while (Module32Next(handleSnapshot, &moduleEntry))
		{
			if (_wcsicmp(moduleEntry.szModule, moduleName) == 0)
			{
				address = (uintptr_t)moduleEntry.modBaseAddr;
				break;
			}
		}
	}

	CloseHandle(handleSnapshot);

	return address;
}
