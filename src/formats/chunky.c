#include <stdlib.h>

#include "../buffer.h"
#include "../image.h"

buffer_t *chunky_convert(image_t *const image, const unsigned int depth) {
	if (depth != 2 && depth != 4 && depth != 8) { return NULL; }
	if ((image->bitmap->size * depth % 8) != 0) { return NULL; }

	unsigned int buffer_size = depth == 8 ? image->bitmap->size : (image->bitmap->size / 8) * depth;

	buffer_t *buffer = buffer_create(buffer_size);
	if (!buffer) { return NULL; }

	if (depth == 2) {
		unsigned int i = 0;
		for (unsigned int j = 0; j < buffer_size; j++) {
			unsigned char c = ((buffer_get_byte(image->bitmap, i++) & 0x03) << 6); 
			c += ((buffer_get_byte(image->bitmap, i++) & 0x03) << 4);
			c += ((buffer_get_byte(image->bitmap, i++) & 0x03) << 2);
			c += (buffer_get_byte(image->bitmap, i++) & 0x03);
			buffer_set_byte(buffer, j, c);
		}
	} else if (depth == 4) {
		unsigned int i = 0;
		for (unsigned int j = 0; j < buffer_size; j++) {
			unsigned char c = ((buffer_get_byte(image->bitmap, i++) & 0x0f) << 4);
			c += (buffer_get_byte(image->bitmap, i++) & 0x0f);
			buffer_set_byte(buffer, j, c);
		}
	} else {
		for (unsigned int i = 0; i < buffer_size; i++) {
			unsigned char c = buffer_get_byte(image->bitmap, i);
			buffer_set_byte(buffer, i, c);
		}
	}


	return buffer;
}
