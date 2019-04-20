#ifndef _IMAGE_H
#define _IMAGE_H

typedef struct {
	unsigned char *bitmap;
	unsigned bitmap_width;
	unsigned bitmap_height;
	unsigned bitmap_depth;

	unsigned char *palette;
	unsigned palette_size;
} image_t;

unsigned image_load(image_t *image, const char *infile);
void image_free(image_t *image);

#endif /* _IMAGE_H */
