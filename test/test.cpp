#include "unstdx/efistream.hpp"
#include "unefix.hpp"

EFI_STATUS EFIAPI main_efix(){
    uefi::raw::SystemTable->ConOut->ClearScreen(uefi::raw::SystemTable->ConOut);

    uefi::cout<<u"qemu and uefi booted and work!"<<u"\r\nline 2\r\n"<<uefi::flush;

    while(true) __asm__ volatile("hlt");

    return EFI_SUCCESS;
}