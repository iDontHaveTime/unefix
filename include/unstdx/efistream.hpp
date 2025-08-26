#ifndef EFISTREAM_HPP
#define EFISTREAM_HPP

#include "types/untypes.hpp"
#include "unstdx/raw/trampoline.hpp"

namespace uefi{
    class __uefi_fflush__{};

    template<size_t size>
    class uefistream{
    protected:
        CHAR16 buff[size + 1];
        size_t index = 0;
    public:
        virtual ~uefistream() = default;
        virtual void flush() = 0;
        virtual uefistream& operator<<(const char* str) = 0;
        virtual uefistream& operator<<(char c) = 0;
        virtual uefistream& operator<<(const CHAR16* str) = 0;
        virtual uefistream& operator<<(const __uefi_fflush__&) = 0;
    };

    template<size_t size>
    class ueficout : public uefistream<size>{
    public:
        
        void flush() override{
            this->buff[this->index] = '\0';
            uefi::raw::SystemTable->ConOut->OutputString(uefi::raw::SystemTable->ConOut, this->buff);
            this->index = 0;
        }

        ueficout& operator<<(const char* str) override{
            size_t i = 0;
            while(str[i]){
                if(this->index >= size){
                    flush();
                }
                this->buff[this->index++] = (CHAR16)str[i++];
            }
            return *this;
        }
        ueficout& operator<<(char c) override{
            if(this->index >= size){
                flush();
            }
            this->buff[this->index++] = (CHAR16)c;
            return *this;
        }
        ueficout& operator<<(const CHAR16* str) override{
            size_t i = 0;
            while(str[i]){
                if(this->index >= size){
                    flush();
                }
                this->buff[this->index++] = str[i++];
            }
            return *this;
        }
        ueficout& operator<<(const __uefi_fflush__&) override{
            flush();
            return *this;
        }
    };

    extern ueficout<2048> cout;
    extern const __uefi_fflush__ flush;
}

#endif // EFISTREAM_HPP
