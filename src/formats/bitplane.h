#ifndef _FORMATS_BITPLANE_H
#define _FORMATS_BITPLANE_H

#include "../buffer.h"

buffer_t *bitplane_convert(image_t *const image, const unsigned int depth);
buffer_t *bitplane_convert_mask(image_t *const image, const unsigned int depth, const bool inverted);
buffer_t *bitplane_convert_interleaved(image_t *const image, const unsigned int depth);
buffer_t *bitplane_convert_mask_interleaved(image_t *const image, const unsigned int depth, const bool inverted);

#endif /* _FORMATS_BITPLANE_H */
