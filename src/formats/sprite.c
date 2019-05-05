#include <stdio.h>
#include <stdlib.h>

#include "../buffer.h"
#include "../image.h"

buffer_t *sprite_convert(image_t *const image, const unsigned int width, const bool controlword) {
	if (image->width % 8 != 0) { return NULL; }
	if (width != 16 && width != 32 && width != 64) { return NULL; }

	// Calculate needed buffer size
	unsigned int buffer_size = 0;
	for (unsigned int x = 0; x < image->width; x += width) {
		if (controlword) {
			for (unsigned int i = 0; i < width >> 2; i++) {
				buffer_size++;
			}
		}
		for (unsigned int y = 0; y < image->height; y++) {
			for (unsigned int i = 0; i < width; i += 8) {
				buffer_size++;
			}

			for (unsigned int i = 0; i < width; i += 8) {
				buffer_size++;
			}
		}
		if (controlword) {
			for (unsigned int i = 0; i < width >> 2; i++) {
				buffer_size++;
			}
		}
	}

	buffer_t *buffer = buffer_create(buffer_size);
	if (!buffer) { return NULL; }

	unsigned int b = 0;
	for (unsigned int x = 0; x < image->width; x += width) {
		if (controlword) {
			for (unsigned int i = 0; i < width >> 2; i++) {
				buffer_set_byte(buffer, b++, 0);
			}
		}
		for (unsigned int y = 0; y < image->height; y++) {
			for (unsigned int i = 0; i < width; i += 8) {
				unsigned char c = 0;
				for (unsigned int j = 0; j < 8; j++) { // Low
					c += (buffer_get_byte(image->bitmap, (y * image->width) + x + i + j) & 1) << ((8 - 1) - j);
				}
				buffer_set_byte(buffer, b++, c);
			}

			for (unsigned int i = 0; i < width; i += 8) {
				unsigned char c = 0;
				for (unsigned int j = 0; j < 8; j++) { // High
					c += ((buffer_get_byte(image->bitmap, (y * image->width) + x + i + j) >> 1) & 1) << ((8 - 1) - j);
				}
				buffer_set_byte(buffer, b++, c);
			}
		}
		if (controlword) {
			for (unsigned int i = 0; i < width >> 2; i++) {
				buffer_set_byte(buffer, b++, 0);
			}
		}
	}

	return buffer;
}

buffer_t *sprite_convert_attached(image_t *const image, const unsigned int width, const bool controlword) {
	if (image->width % 8 != 0) { return NULL; }
	if (width != 16 && width != 32 && width != 64) { return NULL; }

	// Calculate needed buffer size
	unsigned int buffer_size = 0;
	for (unsigned int x = 0; x < image->width; x += width) {
		if (controlword) {
			for (unsigned int i = 0; i < width >> 2; i++) {
				buffer_size++;
			}
		}
		for (unsigned int y = 0; y < image->height; y++) {
			for (unsigned int i = 0; i < width; i += 8) {
				buffer_size++;
			}

			for (unsigned int i = 0; i < width; i += 8) {
				buffer_size++;
			}
		}
		if (controlword) {
			for (unsigned int i = 0; i < width >> 2; i++) {
				buffer_size++;
				buffer_size++;
			}
		}
		for (unsigned int y = 0; y < image->height; y++) {
			for (unsigned int i = 0; i < width; i += 8) {
				buffer_size++;
			}

			for (unsigned int i = 0; i < width; i += 8) {
				buffer_size++;
			}
		}
		if (controlword) {
			for (unsigned int i = 0; i < width >> 2; i++) {
				buffer_size++;
			}
		}
	}

	buffer_t *buffer = buffer_create(buffer_size);
	if (!buffer) { return NULL; }

	unsigned int b = 0;
	for (unsigned int x = 0; x < image->width; x += width) {
		if (controlword) {
			for (unsigned int i = 0; i < width >> 2; i++) {
				buffer_set_byte(buffer, b++, 0);
			}
		}
		for (unsigned int y = 0; y < image->height; y++) {
			for (unsigned int i = 0; i < width; i += 8) {
				unsigned char c = 0;
				for (unsigned int j = 0; j < 8; j++) { // Low
					c += (buffer_get_byte(image->bitmap, (y * image->width) + x + i + j) & 1) << ((8 - 1) - j);
				}
				buffer_set_byte(buffer, b++, c);
			}

			for (unsigned int i = 0; i < width; i += 8) {
				unsigned char c = 0;
				for (unsigned int j = 0; j < 8; j++) { // High
					c += ((buffer_get_byte(image->bitmap, (y * image->width) + x + i + j) >> 1) & 1) << ((8 - 1) - j);
				}
				buffer_set_byte(buffer, b++, c);
			}
		}
		if (controlword) {
			for (unsigned int i = 0; i < width >> 2; i++) {
				buffer_set_byte(buffer, b++, 0);
				buffer_set_byte(buffer, b++, 0);
			}
		}
		for (unsigned int y = 0; y < image->height; y++) {
			for (unsigned int i = 0; i < width; i += 8) {
				unsigned char c = 0;
				for (unsigned int j = 0; j < 8; j++) { // Low
					c += ((buffer_get_byte(image->bitmap, (y * image->width) + x + i + j) >> 2) & 1) << ((8 - 1) - j);
				}
				buffer_set_byte(buffer, b++, c);
			}

			for (unsigned int i = 0; i < width; i += 8) {
				unsigned char c = 0;
				for (unsigned int j = 0; j < 8; j++) { // High
					c += ((buffer_get_byte(image->bitmap, (y * image->width) + x + i + j) >> 3) & 1) << ((8 - 1) - j);
				}
				buffer_set_byte(buffer, b++, c);
			}
		}
		if (controlword) {
			for (unsigned int i = 0; i < width >> 2; i++) {
				buffer_set_byte(buffer, b++, 0);
			}
		}
	}

	return buffer;
}
