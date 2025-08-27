#ifndef EFICONF_HPP
#define EFICONF_HPP

#include "types/untypes.hpp"

struct EFI_CONFIGURATION_TABLE{
    EFI_GUID VendorGuid;
    void* VendorTable;
};

#endif // EFICONF_HPP
