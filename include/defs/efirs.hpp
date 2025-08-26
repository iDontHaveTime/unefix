#ifndef EFIRS_HPP
#define EFIRS_HPP

#include "defs/undefix.hpp"
#include "types/untypes.hpp"

typedef EFI_STATUS (EFIAPI *EFI_GET_TIME)(OUT EFI_TIME* time, OUT EFI_TIME_CAPABILITIES* capabilities OPTIONAL);
typedef EFI_STATUS (EFIAPI *EFI_SET_TIME)(IN EFI_TIME* time);

typedef EFI_STATUS (EFIAPI *EFI_GET_WAKEUP_TIME)(OUT BOOLEAN* enabled, OUT BOOLEAN* pending, OUT EFI_TIME* time);
typedef EFI_STATUS (EFIAPI *EFI_SET_WAKEUP_TIME)(IN BOOLEAN enable, IN EFI_TIME* time OPTIONAL);

typedef EFI_STATUS (EFIAPI *EFI_SET_VIRTUAL_ADDRESS_MAP)(IN UINTN memoryMapSize, IN UINTN descriptorSize, IN UINT32 descriptorVersion, IN EFI_MEMORY_DESCRIPTOR* virtualMap);

typedef EFI_STATUS (EFIAPI *EFI_CONVERT_POINTER)(IN UINTN debugDisposition, IN OUT void** address);

typedef EFI_STATUS (EFIAPI *EFI_GET_VARIABLE)(IN CHAR16* variableName, IN EFI_GUID* vendorGuid, OUT UINT32* attributes OPTIONAL, IN OUT UINTN* dataSize, OUT void* data OPTIONAL);
typedef EFI_STATUS (EFIAPI *EFI_GET_NEXT_VARIABLE_NAME)(IN OUT UINTN* variableNameSize, IN OUT CHAR16* variableName, IN OUT EFI_GUID* vendorGuid);

enum class EFI_RESET_TYPE{
    EfiResetCold, EfiResetWarm, EfiResetShutdown, EfiResetPlatformSpecific
};

typedef void (EFIAPI *EFI_RESET_SYSTEM)(IN EFI_RESET_TYPE resetType, IN EFI_STATUS resetStatus, IN UINTN dataSize, IN void* resetData OPTIONAL);
typedef EFI_STATUS (EFIAPI *EFI_UPDATE_CAPSULE)(IN EFI_CAPSULE_HEADER** capsuleHeaderArray, IN UINTN capsuleCount, IN EFI_PHYSICAL_ADDRESS scatterGatherList OPTIONAL);
typedef EFI_STATUS (EFIAPI *EFI_SET_VARIABLE)(IN CHAR16* variableName, IN EFI_GUID* vendorGuid, IN UINT32 attributes, IN UINTN dataSize, IN void* data);
typedef EFI_STATUS (EFIAPI *EFI_GET_NEXT_HIGH_MONO_COUNT)(OUT UINT32* highCount);
typedef EFI_STATUS (EFIAPI *EFI_QUERY_CAPSULE_CAPABILITIES)(IN EFI_CAPSULE_HEADER** capsuleHeaderArray, IN UINTN capsuleCount, OUT UINT64* maximumCapsuleSize, OUT EFI_RESET_TYPE* resetType);
typedef EFI_STATUS (EFIAPI *EFI_QUERY_VARIABLE_INFO)(IN UINT32 attributes, OUT UINT64* maximumVariableStorageSize, OUT UINT64* remainingVariableStorageSize, OUT UINT64* maximumVariableSize);

struct EFI_RUNTIME_SERVICES{
    EFI_TABLE_HEADER Hdr;

    EFI_GET_TIME GetTime;
    EFI_SET_TIME SetTime;

    EFI_GET_WAKEUP_TIME GetWakeupTime;
    EFI_SET_WAKEUP_TIME SetWakeupTime;

    EFI_SET_VIRTUAL_ADDRESS_MAP SetVirtualAddressMap;
    EFI_CONVERT_POINTER ConvertPointer;

    EFI_GET_VARIABLE GetVariable;
    EFI_GET_NEXT_VARIABLE_NAME GetNextVariableName;
    EFI_SET_VARIABLE SetVariable;

    EFI_GET_NEXT_HIGH_MONO_COUNT GetNextHighMonotonicCount;

    EFI_RESET_SYSTEM ResetSystem;
    EFI_UPDATE_CAPSULE UpdateCapsule;

    EFI_QUERY_CAPSULE_CAPABILITIES QueryCapsuleCapabilities;
    EFI_QUERY_VARIABLE_INFO QueryVariableInfo;
};

#endif // EFIRS_HPP
