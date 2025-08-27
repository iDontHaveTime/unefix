#ifndef EFISYS_HPP
#define EFISYS_HPP

#include "types/untypes.hpp"

namespace uefi::system{
    enum class ExitType{
        Shutdown,
        Reboot,
        PlatformReset,
        Loop
    };
    [[noreturn]] void exit(UINTN statusCode, ExitType type) noexcept;
    [[noreturn]] void shutdown(UINTN status = 0) noexcept;
    [[noreturn]] void reboot(UINTN status = 0) noexcept;
    [[noreturn]] void loop(UINTN status = 0) noexcept;
}

#endif // EFISYS_HPP
