#ifndef TRAMPOLINE_HPP
#define TRAMPOLINE_HPP

#include "unefix.hpp"

extern "C" EFI_STATUS EFIAPI __unstdx_trampoline__(EFI_HANDLE img, EFI_SYSTEM_TABLE* systable); 

namespace uefi{
namespace raw{

extern EFI_HANDLE ImageHandle;
extern EFI_SYSTEM_TABLE* SystemTable;

}
}

#endif // TRAMPOLINE_HPP
