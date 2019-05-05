#include <stdlib.h>

#include "../buffer.h"
#include "../image.h"

buffer_t *chunky_convert(image_t *const image) {
	unsigned int size = image->bitmap->size;

	// Calculate needed buffer size
	unsigned int buffer_size = 0;
	for (unsigned int i = 0; i < size; i++) {
		buffer_size++;
	}

	buffer_t *buffer = buffer_create(buffer_size);
	if (!buffer) { return NULL; }

	for (unsigned int i = 0; i < size; i++) {
		unsigned char c = buffer_get_byte(image->bitmap, i);
		buffer_set_byte(buffer, i, c);
	}

	return buffer;
}
