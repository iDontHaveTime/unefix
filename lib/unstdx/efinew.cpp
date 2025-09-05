#include "unstdx/efinew.hpp"
#include "unstdx/efimem.hpp"
#include "unstdx/efiutils.hpp"

void operator delete(void* ptr) noexcept{
    uefi::free(ptr);
}

void operator delete(void* ptr, std::align_val_t) noexcept{
    uefi::free(ptr);
}

void* operator new(size_t size, uefi::align_val_t align){
    void* ptr = uefi::alloc(size, (size_t)align);
    
    return ptr;
}

void* operator new(size_t size){
    void* ptr = uefi::alloc(size);

    return ptr;
}

void* operator new[](size_t size){
    void* ptr = uefi::alloc(size);

    return ptr;
}

void operator delete[](void* ptr) noexcept{
    uefi::free(ptr);
}