#include "unstdx/efigfx.hpp"
#include "unstdx/efimem.hpp"
#include "unstdx/efistream.hpp"
#include "unstdx/efifile.hpp"
#include "unefix.hpp"

void print_ascii(uefi::uefistream& us, const char* str) noexcept{
    us<<str;
}

size_t read_file(const uefi::fs::path& name) noexcept{
    uefi::fs::volume vol(uefi::raw::fsHandles[0]);

    if(vol.valid()){
        uefi::cerr<<"Volume opened"<<uefi::endl;
    }
    else{
        uefi::cerr<<"Volume is not valid"<<uefi::endl;
    }

    uefi::fs::file f = vol.open_file(name, EFI_FILE_MODE_READ);
    if(f){
        uefi::cerr<<"File opened"<<uefi::endl;
    }
    

    char buff[17];
    size_t to_read = 16;
    f.read(buff, &to_read);

    buff[to_read] = '\0';

    uefi::cout<<buff<<uefi::endl;

    return to_read;
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

    uefi::cout<<42<<" 0x"<<(void*)0x1F1471
    <<" 0x"<<uefi::leadz(true)<<(void*)0x1F1471
    <<' '<<-42<<uefi::endl<<uefi::leadz(false);

    char* ptr = (char*)uefi::alloc(24);

    if(!ptr){
        uefi::cout<<"ptr is null. reason: "<<uefi::mem_error<<uefi::endl;
    }

    ptr[23] = '\0';

    uefi::cout<<ptr<<uefi::endl;
    
    uefi::free(ptr);
    
    uefi::cout.flush();

    uefi::fs::path newpath = "toread.txt";
    read_file(newpath);

    // screen.clear(screen.color(100, 100, 100));
    
    uefi::raw::default_shutdown = uefi::system::ExitType::Loop;
    uefi::cout<<"main exit"<<uefi::endl;
    return EFI_SUCCESS; // after main, cout flushes automatically
}