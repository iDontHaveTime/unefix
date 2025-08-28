#include "unstdx/efinew.hpp"
#include "unstdx/efimem.hpp"

void operator delete(void* ptr) noexcept{
    uefi::free(ptr);
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