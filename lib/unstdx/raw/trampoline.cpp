#include "unstdx/raw/trampoline.hpp"
#include "unstdx/efirtti.hpp"
#include "unstdx/efiexcept.hpp"
#include "unstdx/efistream.hpp"
#include "unefix.hpp"
#include "unstdx/efisys.hpp"

namespace std{
    [[noreturn]] void terminate() noexcept{
        uefi::terminate();
    }
}

extern "C" void __gxx_personality_seh0(){ 
    while(true) __asm__("hlt"); 
}

extern "C" void __cxa_begin_catch(){ 
    while(true) __asm__("hlt"); 
}

extern "C" void __cxa_end_catch(){};

extern "C" void* __cxa_allocate_exception(size_t size) noexcept{
    static char buf[512];
    if(size < 512){
        return buf;
    }
    return nullptr;
}

extern "C" __attribute__((weak)) const __cxxabiv1::__class_type_info typeinfo_charptr asm("_ZTIPKc") = {};

extern "C" int atexit(void (*)(void)) noexcept{
    return 0;
}

extern "C" void __cxa_free_exception(void* ptr) noexcept{
    (void)ptr;
}

extern "C" [[noreturn]] void __cxa_throw(void* thrown_exception, void* tinfo, void (*dest)(void*)){
    (void)thrown_exception;
    (void)tinfo;
    (void)dest;

    uefi::cerr<<u"Exception thrown!\r\n";

    std::terminate();
}

namespace uefi{
namespace raw{
EFI_HANDLE ImageHandle = nullptr;
EFI_SYSTEM_TABLE* SystemTable = nullptr;
EFI_GRAPHICS_OUTPUT_PROTOCOL* gop = nullptr;
system::ExitType default_shutdown = system::ExitType::Shutdown;

EFI_GUID gop_guid = {
    0x9042A9DE,
    0x23DC,
    0x4A38,
    {0x96, 0xFB, 0x7A, 0xD4, 0xDF, 0x1B, 0xEA, 0x4F}
};

}
}

extern "C" size_t strlen(const char* _str) noexcept{
    size_t len = 0;
    while(*_str++) len++;
    return len;
}

namespace uefi{
    [[noreturn]] void terminate() noexcept{
        cout.flush();
        while(true) __asm__ volatile("hlt");
    }
}

namespace __cxxabiv1{
    __si_class_type_info::~__si_class_type_info() noexcept{};
    __class_type_info::~__class_type_info() noexcept{};
}


extern "C"{
    typedef void (*ctor_t)();
    typedef void (*dtor_t)();

    ctor_t __init_array_start[1] __attribute__((weak, section(".init_array"))) = {nullptr};
    ctor_t __init_array_end[1]   __attribute__((weak, section(".init_array"))) = {nullptr};

    dtor_t __fini_array_start[1] __attribute__((weak, section(".fini_array"))) = {nullptr};
    dtor_t __fini_array_end[1]   __attribute__((weak, section(".fini_array"))) = {nullptr};
}

void run_global_ctors() noexcept{
    if(__init_array_start[0] == nullptr) return;
    for(ctor_t* ctor = __init_array_start; ctor != __init_array_end; ctor++){
        (*ctor)();
    }
}

extern "C" void __cxa_pure_virtual(){
    while(true) __asm__("hlt");
}

void run_global_dtors() noexcept{
    if(__fini_array_start[0] == nullptr) return;
    for(dtor_t* dtor = __fini_array_start; dtor != __fini_array_end; dtor++){
        (*dtor)();
    }
}


extern "C" EFI_STATUS EFIAPI __unstdx_trampoline__(EFI_HANDLE img, EFI_SYSTEM_TABLE* systable){
    uefi::raw::SystemTable = systable;
    uefi::raw::ImageHandle = img;

    run_global_ctors();

    EFI_STATUS status = main_efix();

    uefi::cout.flush();

    run_global_dtors();

    uefi::system::exit(0, uefi::raw::default_shutdown);

    return status;
}