#ifndef _FORMATS_BITPLANES_H
#define _FORMATS_BITPLANES_H

#include "../buffer.h"

buffer_t *bitplanes_convert(image_t *const image, const unsigned int depth, const bool interleaved);

#endif /* _FORMATS_BITPLANES_H */
