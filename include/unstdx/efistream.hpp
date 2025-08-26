#ifndef EFISTREAM_HPP
#define EFISTREAM_HPP

#include "unefix.hpp"
#include "unstdx/raw/trampoline.hpp"

namespace uefi{
    namespace defaults{
        constexpr size_t cout_buffsize = 2048;
        constexpr size_t cerr_temp_buffsize = 16;
    }
    class __uefi_fflush__{};
    class __uefi_endl__{};

    template<size_t size>
    class uefistream{
    protected:
        CHAR16 buff[size ? size + 1 : 0];
        size_t index;
    public:

        virtual ~uefistream() noexcept = default;
        virtual void flush() = 0;
        virtual uefistream& operator<<(const char* str) = 0;
        virtual uefistream& operator<<(char c) = 0;
        virtual uefistream& operator<<(const CHAR16* str) = 0;
        virtual uefistream& operator<<(const __uefi_fflush__&) = 0;
        virtual uefistream& operator<<(const __uefi_endl__&) = 0;
    };

    class ueficerr : public uefistream<0>{
    public:
        void flush() noexcept override{
            return;
        }
        ueficerr& operator<<(const char* str) noexcept override{
            size_t bufi = 0;
            size_t stri = 0;
            CHAR16 temp[defaults::cerr_temp_buffsize+1];

            while(str[stri]){
                temp[bufi++] = (CHAR16)str[stri++];
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
            
            return *this;
        }

        ueficerr& operator<<(char c) noexcept override{
            CHAR16 out[2];

            out[0] = (CHAR16)c;
            out[1] = '\0';

            raw::SystemTable->ConOut->OutputString(raw::SystemTable->ConOut, out);

            return *this;
        }

        ueficerr& operator<<(const CHAR16* str) noexcept override{
            size_t bufi = 0;
            size_t stri = 0;
            CHAR16 temp[defaults::cerr_temp_buffsize+1];

            while(str[stri]){
                temp[bufi++] = str[stri++];
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

            return *this;
        }

        ueficerr& operator<<(const __uefi_fflush__&) noexcept override{
            flush();
            return *this;
        }

        ueficerr& operator<<(const __uefi_endl__&) noexcept override{
            (*this)<<u"\r\n";
            flush();
            return *this;
        }
    };

    template<size_t size>
    class ueficout : public uefistream<size>{
    public:
        void flush() noexcept override{
            this->buff[this->index] = '\0';
            raw::SystemTable->ConOut->OutputString(raw::SystemTable->ConOut, this->buff);
            this->index = 0;
        }

        ueficout& operator<<(const char* str) noexcept override{
            size_t i = 0;
            while(str[i]){
                if(this->index >= size){
                    flush();
                }
                this->buff[this->index++] = (CHAR16)str[i++];
            }
            return *this;
        }
        ueficout& operator<<(char c) noexcept override{
            if(this->index >= size){
                flush();
            }
            this->buff[this->index++] = (CHAR16)c;
            return *this;
        }
        ueficout& operator<<(const CHAR16* str) noexcept override{
            size_t i = 0;
            while(str[i]){
                if(this->index >= size){
                    flush();
                }
                this->buff[this->index++] = str[i++];
            }
            return *this;
        }
        ueficout& operator<<(const __uefi_fflush__&) noexcept override{
            flush();
            return *this;
        }
        ueficout& operator<<(const __uefi_endl__&) noexcept override{
            (*this)<<u"\r\n";
            flush();
            return *this;
        }
    };

    extern ueficout<defaults::cout_buffsize> cout;
    extern ueficerr cerr;
    extern const __uefi_fflush__ flush;
    extern const __uefi_endl__ endl;

    void clearScreen() noexcept;
}

#endif // EFISTREAM_HPP
