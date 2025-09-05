#ifndef EFIFILE_HPP
#define EFIFILE_HPP

#include "defs/efifs.hpp"
#include "defs/undefix.hpp"
#include "types/untypes.hpp"
#include "unstdx/efistream.hpp"

namespace uefi{
    namespace defaults{
        constexpr size_t max_path_size = 256;
    }
namespace fs{

    class path{
        size_t where = 0;
        char buff[defaults::max_path_size];
    public:
        path() noexcept = default;
        path(const char* _path) noexcept{
            set_path(_path);
        }

        void set_path(const char* p) noexcept{
            where = 0;
            size_t len = uefi::str::strlen(p);
            if(len >= sizeof(buff)) len = sizeof(buff) - 1;

            for(size_t i = 0; i < len; i++){
                buff[i] = p[i];
            }

            buff[len] = '\0';
            where = len;
        }

        const char* data() const noexcept{
            return buff;
        }

        size_t size() const noexcept{
            return where;
        }

        void to_char16(CHAR16* out, size_t max) const noexcept{
            size_t i = 0;
            for(; i < where && i < max-1; i++){
                char c = buff[i];
                out[i] = (c == '/') ? u'\\' : (CHAR16)c;
            }
            out[i] = 0;
        }

        friend uefi::uefistream& operator<<(uefi::uefistream& us, const path& p) noexcept{
            if(!p.where) return us;
            us<<p.data();
            return us;
        }
    };

    class file{
        EFI_FILE_HANDLE handle;
    public:
        file() noexcept : handle(nullptr){};
        file(EFI_FILE_HANDLE h) noexcept : handle(h){};

        EFI_FILE_HANDLE raw_handle(void) const noexcept{
            return handle;
        }

        file(const file&) = delete;
        file& operator=(const file&) = delete;

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

        EFI_FILE_HANDLE raw_root() const noexcept{
            return root;
        }

        EFI_HANDLE raw_fsh() const noexcept{
            return fsHandle;
        }

        bool open(EFI_HANDLE handle) noexcept{
            close();
            fsHandle = handle;

            EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fsProtocol = nullptr;
            EFI_GUID guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
            EFI_STATUS status = uefi::raw::SystemTable->BootServices->HandleProtocol(
                handle,
                &guid,
                (void**)&fsProtocol
            );

            if(status != EFI_SUCCESS || !fsProtocol){
                return true;
            }

            status = fsProtocol->OpenVolume(fsProtocol, &root);
            if(status != EFI_SUCCESS){
                root = nullptr;
            }

            return false;
        }

        volume() noexcept : root(nullptr), fsHandle(nullptr){};
        volume(EFI_HANDLE handle) noexcept{
            root = nullptr;
            fsHandle = nullptr;

            open(handle);
        }

        volume(const volume&) = delete;
        volume& operator=(const volume&) = delete;

        bool valid() const noexcept{
            return (root && fsHandle);
        }

        operator bool() const noexcept{
            return valid();
        }

        void close() noexcept{
            if(root){
                root->Close(root);
            }
            root = nullptr;
            fsHandle = nullptr;
        }

        ~volume() noexcept{
            close();
        }

        file open_file(const path& path, UINT64 mode) const noexcept{
            alignas(16) CHAR16 buff[defaults::max_path_size];
            path.to_char16(buff, defaults::max_path_size);
            return open_file(buff, mode);
        }

        file open_file(CHAR16* path, UINT64 mode) const noexcept{
            EFI_FILE_HANDLE f = nullptr;
            if(root && EFI_SUCCESS == root->Open(root, &f, path, mode, 0)){
                return file(f);
            }
            return file{};
        }
    };
}
}

#endif // EFIFILE_HPP
