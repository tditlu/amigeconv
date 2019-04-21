#include <stdlib.h>

#include "../buffer.h"
#include "../image.h"

buffer_t *chunky_convert(image_t *const image) {
	buffer_t *buffer = buffer_create(image->width * image->height);
	if (!buffer) { return NULL; }

	unsigned int size = image->bitmap->size;
	for (unsigned int i = 0; i < size; i++) {
		unsigned char c = buffer_get_byte(image->bitmap, i);
		buffer_set_byte(buffer, i, c);
	}

	return buffer;
}
