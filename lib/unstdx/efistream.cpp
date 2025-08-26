#include "unstdx/efistream.hpp"

namespace uefi{
    ueficout<2048> cout = {};
    const __uefi_fflush__ flush = {};
}