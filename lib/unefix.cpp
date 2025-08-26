#include "unefix.hpp"

#define __uefi_start extern "C" __attribute__((noreturn, naked, visibility("default")))

#if defined(__i386__)
#define __uefi_arch "i386"

__uefi_start void _start_i386(){

}

#elif defined(__x86_64__)
#define __uefi_arch "x86_64"

__uefi_start void _start_x86_64(){
    __asm__ volatile(
        "andq $-16, %rsp\n"
        "callq main_efix\n"
        "hlt\n"
    );
}

#endif

__uefi_start void _start(){
    __asm__ volatile(
        "jmp _start_" __uefi_arch 
        /* According to the C standard, in the lexing steps the lexer should merge strings */
    );
}