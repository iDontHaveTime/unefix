#ifndef EFISTREAM_HPP
#define EFISTREAM_HPP

#include "unstdx/raw/trampoline.hpp"
#include "unefix.hpp"

namespace uefi{
    namespace defaults{
        constexpr size_t cout_buffsize = 2048;
        constexpr size_t cerr_temp_buffsize = 16;
    }
    class __uefi_fflush__{};
    class __uefi_endl__{};

    class uefistream{
    public:
        virtual EFIAPI ~uefistream() noexcept = default;
        virtual EFIAPI void flush() = 0;
        virtual EFIAPI uefistream& operator<<(const char* str) = 0;
        virtual EFIAPI uefistream& operator<<(char c) = 0;
        virtual EFIAPI uefistream& operator<<(const CHAR16* str) = 0;
        virtual EFIAPI uefistream& operator<<(const __uefi_fflush__&) = 0;
        virtual EFIAPI uefistream& operator<<(const __uefi_endl__&) = 0;

        virtual EFIAPI void write(char c) = 0;
        virtual EFIAPI void write(const CHAR16* str, size_t l) = 0;
        virtual EFIAPI void write(const char* str, size_t l) = 0;
    };

    class ueficerr : public uefistream{
    public:
        void EFIAPI flush() noexcept override{
            return;
        }
        ueficerr& EFIAPI operator<<(const char* str) noexcept override{
            size_t len = __builtin_strlen(str);
            write(str, len);
            return *this;
        }

        ueficerr& EFIAPI operator<<(char c) noexcept override{
            write(c);
            return *this;
        }

        ueficerr& EFIAPI operator<<(const CHAR16* str) noexcept override{
            size_t len = 0;
            while(str[len]) len++;
            write(str, len);
            return *this;
        }

        ueficerr& EFIAPI operator<<(const __uefi_fflush__&) noexcept override{
            flush();
            return *this;
        }

        ueficerr& EFIAPI operator<<(const __uefi_endl__&) noexcept override{
            write(u"\r\n", 2);
            flush();
            return *this;
        }

        EFIAPI void write(char c) noexcept override{
            CHAR16 out[2];

            out[0] = (CHAR16)c;
            out[1] = '\0';

            raw::SystemTable->ConOut->OutputString(raw::SystemTable->ConOut, out);
        }

        EFIAPI void write(const CHAR16* str, size_t l) noexcept override{
            size_t bufi = 0;
            CHAR16 temp[defaults::cerr_temp_buffsize+1];
            for(size_t i = 0; i < l; i++){
                temp[bufi++] = str[i];
                if(bufi >= defaults::cerr_temp_buffsize){
                    temp[bufi] = '\0';
                    raw::SystemTable->ConOut->OutputString(raw::SystemTable->ConOut, temp);
                    bufi = 0;
                }
            }

            if(bufi){
                temp[bufi] = '\0';
                raw::SystemTable->ConOut->OutputString(raw::SystemTable->ConOut, temp);
            }
        }

        EFIAPI void write(const char* str, size_t l) noexcept override{
            size_t bufi = 0;
            CHAR16 temp[defaults::cerr_temp_buffsize+1];

            for(size_t i = 0; i < l; i++){
                temp[bufi++] = (CHAR16)str[i];
                if(bufi >= defaults::cerr_temp_buffsize){
                    temp[bufi] = '\0';
                    raw::SystemTable->ConOut->OutputString(raw::SystemTable->ConOut, temp);
                    bufi = 0;
                }
            }

            if(bufi){
                temp[bufi] = '\0';
                raw::SystemTable->ConOut->OutputString(raw::SystemTable->ConOut, temp);
            }
        }
    };
    class ueficout : public uefistream{
    private:
        CHAR16 buff[defaults::cout_buffsize];
        size_t index = 0;
    public:
        void EFIAPI flush() noexcept override{
            this->buff[this->index] = '\0';
            raw::SystemTable->ConOut->OutputString(raw::SystemTable->ConOut, this->buff);
            this->index = 0;
        }

        ueficout& EFIAPI operator<<(const char* str) noexcept override{
            size_t len = __builtin_strlen(str);
            write(str, len);
            return *this;
        }
        ueficout& EFIAPI operator<<(char c) noexcept override{
            write(c);
            return *this;
        }
        ueficout& EFIAPI operator<<(const CHAR16* str) noexcept override{
            size_t len = 0;
            while(str[len]) len++;
            write(str, len);
            return *this;
        }
        ueficout& EFIAPI operator<<(const __uefi_fflush__&) noexcept override{
            flush();
            return *this;
        }
        ueficout& EFIAPI operator<<(const __uefi_endl__&) noexcept override{
            write(u"\r\n", 2);
            flush();
            return *this;
        }
        
        EFIAPI void write(char c) noexcept override{
            if(this->index >= defaults::cout_buffsize){
                flush();
            }
            this->buff[this->index++] = (CHAR16)c;
        }

        EFIAPI void write(const CHAR16* str, size_t l) noexcept override{
            for(size_t i = 0; i < l; i++){
                if(this->index >= defaults::cout_buffsize){
                    flush();
                }
                this->buff[this->index++] = str[i];
            }
        }

        EFIAPI void write(const char* str, size_t l) noexcept override{
            for(size_t i = 0; i < l; i++){
                if(this->index >= defaults::cout_buffsize){
                    flush();
                }
                this->buff[this->index++] = (CHAR16)str[i];
            }
        }
    };
    extern ueficout cout;
    extern ueficerr cerr;
    extern const __uefi_fflush__ flush;
    extern const __uefi_endl__ endl;

    void EFIAPI clearScreen() noexcept;
}

#endif // EFISTREAM_HPP
