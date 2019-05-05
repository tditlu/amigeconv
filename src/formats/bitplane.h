#ifndef _FORMATS_BITPLANE_H
#define _FORMATS_BITPLANE_H

#include "../buffer.h"

buffer_t *bitplane_convert(image_t *const image, const unsigned int depth);
buffer_t *bitplane_convert_interleaved(image_t *const image, const unsigned int depth);

#endif /* _FORMATS_BITPLANE_H */
