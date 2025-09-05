#ifndef EFIMEM_HPP
#define EFIMEM_HPP

#include "types/untypes.hpp"

namespace uefi{
    extern const char* mem_error;

    void* alloc(UINTN bytes, unsigned int alignment = alignof(long double)) noexcept;
    void free(void* ptr) noexcept;
}

#endif // EFIMEM_HPP
