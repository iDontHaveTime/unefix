#include "unstdx/efimem.hpp"
#include "unstdx/raw/trampoline.hpp"
#include "defs/efiboot.hpp"

namespace uefi{
const char* mem_error = nullptr;

void* alloc(UINTN bytes) noexcept{
    void* ptr = nullptr;
    EFI_STATUS status = raw::SystemTable->BootServices->AllocatePool(
        EFI_MEMORY_TYPE::EfiLoaderData,
        bytes,
        &ptr
    );

    if(status != EFI_SUCCESS){
        mem_error = "UEFI AllocatePool Failed";
        return nullptr;
    }
    return ptr;
}

void free(void* ptr) noexcept{
    if(ptr){
        raw::SystemTable->BootServices->FreePool(ptr);
    }
}

}