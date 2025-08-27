#include "unstdx/efigfx.hpp"

namespace uefi{
namespace gfx{

void draw_pixel(UINT32 x, UINT32 y, uint8_t r, uint8_t g, uint8_t b, ScreenInfo& info) noexcept{
    if(x >= info.width || y >= info.height) return;

    size_t idx = y * info.pitch + x;
    uint32_t pixel = 0;

    switch(info.format){
        case PixelFormat::RGB: 
            pixel = (r << 16) | (g << 8) | b; 
            break;
        case PixelFormat::BGR: 
            pixel = (b << 16) | (g << 8) | r; 
            break;
        case PixelFormat::BITMASK:
            break;
    }

    info.framebuffer[idx] = pixel;
}

}
}