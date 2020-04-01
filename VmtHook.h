#pragma once

#include <Windows.h>
#include <map>


class VmtHook
{
private:
	void** vmt;
	std::map<int, void*> hookedfuncs;

public:
	VmtHook(void** vmt);

	void* Hook(int index, void* hookedFunction);

	bool Unhook(int index);
	void Unhook();
};
