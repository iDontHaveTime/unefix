#ifndef UNEFIX_HPP
#define UNEFIX_HPP

#include "defs/undefix.hpp"
#include "defs/efitop.hpp"
#include "defs/efiinp.hpp"
#include "defs/efirs.hpp"
#include "types/untypes.hpp"

struct EFI_SYSTEM_TABLE{
    EFI_TABLE_HEADER Hdr;

    CHAR16* FirmwareVendor;

    UINT32 FirmwareRevision;

    EFI_HANDLE ConsoleInHandle;

    EFI_SIMPLE_TEXT_INPUT_PROTOCOL* ConIn;

    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut;

    EFI_HANDLE StandardErrorHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* StdErr;

    EFI_RUNTIME_SERVICES* RuntimeServices;
    void* BootServices; // TODO: implement EFI_BOOT_SERVICES
    
    UINTN NumberOfTableEntries;

    void* ConfigurationTable; // TODO: implement EFI_CONFIGURATION_TABLE
};

extern EFI_STATUS EFIAPI main_efix();

#define EFI_SUCCESS 0

#endif // UNEFIX_HPP
