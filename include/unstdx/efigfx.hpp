#ifndef EFIGFX_HPP
#define EFIGFX_HPP

#include "types/untypes.hpp"
#include "unstdx/raw/trampoline.hpp"
#include "defs/efigrph.hpp"

namespace uefi{
namespace gfx{
    
enum class PixelFormat : UINT32{
    RGB, BGR, BITMASK
};

constexpr inline UINT32 GetColor(UINT8 r, UINT8 g, UINT8 b, PixelFormat fmt) noexcept{
    uint32_t pixel = 0;
    switch(fmt){
        case PixelFormat::RGB: 
            #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
            pixel = (b << 16) | (g << 8) | r; 
            #else
            pixel = (r << 16) | (g << 8) | b;
            #endif
        break;
        case PixelFormat::BGR: 
            #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
            pixel = (r << 16) | (g << 8) | b; 
            #else
            pixel = (b << 16) | (g << 8) | r; 
            #endif
            break;
        case PixelFormat::BITMASK:{
                EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* mode = uefi::raw::gop->Mode->Info;
                UINT32 red_mask = mode->PixelInformation.RedMask;
                UINT32 green_mask = mode->PixelInformation.GreenMask;
                UINT32 blue_mask = mode->PixelInformation.BlueMask;

                int red_shift = __builtin_ctz(red_mask);
                int green_shift = __builtin_ctz(green_mask);
                int blue_shift = __builtin_ctz(blue_mask);

                pixel = ((uint32_t)r << red_shift) & red_mask;
                pixel |= ((uint32_t)g << green_shift) & green_mask;
                pixel |= ((uint32_t)b << blue_shift) & blue_mask;
            }
            break;
    }
    return pixel;
}

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

    void restart() noexcept{
        _init();
    }

    UINT32 color(UINT8 r, UINT8 g, UINT8 b) noexcept{
        return GetColor(r, g, b, format);
    }

    void draw(UINT32 x, UINT32 y, UINT32 color) noexcept{
        if(x >= width || y >= height || !framebuffer) return;
        size_t idx = y * pitch + x;
        framebuffer[idx] = color;
    }

    void clear(UINT32 color) noexcept{
        if(!framebuffer) return;
        for(UINT32 y = 0; y < height; y++){
            for(UINT32 x = 0; x < width; x++){
                framebuffer[y * pitch + x] = color;
            }
        }
    }

};

}
}

#endif // EFIGFX_HPP
