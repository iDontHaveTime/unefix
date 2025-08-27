#include "unstdx/efisys.hpp"
#include "defs/efirs.hpp"
#include "unstdx/raw/trampoline.hpp"

namespace uefi::system{

[[noreturn]] void exit(UINTN statusCode, ExitType type) noexcept{
    switch(type){
        case ExitType::Reboot:
            uefi::raw::SystemTable->RuntimeServices->ResetSystem(EFI_RESET_TYPE::EfiResetCold, statusCode, 0, nullptr);
            break;
        case ExitType::PlatformReset:
            uefi::raw::SystemTable->RuntimeServices->ResetSystem(EFI_RESET_TYPE::EfiResetWarm, statusCode, 0, nullptr);
            break;
        case ExitType::Loop:
            break;
        case ExitType::Shutdown:
            [[fallthrough]];
        default:
            uefi::raw::SystemTable->RuntimeServices->ResetSystem(EFI_RESET_TYPE::EfiResetShutdown, statusCode, 0, nullptr);
            break;
    }

    while(true) __asm__ volatile("hlt");
}

[[noreturn]] void shutdown(UINTN status) noexcept{
    exit(status, ExitType::Shutdown);
}
[[noreturn]] void reboot(UINTN status) noexcept{
    exit(status, ExitType::Reboot);
}
[[noreturn]] void loop(UINTN status) noexcept{
    exit(status, ExitType::Loop);
}

}