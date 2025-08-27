#include "unstdx/efistream.hpp"
#include "unstdx/raw/trampoline.hpp"

namespace uefi{
    ueficerr cerr = {};
    ueficout cout = {};
    const __uefi_fflush__ flush = {};
    const __uefi_endl__ endl = {};

    void EFIAPI clearScreen() noexcept{
        raw::SystemTable->ConOut->ClearScreen(raw::SystemTable->ConOut);
    }
}