#include "hook_tools.h"
#include <Windows.h>
#include <cstdint>

//Injects a relative CALL to [target] at the [position].
//Original function from BWAPI by Kovarex; Modified by pastelmind
void callPatch(const void* target, void* position, const unsigned int nops) {
	uint8_t* const shellCode = new uint8_t[5 + nops];
	shellCode[0] = 0xE8; //Relative CALL instruction

	const DWORD relativeAddr = (DWORD)target - (DWORD)position - 5;  //Relative address
	*(DWORD*)(&shellCode[1]) = relativeAddr;

	for (unsigned int i = 0; i < nops; ++i)
		shellCode[5 + i] = 0x90; //NOP instruction
	memoryPatch(position, shellCode, 5 + nops);
	delete[] shellCode;
}


//Injects a relative JMP to [target] at the [position].
//Original function from BWAPI by Kovarex; Modified by pastelmind
void jmpPatch(const void* target, void* position, unsigned int nops) {
	uint8_t* const shellCode = new uint8_t[5 + nops];
	shellCode[0] = 0xE9; //Relative JMP instruction
	const DWORD relativeAddr = (DWORD)target - (DWORD)position - 5;  //Relative address
	*(DWORD*)(&shellCode[1]) = relativeAddr;
	for (unsigned int i = 0; i < nops; ++i)
		shellCode[5 + i] = 0x90; //NOP instruction
	memoryPatch(position, shellCode, 5 + nops);
	delete[] shellCode;
}


//Inject an array of bytes, using the given length.
void memoryPatch(void* const address, const uint8_t* data, const size_t size) {
	DWORD oldProt = 0;
	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProt);
	memcpy(address, data, size);
	VirtualProtect(address, size, oldProt, &oldProt);
}
