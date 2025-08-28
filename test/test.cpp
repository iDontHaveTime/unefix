#include "unstdx/efigfx.hpp"
#include "unstdx/efimem.hpp"
#include "unstdx/efistream.hpp"
#include "unefix.hpp"

void print_ascii(uefi::uefistream& us, const char* str){
    us<<str;
}

EFI_STATUS EFIAPI main_efix(){
    if(!uefi::raw::SystemTable) throw "";
    uefi::clearScreen();

    if(!uefi::raw::gop){
        uefi::cout<<"gop isnt loaded"<<uefi::endl;
    }
    else{
        uefi::cout<<"gop is loaded"<<uefi::endl;
    }
    
    uefi::cout<<u"qemu and uefi booted and works!"<<uefi::endl<<u"line 2"<<uefi::endl;
    uefi::cerr<<"ascii cerr "<<uefi::endl<<u"ustring cerr"<<uefi::endl;

    print_ascii(uefi::cout, "from cout!\r\n");
    print_ascii(uefi::cerr, "from cerr!\r\n");

    uefi::gfx::ScreenInfo screen;

    char* ptr = (char*)uefi::alloc(24);

    if(!ptr){
        uefi::cout<<"ptr is null. reason: "<<uefi::mem_error<<uefi::endl;
    }

    ptr[23] = '\0';

    uefi::cout<<ptr<<uefi::endl;

    uefi::free(ptr);

    // screen.clear(screen.color(100, 100, 100));
    
    uefi::raw::default_shutdown = uefi::system::ExitType::Loop;
    uefi::cout<<"main exit"<<uefi::endl;
    return EFI_SUCCESS; // after main, cout flushes automatically
}