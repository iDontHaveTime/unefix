#ifndef EFISYS_HPP
#define EFISYS_HPP

#include "defs/undefix.hpp"
#include "types/untypes.hpp"

namespace uefi::system{
    enum class ExitType{
        Shutdown,
        Reboot,
        PlatformReset,
        Loop
    };
    [[noreturn]] void EFIAPI exit(UINTN statusCode, ExitType type) noexcept;
    [[noreturn]] void EFIAPI shutdown(UINTN status = 0) noexcept;
    [[noreturn]] void EFIAPI reboot(UINTN status = 0) noexcept;
    [[noreturn]] void EFIAPI loop(UINTN status = 0) noexcept;
}

#endif // EFISYS_HPP
