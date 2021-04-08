#pragma once

#include <Windows.h>

#include <cstdint>

class Patcher {
 public:
  void PatchBytes(BYTE* address, BYTE* shellcode, const int shellCodeSize,
                  bool modifyPageProtection = true,
                  DWORD newPageProtection = PAGE_EXECUTE_READWRITE,
                  bool restorePageProtection = true);

  void NOPBytes(BYTE* address, const int amount,
                bool modifyPageProtection = true,
                DWORD newPageProtection = PAGE_EXECUTE_READWRITE,
                bool restorePageProtection = true);

  // TODO: template?
  void Patch(BYTE* address, int8_t value);
  void Patch(BYTE* address, int16_t value);
  void Patch(BYTE* address, int32_t value);
  void Patch(BYTE* address, int64_t value);
};
