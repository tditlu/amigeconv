#ifndef _FORMATS_PALETTE_H
#define _FORMATS_PALETTE_H

#include "../buffer.h"

buffer_t *palette_convert_pal4(image_t *const image, const unsigned int colors, const bool piccon_compatibility);
buffer_t *palette_convert_pal4_copper(image_t *const image, const unsigned int colors, const bool piccon_compatibility);
buffer_t *palette_convert_pal8(image_t *const image, const unsigned int colors);
buffer_t *palette_convert_pal8_copper(image_t *const image, const unsigned int colors);
buffer_t *palette_convert_pal32(image_t *const image, const unsigned int colors);
buffer_t *palette_convert_loadrgb32(image_t *const image, const unsigned int colors);

#endif /* _FORMATS_PALETTE_H */
