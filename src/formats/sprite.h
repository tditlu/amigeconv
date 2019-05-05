#ifndef _FORMATS_SPRITE_H
#define _FORMATS_SPRITE_H

#include "../buffer.h"

buffer_t *sprite_convert(image_t *const image, const unsigned int width, const bool controlword);
buffer_t *sprite_convert_attached(image_t *const image, const unsigned int width, const bool controlword);

#endif /* _FORMATS_SPRITE_H */
