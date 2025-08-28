#ifndef EFIFILE_HPP
#define EFIFILE_HPP

#include "defs/efifs.hpp"
#include "defs/undefix.hpp"
#include "types/untypes.hpp"

namespace uefi{
namespace fs{

    class file{
        EFI_FILE_HANDLE handle;
    public:
        file() noexcept : handle(nullptr){};
        file(EFI_FILE_HANDLE h) noexcept : handle(h){};

        bool valid() const noexcept{
            return handle != nullptr;
        }
        operator bool() const noexcept{
            return valid();
        }

        EFI_STATUS read(void* buffer, UINTN* size) noexcept{
            if(!handle) return EFI_INVALID_PARAMETER;
            return handle->Read(handle, size, buffer);
        }

        EFI_STATUS write(const void* buffer, UINTN* size) noexcept{
            if(!handle) return EFI_INVALID_PARAMETER;
            return handle->Write(handle, size, (void*)buffer);
        }

        EFI_STATUS flush() noexcept{
            if(!handle) return EFI_INVALID_PARAMETER;
            return handle->Flush(handle);
        }

        void close() noexcept{
            if(handle){
                flush();
                handle->Close(handle);
                handle = nullptr;
            }
        }

        ~file() noexcept{
            close();
        }
    };

    class volume{
        EFI_FILE_HANDLE root;
        EFI_HANDLE fsHandle;
    public:

        static volume from_handle(EFI_HANDLE handle) noexcept;

        volume() noexcept : root(nullptr), fsHandle(nullptr){};
        volume(EFI_HANDLE handle) noexcept{
            *this = from_handle(handle);
        }

        bool valid() const noexcept{
            return (root && fsHandle);
        }

        operator bool() const noexcept{
            return valid();
        }

        void close() noexcept;

        ~volume() noexcept{
            close();
        }

        file open_file(const CHAR16* path, UINT64 mode) noexcept{
            EFI_FILE_HANDLE f = nullptr;
            if(root && EFI_SUCCESS == root->Open(root, &f, (CHAR16*)path, mode, 0)){
                return file(f);
            }
            return file{};
        }
    };
}
}

#endif // EFIFILE_HPP
