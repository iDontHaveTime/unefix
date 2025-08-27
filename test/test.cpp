#include "unstdx/efistream.hpp"
#include "unefix.hpp"

EFI_STATUS EFIAPI main_efix(){
    uefi::clearScreen();

    uefi::cout<<u"qemu and uefi booted and works!"<<uefi::endl<<u"line 2"<<uefi::endl;
    uefi::cerr<<"ascii cerr "<<uefi::endl<<u"ustring cerr";

    
    // uefi::raw::loop_on_exit = false;
    return EFI_SUCCESS; // uefi::raw::loop_on_exit is true
}