#ifndef UNTYPES_HPP
#define UNTYPES_HPP

#include "types/uefi_stddef.h"
#include "types/uefi_stdint.h"

#ifndef __cplusplus
#error "This library is C++ only"
#endif

typedef bool BOOLEAN;

typedef intptr_t INTN;
typedef uintptr_t UINTN;

typedef int8_t INT8;
typedef uint8_t UINT8;

typedef int16_t INT16;
typedef uint16_t UINT16;

typedef int32_t INT32;
typedef uint32_t UINT32;

typedef int64_t INT64;
typedef uint64_t UINT64;

#ifdef __INT128_DEFINED__
typedef __i128 INT128;
typedef __u128 UINT128;
#endif

typedef char8_t CHAR8;
typedef char16_t CHAR16;

typedef void VOID;

struct alignas(8) EFI_GUID{
    UINT32 Data1;
    UINT16 Data2;
    UINT16 Data3;
    UINT8 Data4[8];
};

typedef UINTN EFI_STATUS;

typedef void* EFI_HANDLE;
typedef void* EFI_EVENT;

typedef UINT64 EFI_LBA;

typedef UINTN EFI_TPL;

struct EFI_MAC_ADDRESS{
    UINT8 Addr[32];
};

struct EFI_IPv4_ADDRESS{
    UINT8 Addr[4];
};

struct EFI_IPv6_ADDRESS{
    UINT8 Addr[16];
};

struct alignas(4) EFI_IP_ADDRESS{
    UINT8 Addr[16];
};

struct EFI_TIME{
    UINT16 Year;
    UINT8 Month;
    UINT8 Day;
    UINT8 Hour;
    UINT8 Minute;
    UINT8 Second;
    UINT8 __padding1__;
    UINT32 Nanosecond;
    INT16 Timezone;
    UINT8 Daylight;
    UINT8 __padding2__;
};

struct EFI_TIME_CAPABILITIES{
    UINT32 Resolution;
    UINT32 Accuracy;
    BOOLEAN SetsToZero;
};

using EFI_PHYSICAL_ADDRESS = UINT64;
using EFI_VIRTUAL_ADDRESS = UINT64;

struct EFI_MEMORY_DESCRIPTOR{
    UINT32 Type;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS VirtualStart;
    UINT64 NumberOfPages;
    UINT64 Attribute;
};

struct EFI_CAPSULE_HEADER{
    EFI_GUID CapsuleGuid;
    UINT32 HeaderSize;
    UINT32 Flags;
    UINT32 CapsuleImageSize;
};

struct EFI_TABLE_HEADER{
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
};

struct EFI_INPUT_KEY{
   UINT16 ScanCode;
   CHAR16 UnicodeChar;
};

#endif // UNTYPES_HPP
