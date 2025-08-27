#ifndef EFIBOOT_HPP
#define EFIBOOT_HPP

#include "defs/undefix.hpp"
#include "types/untypes.hpp"

typedef EFI_TPL (EFIAPI *EFI_RAISE_TPL)(IN EFI_TPL newTpl);
typedef void (EFIAPI *EFI_RESTORE_TPL)(IN EFI_TPL oldTpl);

enum class EFI_ALLOCATE_TYPE : UINT32{
    AllocateAnyPages, AllocateMaxAddress, AllocateAddress, MaxAllocateType
};
enum class EFI_MEMORY_TYPE : UINT32{
    EfiReservedMemoryType, EfiLoaderCode, EfiLoaderData, EfiBootServicesCode, EfiBootServicesData,
    EfiRuntimeServicesCode, EfiRuntimeServicesData, EfiConventionalMemory, EfiUnusableMemory,
    EfiACPIReclaimMemory, EfiACPIMemoryNVS, EfiMemoryMappedIO, EfiMemoryMappedIOPortSpace,
    EfiPalCode, EfiPersistentMemory, EfiUnacceptedMemoryType, EfiMaxMemoryType,

    MEMORY_TYPE_OEM_RESERVED_MIN = 0x70000000,
    MEMORY_TYPE_OEM_RESERVED_MAX = 0x7FFFFFFF,
    MEMORY_TYPE_OS_RESERVED_MIN = 0x80000000,
    MEMORY_TYPE_OS_RESERVED_MAX = 0xFFFFFFFF,
};
enum class EFI_TIMER_DELAY : UINT32{
    TimerCancel, TimerPeriodic, TimerRelative
};

typedef EFI_STATUS (EFIAPI *EFI_ALLOCATE_PAGES)(IN EFI_ALLOCATE_TYPE type, IN EFI_MEMORY_TYPE memoryType, IN UINTN pages, IN OUT EFI_PHYSICAL_ADDRESS* memory);
typedef EFI_STATUS (EFIAPI *EFI_FREE_PAGES)(IN EFI_PHYSICAL_ADDRESS memory, IN UINTN pages);
typedef EFI_STATUS (EFIAPI *EFI_GET_MEMORY_MAP)(IN OUT UINTN* memoryMapSize, OUT EFI_MEMORY_DESCRIPTOR* memoryMap, OUT UINTN* mapKey, OUT UINTN* descriptorSize, OUT UINT32* descriptorVersion);
typedef EFI_STATUS (EFIAPI *EFI_ALLOCATE_POOL)(IN EFI_MEMORY_TYPE poolType, IN UINTN size, OUT void** buffer);
typedef EFI_STATUS (EFIAPI *EFI_FREE_POOL)(IN void* buffer);

typedef void (EFIAPI *EFI_EVENT_NOTIFY)(IN EFI_EVENT event, IN void* context);
typedef EFI_STATUS (EFIAPI *EFI_CREATE_EVENT)(IN UINT32 type, IN EFI_TPL notifyTpl, IN EFI_EVENT_NOTIFY notifyFunction OPTIONAL, IN void* notifyContext OPTIONAL, OUT EFI_EVENT* event);
typedef EFI_STATUS (EFIAPI *EFI_SET_TIMER)(IN EFI_EVENT event, IN EFI_TIMER_DELAY type, IN UINT64 triggerTime);
typedef EFI_STATUS (EFIAPI *EFI_WAIT_FOR_EVENT)(IN UINTN numberOfEvents, IN EFI_EVENT* event, OUT UINTN* index);
typedef EFI_STATUS (EFIAPI *EFI_SIGNAL_EVENT)(IN EFI_EVENT event);
typedef EFI_STATUS (EFIAPI *EFI_CLOSE_EVENT)(IN EFI_EVENT event);
typedef EFI_STATUS (EFIAPI *EFI_CHECK_EVENT)(IN EFI_EVENT event);

enum class EFI_INTERFACE_TYPE : UINT32{
    EFI_NATIVE_INTERFACE
};

typedef EFI_STATUS (EFIAPI *EFI_INSTALL_PROTOCOL_INTERFACE)(IN OUT EFI_HANDLE* handle, IN EFI_GUID* protocol, IN EFI_INTERFACE_TYPE interfaceType, IN void* interface);
typedef EFI_STATUS (EFIAPI *EFI_REINSTALL_PROTOCOL_INTERFACE)(IN EFI_HANDLE handle, IN EFI_GUID* protocol, IN void* oldInterface, IN void* newInterface);
typedef EFI_STATUS (EFIAPI *EFI_UNINSTALL_PROTOCOL_INTERFACE)(IN EFI_HANDLE handle, IN EFI_GUID* protocol, IN void* interface);
typedef EFI_STATUS (EFIAPI *EFI_HANDLE_PROTOCOL)(IN EFI_HANDLE handle, IN EFI_GUID* protocol, OUT void** interface);

enum class EFI_LOCATE_SEARCH_TYPE : UINT32{
    AllHandles, ByRegisterNotify, ByProtocol
};

struct EFI_DEVICE_PATH_PROTOCOL{
    UINT8 Type;
    UINT8 SubType;
    UINT8 Length[2];
};

typedef EFI_STATUS (EFIAPI *EFI_REGISTER_PROTOCOL_NOTIFY)(IN EFI_GUID* protocol, IN EFI_EVENT event, OUT void** registration);
typedef EFI_STATUS (EFIAPI *EFI_LOCATE_HANDLE)(IN EFI_LOCATE_SEARCH_TYPE searchType, IN EFI_GUID* protocol OPTIONAL, IN void* searchKey OPTIONAL, IN OUT UINTN* bufferSize, OUT EFI_HANDLE* buffer);
typedef EFI_STATUS (EFIAPI *EFI_LOCATE_DEVICE_PATH)(IN EFI_GUID* protocol, IN OUT EFI_DEVICE_PATH_PROTOCOL** devicePath, OUT EFI_HANDLE* device);
typedef EFI_STATUS (EFIAPI *EFI_INSTALL_CONFIGURATION_TABLE)(IN EFI_GUID* guid, IN void* table);
typedef EFI_STATUS (EFIAPI *EFI_IMAGE_LOAD)(IN BOOLEAN bootPolicy, IN EFI_HANDLE parentImageHandle, IN EFI_DEVICE_PATH_PROTOCOL* devicePath OPTIONAL, IN void* sourceBuffer OPTIONAL, IN UINTN sourceSize, OUT EFI_HANDLE* imageHandle);
typedef EFI_STATUS (EFIAPI *EFI_IMAGE_START)(IN EFI_HANDLE imageHandle, OUT UINTN* exitDataSize, OUT CHAR16** exitData OPTIONAL);
typedef EFI_STATUS (EFIAPI *EFI_EXIT)(IN EFI_HANDLE imageHandle, IN EFI_STATUS exitStatus, IN UINTN exitDataSize, IN CHAR16* exitData OPTIONAL);

struct EFI_OPEN_PROTOCOL_INFORMATION_ENTRY{
    EFI_HANDLE AgentHandle;
    EFI_HANDLE ControllerHandle;
    UINT32 Attributes;
    UINT32 OpenCount;
};

typedef EFI_STATUS (EFIAPI *EFI_IMAGE_UNLOAD)(IN EFI_HANDLE imageHandle);
typedef EFI_STATUS (EFIAPI *EFI_EXIT_BOOT_SERVICES)(IN EFI_HANDLE imageHandle, IN UINTN mapKey);

typedef EFI_STATUS (EFIAPI *EFI_GET_NEXT_MONOTONIC_COUNT)(OUT UINT64* count);
typedef EFI_STATUS (EFIAPI *EFI_STALL)(IN UINTN microseconds);

typedef EFI_STATUS (EFIAPI *EFI_SET_WATCHDOG_TIMER)(IN UINTN timeout, IN UINT64 watchdogCode, IN UINTN dataSize, IN CHAR16* watchdogData OPTIONAL);

typedef EFI_STATUS (EFIAPI *EFI_CONNECT_CONTROLLER)(IN EFI_HANDLE controllerHandle, IN EFI_HANDLE* driverImageHandle OPTIONAL, IN EFI_DEVICE_PATH_PROTOCOL* remainingDevicePath OPTIONAL, IN BOOLEAN recursive);
typedef EFI_STATUS (EFIAPI *EFI_DISCONNECT_CONTROLLER)(IN EFI_HANDLE controllerHandle, IN EFI_HANDLE driverImageHandle OPTIONAL, IN EFI_HANDLE childHandle OPTIONAL);

typedef EFI_STATUS (EFIAPI *EFI_OPEN_PROTOCOL)(IN EFI_HANDLE handle, IN EFI_GUID* protocol, OUT void** interface OPTIONAL, IN EFI_HANDLE agentHandle, IN EFI_HANDLE controllerHandle, IN UINT32 attributes);
typedef EFI_STATUS (EFIAPI *EFI_CLOSE_PROTOCOL)(IN EFI_HANDLE handle, IN EFI_GUID* protocol, IN EFI_HANDLE agentHandle, IN EFI_HANDLE controllerHandle);

typedef EFI_STATUS (EFIAPI *EFI_OPEN_PROTOCOL_INFORMATION)(IN EFI_HANDLE handle, IN EFI_GUID* protocol, OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY** entryBuffer, OUT UINTN* entryCount);
typedef EFI_STATUS (EFIAPI *EFI_PROTOCOLS_PER_HANDLE)(IN EFI_HANDLE handle, OUT EFI_GUID*** protocolBuffer, OUT UINTN* protocolBufferCount);

typedef EFI_STATUS (EFIAPI *EFI_LOCATE_HANDLE_BUFFER)(IN EFI_LOCATE_SEARCH_TYPE searchType, IN EFI_GUID* protocol OPTIONAL, IN void* searchKey OPTIONAL, OUT UINTN* noHandles, OUT EFI_HANDLE** buffer);
typedef EFI_STATUS (EFIAPI *EFI_LOCATE_PROTOCOL)(IN EFI_GUID* protocol, IN void* registration OPTIONAL, OUT void** interface);

typedef EFI_STATUS (EFIAPI *EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES)(IN OUT EFI_HANDLE* handle, ...);
typedef EFI_STATUS (EFIAPI *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES)(IN EFI_HANDLE handle, ...);

typedef EFI_STATUS (EFIAPI *EFI_CALCULATE_CRC32)(IN void* data, IN UINTN dataSize, OUT UINT32* crc32);

typedef void (EFIAPI *EFI_COPY_MEM)(IN void* destination, IN void* source, IN UINTN length);
typedef void (EFIAPI *EFI_SET_MEM)(IN void* buffer, IN UINTN size, IN UINT8 value);

typedef EFI_STATUS (EFIAPI *EFI_CREATE_EVENT_EX)(IN UINT32 type, IN EFI_TPL notifyTpl, IN EFI_EVENT_NOTIFY notifyFunction OPTIONAL, IN CONST void* notifyContext OPTIONAL, IN CONST EFI_GUID* eventGroup OPTIONAL, OUT EFI_EVENT* event);

struct EFI_BOOT_SERVICES{
    EFI_TABLE_HEADER Hdr;

    EFI_RAISE_TPL RaiseTPL;
    EFI_RESTORE_TPL RestoreTPL;

    EFI_ALLOCATE_PAGES AllocatePages;
    EFI_FREE_PAGES FreePages;
    EFI_GET_MEMORY_MAP GetMemoryMap;

    EFI_ALLOCATE_POOL AllocatePool;
    EFI_FREE_POOL FreePool;

    EFI_CREATE_EVENT CreateEvent;

    EFI_SET_TIMER SetTimer;

    EFI_WAIT_FOR_EVENT WaitForEvent;
    EFI_SIGNAL_EVENT SignalEvent;
    EFI_CLOSE_EVENT CloseEvent;
    EFI_CHECK_EVENT CheckEvent;

    EFI_INSTALL_PROTOCOL_INTERFACE InstallProtocolInterface;
    EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface;
    EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface;
    EFI_HANDLE_PROTOCOL HandleProtocol;

    void* Reserved;

    EFI_REGISTER_PROTOCOL_NOTIFY RegisterProtocolNotify;
 
    EFI_LOCATE_HANDLE LocateHandle;
    EFI_LOCATE_DEVICE_PATH LocateDevicePath;

    EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable;
    
    EFI_IMAGE_LOAD LoadImage;
    EFI_IMAGE_START StartImage;
    
    EFI_EXIT Exit;

    EFI_IMAGE_UNLOAD UnloadImage;
 
    EFI_EXIT_BOOT_SERVICES ExitBootServices;
    
    EFI_GET_NEXT_MONOTONIC_COUNT GetNextMonotonicCount;
    
    EFI_STALL Stall;
    
    EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;
    
    EFI_CONNECT_CONTROLLER ConnectController;
    
    EFI_DISCONNECT_CONTROLLER DisconnectController;
    
    EFI_OPEN_PROTOCOL OpenProtocol;
    
    EFI_CLOSE_PROTOCOL CloseProtocol;
    
    EFI_OPEN_PROTOCOL_INFORMATION OpenProtocolInformation;
    
    EFI_PROTOCOLS_PER_HANDLE ProtocolsPerHandle;
    
    EFI_LOCATE_HANDLE_BUFFER LocateHandleBuffer;
    
    EFI_LOCATE_PROTOCOL LocateProtocol;
    
    EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces;
    
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;
    
    EFI_CALCULATE_CRC32 CalculateCrc32;
    
    EFI_COPY_MEM CopyMem;
    
    EFI_SET_MEM SetMem;
    
    EFI_CREATE_EVENT_EX CreateEventEx;
};

#endif // EFIBOOT_HPP
