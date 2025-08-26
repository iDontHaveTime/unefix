#include "unstdx/efinew.hpp"

void operator delete(void*) noexcept{
    return;
}

void* operator new(size_t size){
    return (void*)(size - size);
}

void* operator new[](size_t size){
    return operator new(size);
}

void operator delete[](void* ptr) noexcept{
    operator delete(ptr);
}