#include "../pch.h"
#include "mem.h"

void mem::PatchEx(void* dst, void* src, unsigned int size, HANDLE processHandle)
{
	DWORD oldProtect;
	VirtualProtectEx(processHandle, dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	WriteProcessMemory(processHandle, dst, src, size, nullptr);
	VirtualProtectEx(processHandle, dst, size, oldProtect, &oldProtect);
}

void mem::NopEx(void* dst, unsigned int size, HANDLE processHandle)
{
	BYTE* nopArray = new BYTE[size];
	memset(nopArray, 0x90, size);
	PatchEx(dst, nopArray, size, processHandle);
	delete[] nopArray;
}

uintptr_t mem::ResolvePointerEx(HANDLE processHandle, uintptr_t base, std::vector<int> offsets)
{
	uintptr_t address = base;

	for (auto offset : offsets)
	{
		ReadProcessMemory(processHandle, (void*)address, &address, sizeof(address), NULL);
		address += offset;
	}

	return address;
}

void mem::Patch(void* dst, void* src, unsigned int size)
{
	DWORD oldProtect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldProtect, &oldProtect);
}

void mem::Nop(void* dst, unsigned int size)
{
	BYTE* nopArray = new BYTE[size];
	memset(nopArray, 0x90, size);
	Patch(dst, nopArray, size);
	delete[] nopArray;
}

uintptr_t mem::ResolvePointer(uintptr_t base, std::vector<int> offsets)
{
	uintptr_t address = base;

	for (auto offset : offsets)
	{
		address = *(uintptr_t*) address;
		address += offset;
	}

	return address;
}