#include "Pattern.h"

#include <Windows.h>
#include <psapi.h>
#include <tlhelp32.h>

#include <iostream>

// uint64_t Pattern::FindSignature(const char* szModule, const char*
// szSignature)
//{
//	printf("Start FindSig\n");
//	//CREDITS: learn_more
//#define INRANGE(x,a,b)  (x >= a && x <= b)
//#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' +
//0xa) : (INRANGE(x,'0','9') ? x - '0' : 0)) #define getByte( x ) (getBits(x[0])
//<< 4 | getBits(x[1]))
//
//	MODULEINFO modInfo;
//	GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(szModule),
//&modInfo, sizeof(MODULEINFO));
//
//	printf("GetModuleInformation\n");
//
//	DWORD startAddress = (DWORD)modInfo.lpBaseOfDll;
//	DWORD endAddress = startAddress + modInfo.SizeOfImage;
//	const char* pat = szSignature;
//	DWORD firstMatch = 0;
//	printf("BeforeLoop\n");
//	for (DWORD pCur = startAddress; pCur < endAddress; pCur++) {
//		if (!*pat) return firstMatch;
//		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
//			if (!firstMatch) firstMatch = pCur;
//			if (!pat[2]) return firstMatch;
//			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat +=
//3; 			else pat += 2;    //one ?
//		}
//		else {
//			pat = szSignature;
//			firstMatch = 0;
//		}
//	}
//	return NULL;
//}

uint64_t Pattern::FindSignature(const char* szModule, const char* szSignature) {
#define INRANGE(x, a, b) (x >= a && x <= b)
#define GET_BYTE(x) (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS(x)                                               \
  (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xa) \
                                    : (INRANGE(x, '0', '9') ? x - '0' : 0))

  MODULEINFO modInfo;
  GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(szModule),
                       &modInfo, sizeof(MODULEINFO));
  uint64_t startAddress = (uint64_t)GetModuleHandleA(szModule);
  uint64_t endAddress = (startAddress + (uint64_t)modInfo.SizeOfImage);
  const char* pat = szSignature;
  uint64_t firstMatch = 0;
  for (uint64_t pCur = startAddress; pCur < endAddress; pCur++) {
    if (!*pat) return firstMatch;
    if (*(PBYTE)pat == ('\?') || *(BYTE*)pCur == GET_BYTE(pat)) {
      if (!firstMatch) firstMatch = pCur;
      if (!pat[2]) return firstMatch;
      if (*(PWORD)pat == ('\?\?') || *(PBYTE)pat != ('\?'))
        pat += 3;
      else
        pat += 2;
    } else {
      pat = szSignature;
      firstMatch = 0;
    }
  }
  return NULL;
}
