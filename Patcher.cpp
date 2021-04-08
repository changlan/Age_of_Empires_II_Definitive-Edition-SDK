#include "Patcher.h"

void Patcher::PatchBytes(BYTE* address, BYTE* shellcode,
                         const int shellCodeSize, bool modifyPageProtection,
                         DWORD newPageProtection, bool restorePageProtection) {
  DWORD oldProtection;
  if (modifyPageProtection) {
    // apply new page protection
    VirtualProtect(address, shellCodeSize, newPageProtection, &oldProtection);
  } else {
    // there is nothing to restore if page protection wasn't changed
    restorePageProtection = false;
  }

  // apply patch
  memcpy(address, shellcode, shellCodeSize);

  if (restorePageProtection) {
    // restore page protection
    VirtualProtect(address, shellCodeSize, oldProtection, &oldProtection);
  }
}

void Patcher::NOPBytes(BYTE* address, const int amount,
                       bool modifyPageProtection, DWORD newPageProtection,
                       bool restorePageProtection) {
  DWORD oldProtection;
  if (modifyPageProtection) {
    // apply new page protection
    VirtualProtect(address, amount, newPageProtection, &oldProtection);
  } else {
    // there is nothing to restore if page protection wasn't changed
    restorePageProtection = false;
  }

  // apply patch
  for (int i = 0; i < amount; i++) {
    address[i] = 0x90;  // NOP
  }

  if (restorePageProtection) {
    // restore page protection
    VirtualProtect(address, amount, oldProtection, &oldProtection);
  }
}

// Writes a 1 byte value using local endianess
void Patcher::Patch(BYTE* address, int8_t value) {
  DWORD oldProtection;

  // apply new page protection
  VirtualProtect(address, sizeof(value), PAGE_EXECUTE_READWRITE,
                 &oldProtection);

  // write value
  *(int8_t*)address = value;

  // restore page protection
  VirtualProtect(address, sizeof(value), oldProtection, &oldProtection);
}

// Writes a 2 byte value using local endianess
void Patcher::Patch(BYTE* address, int16_t value) {
  DWORD oldProtection;

  // apply new page protection
  VirtualProtect(address, sizeof(value), PAGE_EXECUTE_READWRITE,
                 &oldProtection);

  // write value
  *(int16_t*)address = value;

  // restore page protection
  VirtualProtect(address, sizeof(value), oldProtection, &oldProtection);
}

// Writes a 4 byte value using local endianess
void Patcher::Patch(BYTE* address, int32_t value) {
  DWORD oldProtection;

  // apply new page protection
  VirtualProtect(address, sizeof(value), PAGE_EXECUTE_READWRITE,
                 &oldProtection);

  // write value
  *(int32_t*)address = value;

  // restore page protection
  VirtualProtect(address, sizeof(value), oldProtection, &oldProtection);
}

// Writes a 8 byte value using local endianess
void Patcher::Patch(BYTE* address, int64_t value) {
  DWORD oldProtection;

  // apply new page protection
  VirtualProtect(address, sizeof(value), PAGE_EXECUTE_READWRITE,
                 &oldProtection);

  // write value
  *(int64_t*)address = value;

  // restore page protection
  VirtualProtect(address, sizeof(value), oldProtection, &oldProtection);
}