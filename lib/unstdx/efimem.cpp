#include "unstdx/efimem.hpp"
#include "unstdx/raw/trampoline.hpp"
#include "defs/efiboot.hpp"

namespace uefi{
const char* mem_error = nullptr;

void* alloc(UINTN bytes, unsigned int alignment) noexcept{
    void* ptr = nullptr;

    UINTN total = bytes + alignment - 1 + sizeof(void*);

    EFI_STATUS status = raw::SystemTable->BootServices->AllocatePool(
        EFI_MEMORY_TYPE::EfiLoaderData,
        total,
        &ptr
    );

    if(status != EFI_SUCCESS){
        mem_error = "UEFI AllocatePool Failed";
        return nullptr;
    }

    uintptr_t raw = (uintptr_t)ptr;
    uintptr_t offset = raw + sizeof(void*);
    uintptr_t aligned = (offset + alignment - 1) & ~(alignment - 1);

    ((void**)aligned)[-1] = ptr;

    return (void*)aligned;
}

void free(void* ptr) noexcept{
    if(ptr){
        void* rptr = ((void**)ptr)[-1];
        raw::SystemTable->BootServices->FreePool(rptr);
    }
}

}