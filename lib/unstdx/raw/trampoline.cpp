#include "unstdx/raw/trampoline.hpp"
#include "unefix.hpp"

namespace uefi{
namespace raw{
EFI_HANDLE ImageHandle = nullptr;
EFI_SYSTEM_TABLE* SystemTable = nullptr;
}
}

extern "C"{
    typedef void (*ctor_t)();
    typedef void (*dtor_t)();

    ctor_t __init_array_start[1] __attribute__((weak, section(".init_array"))) = {nullptr};
    ctor_t __init_array_end[1]   __attribute__((weak, section(".init_array"))) = {nullptr};

    dtor_t __fini_array_start[1] __attribute__((weak, section(".fini_array"))) = {nullptr};
    dtor_t __fini_array_end[1]   __attribute__((weak, section(".fini_array"))) = {nullptr};
}

void run_global_ctors(){
    if(__init_array_start[0] == nullptr) return;
    for(ctor_t* ctor = __init_array_start; ctor != __init_array_end; ctor++){
        (*ctor)();
    }
}

void run_global_dtors(){
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
    run_global_dtors();

    return status;
}