#pragma once
#include <cstdint>


class Pattern
{
public:
	static uint64_t FindSignature(const char* szModule, const char* szSignature);
};