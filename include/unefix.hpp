#ifndef UNEFIX_HPP
#define UNEFIX_HPP

#include "defs/undefix.hpp"
#include "types/untypes.hpp"

struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

struct EFI_TABLE_HEADER{
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
};

typedef EFI_STATUS (EFIAPI *EFI_TEXT_RESET)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* _this, IN BOOLEAN extVerify);
typedef EFI_STATUS (EFIAPI *EFI_TEXT_STRING)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* _this, IN CONST CHAR16* str);
typedef EFI_STATUS(EFIAPI *EFI_TEXT_TEST_STRING)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* _this, IN CONST CHAR16* str);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_QUERY_MODE)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* _this, IN UINTN modeNumber, OUT UINTN* columns, OUT UINTN* rows);

typedef EFI_STATUS(EFIAPI *EFI_TEXT_SET_MODE)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* _this, IN UINTN modeNumber);
typedef EFI_STATUS(EFIAPI *EFI_TEXT_SET_ATTRIBUTE)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* _this, IN UINTN attribute);
typedef EFI_STATUS(EFIAPI *EFI_TEXT_CLEAR_SCREEN)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* _this);
typedef EFI_STATUS(EFIAPI *EFI_TEXT_SET_CURSOR_POSITION)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* _this, IN UINTN column, IN UINTN row);
typedef EFI_STATUS(EFIAPI *EFI_TEXT_ENABLE_CURSOR)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* _this, IN BOOLEAN visible);

struct EFI_SIMPLE_TEXT_OUTPUT_MODE{
    INT32 maxMode;
    INT32 mode;
    INT32 attribute;
    INT32 cursorColumn;
    INT32 cursorRow;
    BOOLEAN cursorVisible;
};

struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL{
    EFI_TEXT_RESET Reset;

    EFI_TEXT_STRING OutputString;
    EFI_TEXT_TEST_STRING TestString;

    EFI_TEXT_QUERY_MODE QueryMode;
    EFI_TEXT_SET_MODE SetMode;
    EFI_TEXT_SET_ATTRIBUTE SetAttribute;

    EFI_TEXT_CLEAR_SCREEN ClearScreen;
    EFI_TEXT_SET_CURSOR_POSITION SetCursorPosition;
    EFI_TEXT_ENABLE_CURSOR EnableCursor;

    EFI_SIMPLE_TEXT_OUTPUT_MODE* Mode;
};

struct EFI_SYSTEM_TABLE{
    EFI_TABLE_HEADER Hdr;

    CHAR16* FirmwareVendor;

    UINT32 FirmwareRevision;

    EFI_HANDLE ConsoleInHandle;

    void* ConIn; // TODO: implement EFI_SIMPLE_TEXT_INPUT_PROTOCOL

    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut;

    EFI_HANDLE StandardErrorHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* StdErr;

    void* RuntimeServices; // TODO: implement EFI_RUNTIME_SERVICES
    void* BootServices; // TODO: implement EFI_BOOT_SERVICES
    
    UINTN NumberOfTableEntries;

    void* ConfigurationTable; // TODO: implement EFI_CONFIGURATION_TABLE
};

// a little helper
#define define_main(x, y) extern "C" EFI_STATUS EFIAPI main_efix(EFI_HANDLE x, void* y)
define_main(ImageHandle, SystemTable);

#define get_table(name, arg) EFI_SYSTEM_TABLE* name = (EFI_SYSTEM_TABLE*)arg

#define EFI_SUCCESS 0

/* How to use the macro: 
define_main(){
    code
}
*/ // As simple as that

#endif // UNEFIX_HPP
