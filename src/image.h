#ifndef _IMAGE_H
#define _IMAGE_H

#include "buffer.h"

typedef struct {
	buffer_t *bitmap;
	unsigned int width;
	unsigned int height;
	unsigned int depth;

	buffer_t *palette;
	unsigned int colors;
} image_t;

typedef enum {
	IMAGE_ERROR_NO_ERROR = 0,
	IMAGE_ERROR_OPEN = 1,
	IMAGE_ERROR_DECODE = 2,
	IMAGE_ERROR_COLOR_TYPE = 3,
	IMAGE_ERROR_BIT_DEPTH = 4,
	IMAGE_ERROR_INIT_BITMAP = 5,
	IMAGE_ERROR_INIT_PALETTE = 6
} image_error_t;

image_error_t image_load(image_t *const image, const char *infile);
void image_free(image_t *const image);
const char *image_error_text(image_error_t error);

#endif /* _IMAGE_H */
