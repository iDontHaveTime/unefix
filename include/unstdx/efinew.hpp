#ifndef EFINEW_HPP
#define EFINEW_HPP

#include "types/uefi_stddef.h"

void operator delete(void* ptr) noexcept;
void* operator new(size_t size);

void* operator new[](size_t size);
void operator delete[](void* ptr) noexcept;

#endif // EFINEW_HPP
