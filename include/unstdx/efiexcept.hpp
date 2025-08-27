#ifndef EFIEXCEPT_HPP
#define EFIEXCEPT_HPP

#include "defs/undefix.hpp"

namespace uefi{
    [[noreturn]] void EFIAPI terminate() noexcept;
}

#endif // EFIEXCEPT_HPP
