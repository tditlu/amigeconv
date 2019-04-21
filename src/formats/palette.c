#include <stdlib.h>

#include "../buffer.h"
#include "../image.h"

buffer_t *palette_convert(image_t *const image, const unsigned int colors) {
	if (colors < 1 || colors > 256) { return NULL; }

	buffer_t *buffer = buffer_create(colors * 4);
	if (!buffer) { return NULL; }
	for (unsigned int i = 0; i < colors * 4; i += 4) {

		unsigned char r = buffer_get_byte(image->palette, i + 0);
		unsigned char g = buffer_get_byte(image->palette, i + 1);
		unsigned char b = buffer_get_byte(image->palette, i + 2);

		buffer_set_byte(buffer, i + 0, 0);
		buffer_set_byte(buffer, i + 1, r);
		buffer_set_byte(buffer, i + 2, g);
		buffer_set_byte(buffer, i + 3, b);
	}

	return buffer;
}
