#ifndef EFISTREAM_HPP
#define EFISTREAM_HPP

#include "unstdx/efistr.hpp"
#include "unstdx/raw/trampoline.hpp"
#include "unefix.hpp"

namespace uefi{
    namespace defaults{
        constexpr size_t cout_buffsize = 1024;
        constexpr size_t cerr_temp_buffsize = 16;
    }
    class __uefi_fflush__{};
    class __uefi_endl__{};
    
    struct leadz{
        bool leading;
        leadz(bool _to_lead) noexcept : leading(_to_lead){};
    };

    class uefistream{
        bool leadzero = false;
    public:
        virtual EFIAPI ~uefistream() noexcept = default;
        virtual EFIAPI void flush() = 0;

        uefistream(const uefistream&) = delete;
        uefistream& operator=(const uefistream&) = delete;

        EFIAPI uefistream& operator<<(const char* str){
            write(str, str::strlen(str));
            return *this;
        }

        EFIAPI uefistream& operator<<(char c){
            write(c);
            return *this;
        }

        EFIAPI uefistream& operator<<(const CHAR16* str){
            size_t len = 0;
            while(str[len]) len++;
            write(str, len);
            return *this;
        }

        EFIAPI uefistream& operator<<(const __uefi_fflush__&){
            flush();
            return *this;
        }

        EFIAPI uefistream& operator<<(const __uefi_endl__&){
            write(u"\r\n", 2);
            flush();
            return *this;
        }

        EFIAPI uefistream& operator<<(const leadz& lz){
            leadzero = lz.leading;
            return *this;
        }

        EFIAPI uefistream& operator<<(int n){
            bool sign = (n < 0);
            if(sign){
                write('-');
                n = -n;
            }

            int f = 0;
            while(n){
                int d = n % 10;
                f = f * 10 + d;
                n /= 10;
            }

            while(f){
                write((f % 10) + '0');
                f /= 10;
            }
            return *this;
        }

        EFIAPI uefistream& operator<<(void* ptr){
            uintptr_t val = (uintptr_t)ptr;
            bool started = leadzero;

            for(int i = sizeof(void*)*2-1; i >= 0; i--){
                uintptr_t digit = (val >> (i*4)) & 0xF;
                if(digit != 0 || started){
                    started = true;
                    if(digit < 10){
                        write('0' + digit);
                    }
                    else{
                        write('A' + (digit - 10));
                    }
                }
            }

            if(!started && leadzero == false){
                write('0');
            }

            return *this;
        }

        virtual EFIAPI void write(char c) = 0;
        virtual EFIAPI void write(const CHAR16* str, size_t l) = 0;
        virtual EFIAPI void write(const char* str, size_t l) = 0;
    };

    class ueficerr : public uefistream{
    public:
        void EFIAPI flush() noexcept override{
            return;
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
