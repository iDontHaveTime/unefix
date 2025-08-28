#include "unstdx/efifile.hpp"
#include "unstdx/raw/trampoline.hpp"

namespace uefi{
namespace fs{

volume volume::from_handle(EFI_HANDLE handle) noexcept{
    volume v{};
    v.fsHandle = handle;

    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fsProtocol = nullptr;
    EFI_GUID guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    EFI_STATUS status = uefi::raw::SystemTable->BootServices->HandleProtocol(
        handle,
        &guid,
        (void**)&fsProtocol
    );

    if(status != EFI_SUCCESS || !fsProtocol){
        return v;
    }

    status = fsProtocol->OpenVolume(fsProtocol, &v.root);
    if(status != EFI_SUCCESS){
        v.root = nullptr;
    }

    return v;
}

void volume::close() noexcept{
    if(root){
        root->Close(root);
        root = nullptr;
    }
    fsHandle = nullptr;
}

}
}