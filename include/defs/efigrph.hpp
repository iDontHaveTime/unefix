#ifndef EFIGRPH_HPP
#define EFIGRPH_HPP

#include "defs/undefix.hpp"
#include "types/untypes.hpp"

enum EFI_GRAPHICS_PIXEL_FORMAT{
    PixelRedGreenBlueReserved8BitPerColor,
    PixelBlueGreenRedReserved8BitPerColor,
    PixelBitMask,
    PixelBltOnly,
    PixelFormatMax
};

struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION{
    UINT32 Version;
    UINT32 HorizontalResolution;
    UINT32 VerticalResolution;
    EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
    UINT32 PixelPerScanLine;
};

using EFI_PHYSICAL_ADDRESS = UINT64;
struct EFI_GRAPHICS_OUTPUT_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_GRAPHICS_QUERY_MODE)(EFI_GRAPHICS_OUTPUT_PROTOCOL* _this, UINT32 modeNumber, EFI_GRAPHICS_OUTPUT_MODE_INFORMATION** info);
typedef EFI_STATUS (EFIAPI *EFI_GRAPHICS_SET_MODE)(EFI_GRAPHICS_OUTPUT_PROTOCOL* _this, UINT32 modeNumber);
typedef EFI_STATUS (EFIAPI *EFI_GRAPHICS_BLT)(EFI_GRAPHICS_OUTPUT_PROTOCOL* _this, void* buffer, int operation, UINTN sourceX, UINTN sourceY, UINTN destX, UINTN destY, UINTN width, UINTN height, UINTN delta);

struct EFI_GRAPHICS_OUTPUT_PROTOCOL{
    struct EFI_GRAPHICS_OUTPUT_MODE{
        UINT32 MaxMode;
        UINT32 Mode;
        EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* Info;
        UINTN SizeOfInfo;
        EFI_PHYSICAL_ADDRESS FrameBufferBase;
        UINTN FrameBufferSize;
    } *Mode;

    EFI_GRAPHICS_QUERY_MODE QueryMode;
    EFI_GRAPHICS_SET_MODE SetMode;
    EFI_GRAPHICS_BLT Blt;
};

#endif // EFIGRPH_HPP
