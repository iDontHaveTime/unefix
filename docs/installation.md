# Installation

## Dependencies

Before we install **unefix** we need to know its dependencies.
The main dependency is a C++20 Compiler, and a linker that supports PE with a EFI subsystem.

I personally use and recommend using Clang and LLD, both are modern, fast, and great tools.
And in `CMakeLists.txt` and the `Makefile` they already have Clang and LLD set up, so that's a straightforward choice. 

Speaking of `CMake` and `Makefile`, I would consider them as one of the dependencies of **unefix**.

As for unefix's dependencies as in libraries or headers, it has none. Its a standalone UEFI library with no external library or header dependencies, not even the C++'s STL or libc.

For running we have two options as dependencies, one is QEMU and OVMF, or a second one, which is hardware.
I'd obviously recommend using QEMU and OVMF first, since I never tested this on real hardware yet.

### Short list
- Clang - compiling
- LLD - linking
- QEMU - emulating
- OVMF - uefi
- CMake - building
- Make - invoking the linker

## Installing

To install it you would first copy it from github onto your computer. There are two ways to do it:
- First way: `git clone https://github.com/iDontHaveTime/unefix.git`
- Second way: Download the source code from github directly.

After you have **unefix** installed, if you are not in the folder you need to `cd` into it.
When you are there, make a new folder, I would call it `efi_test`.

Before this step, make sure you have OVMF, I myself don't know how it is on other OSes, but on my OS which is Arch Linux, I copied my OVMF from `/usr/share/ovmf` to `efi_test` using `cp /usr/share/ovmf/x64/OVMF_VARS.4m.fd efi_test/OVMF_VARS.fd`

Next step is building, to build you'll call these commands
```bash
mkdir build

cmake -S . -B build
cmake --build build

make
```
Let me explain, first of all we make a build directory, then we call `CMake` to put the build files in the `build` directory, which just makes everything nice and sorted.

After `CMake` we call `make`, the Makefile takes all the .o files from the build and links them using lld-link, the final product should come out as a `PE32+ executable for EFI`, you can check it using the `file` command on Linux, it should output something like this:
`efi/EFI/BOOT/BOOTX64.EFI: PE32+ executable for EFI (application), x86-64, 8 sections`

## Running

As mentioned before, running it has 2 ways, real hardware and qemu. I'm using QEMU and OVMF to test this library, so I never tested real hardware with this, although I think I'll test it sooner or later.

For starters make sure you have QEMU and OVMF, and make sure you copied the OVMF file into the `efi_test` directory. Let's move to the next step, using QEMU.

To use QEMU we just call it like `qemu-system-<arch>`, so for my case it would be `qemu-system-x86_64` as I'm using an x86-64 CPU. Then we need flags in QEMU, since QEMU needs to know what you are running. So it should look like this:
```bash
qemu-system-x86_64 \
    -drive if=pflash,format=raw,readonly=on,file=/usr/share/ovmf/x64/OVMF_CODE.4m.fd \
    -drive if=pflash,format=raw,file=efi_test/OVMF_VARS.fd \
    -drive file=fat:rw:efi,format=raw \
    -m 512M
```
Which calls QEMU, tells it the OVMF directories, then tells it to use the `efi` folder as the root for the UEFI with read and write permissions and using the FAT filesystem.
The `-m 512M` flag just means memory, aka how much RAM it can use.

## Done

That's it, it should boot into QEMU (or hardware) with no problem whatsoever, which it did on my machine at least.

## Next

For the next part you can check out these:
- **[Introduction](introduction.md)** - learn about why does unefix exist, and roughly how it works.
- **[Core Concepts](usage.md)** - learn about streams, memory, files, graphics, and the entry point.
- **[Examples](examples.md)** - copy-pasteable snippets to see unefix in action.