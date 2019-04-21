#include <stdlib.h>

#include "../buffer.h"
#include "../image.h"

buffer_t *bitplanes_convert(image_t *const image, const unsigned int depth, const bool interleaved) {
	if (image->width % 8 != 0) { return NULL; }

	buffer_t *buffer = buffer_create((image->width >> 3) * image->height * depth);
	if (!buffer) { return NULL; }

	int i = 0;
	if (interleaved) {
		for (int y = 0; y < image->height; y++) {
			for (int j = 0; j < depth; j++) {
				for (int x = 0; x < image->width; x += 8) {
					unsigned char c = 0;
					for (int k = 0; k < 8; k++) {
						c += ((buffer_get_byte(image->bitmap, (y * image->width) + x + k) >> j) & 1) << ((8 - 1) - k);
					}
					buffer_set_byte(buffer, i++, c);
				}
			}
		}
	} else {
		for (int j = 0; j < depth; j++) {
			for (int y = 0; y < image->height; y++) {
				for (int x = 0; x < image->width; x += 8) {
					unsigned char c = 0;
					for (int k = 0; k < 8; k++) {
						c += ((buffer_get_byte(image->bitmap, (y * image->width) + x + k) >> j) & 1) << ((8 - 1) - k);
					}
					buffer_set_byte(buffer, i++, c);
				}
			}
		}
	}

	return buffer;
}
