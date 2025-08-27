# unefix (pronounced you-neh-fix)

## A minimal, freestanding UEFI library in C++ for OS devs.

`unefix` is a lightweight and independent UEFI library that allows you to write UEFI applications and OS boot code without relying on GNU EFI or mingw. It works out-of-the-box with **Clang** + **LLD** (requirements), and only depends on CMake and Make for building.

## Features
- Pure C++ freestanding library, no external dependencies (besides Clang + LLD).
- PE/COFF executable ready to boot in QEMU with OVMF.
- Has minimal exceptions and rtti support
- Fully supports virtual functions

---

## Quickstart
```bash
# Clone
git clone https://github.com/iDontHaveTime/unefix.git
cd unefix

# Build
mkdir build
cmake -S . -B build
cmake --build build
make
```

## Running it

After building, your UEFI executable (`BOOTX64.EFI`) will be located in `build/efi/BOOT/`. To run it in QEMU with OVMF:
```bash
# Make sure OVMF is installed.

mkdir -p efi_test
# Copy OVMF_VARS to keep UEFI variable changes persistent
cp /usr/share/ovmf/x64/OVMF_VARS.4m.fd efi_test/OVMF_VARS.fd

qemu-system-x86_64 \
    -drive if=pflash,format=raw,readonly=on,file=/usr/share/ovmf/x64/OVMF_CODE.4m.fd \
    -drive if=pflash,format=raw,file=efi_test/OVMF_VARS.fd \
    -drive file=fat:rw:efi,format=raw \
    -m 512M
```

## Example
- The example can be found in `test/test.cpp`.

---

## Roadmap
- Add filesystem support.
- Expand into a full UEFI standard library for OS development.
- Kernel Loader (ELF Kernel)