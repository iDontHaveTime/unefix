#include "unefix.hpp"

define_main(ImageHandle, SystemTable){
    get_table(systable, SystemTable);

    systable->ConOut->ClearScreen(systable->ConOut);

    systable->ConOut->OutputString(systable->ConOut, u"UEFI Booted!\r\n");

    while(true) __asm__ volatile("hlt");

    return EFI_SUCCESS;
}