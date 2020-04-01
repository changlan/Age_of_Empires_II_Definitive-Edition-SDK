#include "VmtHook.h"



VmtHook::VmtHook(void** vmt)
{
	this->vmt = vmt;
}

void* VmtHook::Hook(int index, void* hookedFunction)
{
	hookedfuncs.insert(std::make_pair(index, vmt[index]));

	//make page writeable
	DWORD pageProtection;
	VirtualProtect(&vmt[index], sizeof(BYTE*), PAGE_EXECUTE_READWRITE, &pageProtection);

	//overwrite function pointer in VMT to hook function
	vmt[index] = hookedFunction;

	//restore page protection
	VirtualProtect(&vmt[index], sizeof(BYTE*), pageProtection, &pageProtection);

	return hookedfuncs[index];
}

//
//Unhook a single hooked function
bool VmtHook::Unhook(int index)
{
	auto entry = hookedfuncs.find(index);
	if (entry != hookedfuncs.end())
	{
		vmt[entry->first] = entry->second;
		return true;
	}
	return false;
}

//
//Unhook the entire Vmt
void VmtHook::Unhook()
{
	for (std::pair<int, void*> pair : hookedfuncs)
	{
		DWORD oldProtection;
		VirtualProtect(&vmt[pair.first], sizeof(BYTE*), PAGE_EXECUTE_READWRITE, &oldProtection);
		vmt[pair.first] = pair.second;
		VirtualProtect(&vmt[pair.first], sizeof(BYTE*), oldProtection, &oldProtection);
	}
}