#ifndef EFISTR_HPP
#define EFISTR_HPP

#include <types/uefi_stddef.h>

namespace uefi::str{
    inline size_t strlen(const char* _str) noexcept{
        return __builtin_strlen(_str);
    }
    inline void* memset(void* _dest, int c, size_t n) noexcept{
        return __builtin_memset(_dest, c, n);
    }
}

#endif // EFISTR_HPP
