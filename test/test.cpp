#include "unstdx/efistream.hpp"
#include "unefix.hpp"

EFI_STATUS EFIAPI main_efix(){
    uefi::clearScreen();

    uefi::cout<<u"qemu and uefi booted and work!"<<uefi::endl<<u"line 2"<<uefi::endl;

    while(true) __asm__ volatile("hlt");

    return EFI_SUCCESS;
}