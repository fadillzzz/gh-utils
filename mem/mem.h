#pragma once

namespace mem
{
	void PatchEx(void* dst, void* src, unsigned int size, HANDLE processHandle);
	void NopEx(void* dst, unsigned int size, HANDLE processHandle);
	uintptr_t ResolvePointerEx(HANDLE processHandle, uintptr_t base, std::vector<int> offsets);

	void Patch(void* dst, void* src, unsigned int size);
	void Nop(void* dst, unsigned int size);
	uintptr_t ResolvePointer(uintptr_t base, std::vector<int> offsets);
}
