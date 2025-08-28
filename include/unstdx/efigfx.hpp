#ifndef EFIGFX_HPP
#define EFIGFX_HPP

#include "defs/efigrph.hpp"
#include "unstdx/raw/trampoline.hpp"

#warning Graphics are not yet supported

namespace uefi{
namespace gfx{
    
enum class PixelFormat : UINT32{
    RGB, BGR, BITMASK
};
class ScreenInfo{
    void _init() noexcept{
        width = raw::gop->Mode->Info->HorizontalResolution;
        height = raw::gop->Mode->Info->VerticalResolution;
        pitch = raw::gop->Mode->Info->PixelsPerScanLine;

        switch(raw::gop->Mode->Info->PixelFormat){
            case EFI_GRAPHICS_PIXEL_FORMAT::PixelRedGreenBlueReserved8BitPerColor: 
                format = PixelFormat::RGB; 
                break;
            case EFI_GRAPHICS_PIXEL_FORMAT::PixelBlueGreenRedReserved8BitPerColor: 
                format = PixelFormat::BGR; 
                break;
            case EFI_GRAPHICS_PIXEL_FORMAT::PixelBitMask: 
                format = PixelFormat::BITMASK; 
                break;
            default: 
                format = PixelFormat::RGB; 
                break;
        }

        framebuffer = (UINT32*)raw::gop->Mode->FrameBufferBase;
    }
public:
    UINT32* framebuffer;
    UINT32 width;
    UINT32 height;
    UINT32 pitch;
    PixelFormat format;


    ScreenInfo() noexcept{
        _init();
    }
};

void draw_pixel(UINT32 x, UINT32 y, uint8_t r, uint8_t g, uint8_t b, ScreenInfo& info) noexcept;

}
}

#endif // EFIGFX_HPP
