#include "unstdx/efisys.hpp"
#include "defs/efirs.hpp"
#include "unstdx/raw/trampoline.hpp"

#if defined(__x86_64__) || defined(__i386__)
#define __uefi_halt __asm__ volatile("hlt")
#endif

#ifndef __uefi_halt
#define __uefi_halt {volatile int x = 0; if(x < 2) x += 1;}
#endif

namespace uefi::system{

[[noreturn]] void EFIAPI exit(UINTN statusCode, ExitType type) noexcept{
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

    while(true) __uefi_halt;
}

[[noreturn]] void EFIAPI shutdown(UINTN status) noexcept{
    exit(status, ExitType::Shutdown);
}
[[noreturn]] void EFIAPI reboot(UINTN status) noexcept{
    exit(status, ExitType::Reboot);
}
[[noreturn]] void EFIAPI loop(UINTN status) noexcept{
    exit(status, ExitType::Loop);
}

}