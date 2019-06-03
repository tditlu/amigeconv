#include <stdlib.h>

#include "../buffer.h"
#include "../image.h"

buffer_t *chunky_convert(image_t *const image) {
	unsigned int buffer_size = image->bitmap->size;
	buffer_t *buffer = buffer_create(buffer_size);
	if (!buffer) { return NULL; }

	for (unsigned int i = 0; i < buffer_size; i++) {
		unsigned char c = buffer_get_byte(image->bitmap, i);
		buffer_set_byte(buffer, i, c);
	}

	return buffer;
}
