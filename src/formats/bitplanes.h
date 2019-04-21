#ifndef _FORMATS_BITPLANES_H
#define _FORMATS_BITPLANES_H

#include "../buffer.h"

buffer_t *bitplanes_convert(image_t *const image, const unsigned int depth);
buffer_t *bitplanes_convert_interleaved(image_t *const image, const unsigned int depth);

#endif /* _FORMATS_BITPLANES_H */
