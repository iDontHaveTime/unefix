#ifndef EFIEXCEPT_HPP
#define EFIEXCEPT_HPP

namespace uefi{
    [[noreturn]] void terminate() noexcept;
}

#endif // EFIEXCEPT_HPP
