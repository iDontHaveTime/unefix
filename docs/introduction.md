# Introduction

## Why unefix?

Before I explain what is **unefix**, I'd like to explain *why* it exists.

For months I have been struggling to get UEFI booting, I never got it to boot.

The main problem was linker errors, since UEFI uses PE instead of ELF you need to compile your UEFI projects as PE or wrap the ELF file into PE, which is not ideal. So I never got any UEFI app to boot, but then one day I decided to start my own UEFI library. 

But I didn't want just another copy of GNU EFI, I didn't want gigabytes of dependencies, I wanted something clean, modern, and most importantly linkable and compilable.

So when I did start **unefix** which was on August 26th 2025, I wanted something new, never seen before in this field. So my goal was a lightweight, modern, C++20 UEFI library, which brings me to this.

## What is unefix?

So what is **unefix**, actually?

It's a small, modern C++20 library for UEFI. The idea is simple, let you write UEFI apps safely, in modern C++, and little to no boilerplate.

"But what is different?" You might ask, well, in my opinion the biggest difference is the startup sequence.
The startup sequence is made for easy entry into UEFI, no more SystemTables, ImageHandles (still accessible) but rather a clean starting point.

The compilation process is simple, the library gets compiled into a PE file using clang's target triple like \<arch\>-windows-gnu, which just means to use PE but with a unix-like flavor.

This means most of the stuff is handled by the compiler, this is super straightforward, just run `CMake` and it'll compile the library, no questions asked.

The linking step is actually very simple too, contradictory to normal UEFI experiences, the linking is as simple as just running `make` after `CMake`. The makefile calls lld-link, which is just lld but with Windows-style flags, super convenient for PE work. Then it sets the entry point as `_start`, sets the type to EFI, and theoretically and most likely practically it is ready to boot in QEMU (or even real hardware).

---

## Starting Sequence?

The starting sequence in **unefix** is unique, for me at least, I have not seen any UEFI library use this method.

When the boot is called, the code starts in `_start` since that's how its set up in the Makefile, then the `_start` jumps (not calls) into the architecture specific start point, so on x86-64 `_start` will jump into `_start_x86_64` which aligns the stack, then calls the trampoline.

The trampoline is the main piece of this puzzle, this is why the main entry point of this library has no args even though its in a UEFI environment. The trampoline handles stuff such as setting up the global variables, running constructors, calling the main, running destructors, and finally exiting.

## The Runtime

**unefix** provides a very minimal but working C++ runtime, it provides a minimal RTTI to get virtual functions working, it provides support for throwing, and overall exceptions. While not perfect, it does get the job done for UEFI apps development.

---

## What's Next?

Now that you know why **unefix** exists, what it is, and how it starts, you're probably wondering: what's next?

Here’s a quick roadmap:
- **[Getting Started](installation.md)** - how to build the library and what dependencies it has.
- **[Core Concepts](usage.md)** - learn about streams, memory, files, graphics, and the entry point.
- **[Examples](examples.md)** - copy-pasteable snippets to see unefix in action.

If you want to jump in and make something, start with the examples.
If you want to understand how it works inside, hit the core concepts.

If you want to see the ugly code I use for testing, you can check that in `test/test.cpp`.