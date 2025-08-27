#include "unstdx/efistream.hpp"
#include "unefix.hpp"

void print_ascii(uefi::uefistream& us, const char* str){
    us<<str;
}

EFI_STATUS EFIAPI main_efix(){
    uefi::clearScreen();

    
    uefi::cout<<u"qemu and uefi booted and works!"<<uefi::endl<<u"line 2"<<uefi::endl;
    uefi::cerr<<"ascii cerr "<<uefi::endl<<u"ustring cerr"<<uefi::endl;

    print_ascii(uefi::cout, "from cout!\r\n");
    print_ascii(uefi::cerr, "from cerr!\r\n");
    
    uefi::raw::default_shutdown = uefi::system::ExitType::Loop;
    return EFI_SUCCESS; // after main, cout flushes automatically
}