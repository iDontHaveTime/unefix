#include "unefix.hpp"
#include "unstdx/raw/trampoline.hpp"

EFI_STATUS EFIAPI main_efix(){
    EFI_SYSTEM_TABLE* systable = uefi::raw::SystemTable;

    systable->ConOut->ClearScreen(systable->ConOut);

    systable->ConOut->OutputString(systable->ConOut, u"qemu and uefi booted and work!\r\n");

    while(true) __asm__ volatile("hlt");

    return EFI_SUCCESS;
}