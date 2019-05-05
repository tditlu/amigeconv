#include <stdlib.h>

#include "../buffer.h"
#include "../image.h"

buffer_t *bitplane_convert(image_t *const image, const unsigned int depth) {
	if (image->width % 8 != 0) { return NULL; }

	// Calculate needed buffer size
	unsigned int buffer_size = 0;
	for (unsigned int j = 0; j < depth; j++) {
		for (unsigned int y = 0; y < image->height; y++) {
			for (unsigned int x = 0; x < image->width; x += 8) {
				buffer_size++;
			}
		}
	}

	buffer_t *buffer = buffer_create(buffer_size);
	if (!buffer) { return NULL; }

	unsigned int i = 0;
	for (unsigned int j = 0; j < depth; j++) {
		for (unsigned int y = 0; y < image->height; y++) {
			for (unsigned int x = 0; x < image->width; x += 8) {
				unsigned char c = 0;
				for (unsigned int k = 0; k < 8; k++) {
					c += ((buffer_get_byte(image->bitmap, (y * image->width) + x + k) >> j) & 1) << ((8 - 1) - k);
				}
				buffer_set_byte(buffer, i++, c);
			}
		}
	}

	return buffer;
}

buffer_t *bitplane_convert_interleaved(image_t *const image, const unsigned int depth) {
	if (image->width % 8 != 0) { return NULL; }

	// Calculate needed buffer size
	unsigned int buffer_size = 0;
	for (unsigned int y = 0; y < image->height; y++) {
		for (unsigned int j = 0; j < depth; j++) {
			for (unsigned int x = 0; x < image->width; x += 8) {
				buffer_size++;
			}
		}
	}

	buffer_t *buffer = buffer_create(buffer_size);
	if (!buffer) { return NULL; }

	unsigned int i = 0;
	for (unsigned int y = 0; y < image->height; y++) {
		for (unsigned int j = 0; j < depth; j++) {
			for (unsigned int x = 0; x < image->width; x += 8) {
				unsigned char c = 0;
				for (unsigned int k = 0; k < 8; k++) {
					c += ((buffer_get_byte(image->bitmap, (y * image->width) + x + k) >> j) & 1) << ((8 - 1) - k);
				}
				buffer_set_byte(buffer, i++, c);
			}
		}
	}

	return buffer;
}
