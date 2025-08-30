# Usage

## Entry Point

Let's start from the entry point, it wouldn't be an entry point if we didnt start from it.
Anyways, lets take a look at the `_start` function found in `lib/unefix.cpp`

```cpp
__uefi_start void _start(){
    __asm__ volatile(
        __uefi_jump " _start_" __uefi_arch 
    );
}
```

This seems weird, but once you understand the macros it uses it will be pretty straightforward. Lets start from the first macro we see, its the `__uefi_start` macro. It is defined like this:

```cpp
#define __uefi_start extern "C" __attribute__((noreturn, naked, visibility("default")))
```

This attribute just means that the function wont return, that it will use only assembly, and sets it to visible.

The next macro would be the `__uefi_jump` macro, this macro is really straightforward, it just a macro that expands to the architecture's jump instruction, so on x86 this would be defined as this:

```cpp
#define __uefi_jump "jmp"
```

Then the next macro is really similar in purpose, to define an architecture specific string, in this case the macro `__uefi_arch` literally defines the architecture as a string, so on x86 once again, its defined as this:

```cpp
#define __uefi_arch "x86_64"
```

So if we assemble it all together, on x86-64 the final `_start` would look like this:

```cpp
__uefi_start void _start(){
    __asm__ volatile(
        "jmp _start_x86_64"
    );
}
```

Now let's jump to the `_start_x86_64` it jumps to.

```cpp
__uefi_start void _start_x86_64(){
    __asm__ volatile(
        "andq $-16, %rsp\n"
        "callq __unstdx_trampoline__\n"
        "hlt\n"
    );
}
```

As we can see it uses bitwise AND on the RSP register, which basically means to align RSP to 16.
Then it calls the `__unstdx_trampoline__` which is the trampoline that handles the basic startup of this library, and this is what makes the main be so clean. The trampoline is defined like this

```cpp
extern "C" [[noreturn]] void EFIAPI __unstdx_trampoline__(EFI_HANDLE img, EFI_SYSTEM_TABLE* systable);
```

I wont go into detail on what the trampoline does, if you want you can go and check it out yourself, its located in `lib/unstdx/raw/trampoline.cpp`.

## Main

to be added