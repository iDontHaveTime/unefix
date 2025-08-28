#ifndef EFIGRPH_HPP
#define EFIGRPH_HPP

#include "defs/undefix.hpp"
#include "types/untypes.hpp"

struct EFI_PIXEL_BITMASK{
    UINT32 RedMask;
    UINT32 GreenMask;
    UINT32 BlueMask;  
    UINT32 ReservedMask;  
};

enum class EFI_GRAPHICS_PIXEL_FORMAT : UINT32{
    PixelRedGreenBlueReserved8BitPerColor, PixelBlueGreenRedReserved8BitPerColor, PixelBitMask,
    PixelBltOnly, PixelFormatMax
};

struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION{
    UINT32 Version;
    UINT32 HorizontalResolution;
    UINT32 VerticalResolution;
    EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
    EFI_PIXEL_BITMASK PixelInformation;
    UINT32 PixelsPerScanLine;
};

struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL{
    UINT8 Blue;
    UINT8 Green;
    UINT8 Red;
    UINT8 Reserved;
};

union EFI_GRAPHICS_OUTPUT_BLT_PIXEL_UNION{
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL Pixel;
    UINT32 Raw;
};

struct EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE{
    UINT32 MaxMode;
    UINT32 Mode;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* Info;
    UINTN SizeOfInfo;
    EFI_PHYSICAL_ADDRESS FrameBufferBase;
    UINTN FrameBufferSize;
};

struct EFI_GRAPHICS_OUTPUT_PROTOCOL;

enum class EFI_GRAPHICS_OUTPUT_BLT_OPERATION : UINT32{
    EfiBltVideoFill, EfiBltVideoToBltBuffer,
    EfiBltBufferToVideo, EfiBltVideoToVideo,
    EfiGraphicsOutputBltOperationMax
};

typedef EFI_STATUS(EFIAPI *EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE)(IN EFI_GRAPHICS_OUTPUT_PROTOCOL* _this, IN UINT32 modeNumber, OUT UINTN* sizeOfInfo, OUT EFI_GRAPHICS_OUTPUT_MODE_INFORMATION** info);
typedef EFI_STATUS(EFIAPI *EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE)(IN EFI_GRAPHICS_OUTPUT_PROTOCOL* _this, IN UINT32 modeNumber);
typedef EFI_STATUS(EFIAPI *EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT)(IN EFI_GRAPHICS_OUTPUT_PROTOCOL* _this, IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL* bltBuffer OPTIONAL, IN EFI_GRAPHICS_OUTPUT_BLT_OPERATION bltOperation, IN UINTN sourceX, IN UINTN sourceY, IN UINTN destinationX, IN UINTN destinationY, IN UINTN width, IN UINTN height, IN UINTN delta OPTIONAL);

struct EFI_GRAPHICS_OUTPUT_PROTOCOL{
    EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE QueryMode;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE SetMode;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT Blt;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE* Mode;
};

constexpr EFI_GUID EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}};

#endif // EFIGRPH_HPP
