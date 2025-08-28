#ifndef TRAMPOLINE_HPP
#define TRAMPOLINE_HPP

#include "types/untypes.hpp"
#include "unefix.hpp"
#include "defs/efigrph.hpp"
#include "unstdx/efisys.hpp"

extern "C" [[noreturn]] EFI_STATUS EFIAPI __unstdx_trampoline__(EFI_HANDLE img, EFI_SYSTEM_TABLE* systable); 

namespace uefi{
namespace raw{

extern EFI_HANDLE ImageHandle;
extern EFI_SYSTEM_TABLE* SystemTable;
extern EFI_GRAPHICS_OUTPUT_PROTOCOL* gop;
extern system::ExitType default_shutdown;
extern EFI_HANDLE* fsHandles;
extern UINTN fsHandleCount;

}
}

#endif // TRAMPOLINE_HPP
