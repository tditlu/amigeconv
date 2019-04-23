#include <stdlib.h>
// #include <math.h>

#include "../buffer.h"
#include "../image.h"

// PAL4 & LOADRGB4 is the same format
buffer_t *palette_convert_pal4(image_t *const image, const unsigned int colors) {
	if (colors < 1 || colors > 256) { return NULL; }

	buffer_t *buffer = buffer_create(colors * 2);
	if (!buffer) { return NULL; }

	unsigned int j = 0;
	for (unsigned int i = 0; i < colors * 4; i += 4) {
		unsigned char r = buffer_get_byte(image->palette, i + 0);
		unsigned char g = buffer_get_byte(image->palette, i + 1);
		unsigned char b = buffer_get_byte(image->palette, i + 2);

		// Correct conversion
//		r = round((float)r / 17.0);
//		g = round((float)g / 17.0);
//		b = round((float)b / 17.0);

		// PicCon compatibility
		r >>= 4;
		g >>= 4;
		b >>= 4;

		buffer_set_byte(buffer, j++, r);
		buffer_set_byte(buffer, j++, (g << 4) + b);
	}

	return buffer;
}

buffer_t *palette_convert_pal4_copper(image_t *const image, const unsigned int colors) {
	if (colors < 1 || colors > 32) { return NULL; }

	buffer_t *buffer = buffer_create(colors * (2 * 2));
	if (!buffer) { return NULL; }

	unsigned int j = 0, reg = 0x0180;
	for (unsigned int i = 0; i < colors * 4; i += 4) {
		unsigned char r = buffer_get_byte(image->palette, i + 0);
		unsigned char g = buffer_get_byte(image->palette, i + 1);
		unsigned char b = buffer_get_byte(image->palette, i + 2);

		// Correct conversion
//		r = round((float)r / 17.0);
//		g = round((float)g / 17.0);
//		b = round((float)b / 17.0);

		// PicCon compatibility
		r >>= 4;
		g >>= 4;
		b >>= 4;

		buffer_set_byte(buffer, j++, (reg >> 8) & 255);
		buffer_set_byte(buffer, j++, reg & 255);
		buffer_set_byte(buffer, j++, r);
		buffer_set_byte(buffer, j++, (g << 4) + b);
		reg += 2;
	}

	return buffer;
}

buffer_t *palette_convert_pal8(image_t *const image, const unsigned int colors) {
	if (colors < 1 || colors > 256) { return NULL; }

	buffer_t *buffer = buffer_create(colors * 4);
	if (!buffer) { return NULL; }

	unsigned int j = 0;
	for (unsigned int i = 0; i < colors * 4; i += 4) {
		unsigned char r = buffer_get_byte(image->palette, i + 0);
		unsigned char g = buffer_get_byte(image->palette, i + 1);
		unsigned char b = buffer_get_byte(image->palette, i + 2);

		buffer_set_byte(buffer, j++, 0);
		buffer_set_byte(buffer, j++, r);
		buffer_set_byte(buffer, j++, g);
		buffer_set_byte(buffer, j++, b);
	}

	return buffer;
}

buffer_t *palette_convert_pal8_copper(image_t *const image, const unsigned int colors) {
	if (colors < 1 || colors > 256) { return NULL; }

	buffer_t *buffer = buffer_create((((((colors - 1) >> 5)) + 1) * (4 * 2)) + (colors * (4 * 2)));

	unsigned int j = 0;
	for (unsigned int i = 0; i < colors; i += 32) {
		buffer_set_byte(buffer, j++, (0x0106 >> 8) & 255);
		buffer_set_byte(buffer, j++, 0x0106 & 255);
		buffer_set_byte(buffer, j++, (((i << 8) + 0x0000) >> 8) & 255);
		buffer_set_byte(buffer, j++, ((i << 8) + 0x0000) & 255);

		for (unsigned int h = 0; h < 32; h++) { // High
			if ((i + h) >= colors) { break; }

			unsigned char r = buffer_get_byte(image->palette, ((i + h) * 4) + 0);
			unsigned char g = buffer_get_byte(image->palette, ((i + h) * 4) + 1);
			unsigned char b = buffer_get_byte(image->palette, ((i + h) * 4) + 2);

			r >>= 4;
			g >>= 4;
			b >>= 4;

			unsigned int reg = (h << 1) + 0x0180;
			buffer_set_byte(buffer, j++, (reg >> 8) & 255);
			buffer_set_byte(buffer, j++, reg & 255);
			buffer_set_byte(buffer, j++, r);
			buffer_set_byte(buffer, j++, (g << 4) + b);
		}

		buffer_set_byte(buffer, j++, (0x0106 >> 8) & 255);
		buffer_set_byte(buffer, j++, 0x0106 & 255);
		buffer_set_byte(buffer, j++, (((i << 8) + 0x0200) >> 8) & 255);
		buffer_set_byte(buffer, j++, ((i << 8) + 0x0200) & 255);

		for (unsigned int l = 0; l < 32; l++) { // Low
			if ((i + l) >= colors) { break; }

			unsigned char r = buffer_get_byte(image->palette, ((i + l) * 4) + 0);
			unsigned char g = buffer_get_byte(image->palette, ((i + l) * 4) + 1);
			unsigned char b = buffer_get_byte(image->palette, ((i + l) * 4) + 2);

			r &= 0xf;
			g &= 0xf;
			b &= 0xf;

			unsigned int reg = (l << 1) + 0x0180;
			buffer_set_byte(buffer, j++, (reg >> 8) & 255);
			buffer_set_byte(buffer, j++, reg & 255);
			buffer_set_byte(buffer, j++, r);
			buffer_set_byte(buffer, j++, (g << 4) + b);
		}
	}

	return buffer;
}

buffer_t *palette_convert_pal32(image_t *const image, const unsigned int colors) {
	if (colors < 1 || colors > 256) { return NULL; }

	buffer_t *buffer = buffer_create(colors * (4 * 3));
	if (!buffer) { return NULL; }

	unsigned int j = 0;
	for (unsigned int i = 0; i < colors * 4; i += 4) {
		unsigned char r = buffer_get_byte(image->palette, i + 0);
		unsigned char g = buffer_get_byte(image->palette, i + 1);
		unsigned char b = buffer_get_byte(image->palette, i + 2);

		for (unsigned int k = 0; k < 4; k++) {
			buffer_set_byte(buffer, j++, r);
		}

		for (unsigned int k = 0; k < 4; k++) {
			buffer_set_byte(buffer, j++, g);
		}

		for (unsigned int k = 0; k < 4; k++) {
			buffer_set_byte(buffer, j++, b);
		}
	}

	return buffer;
}

buffer_t *palette_convert_loadrgb32(image_t *const image, const unsigned int colors) {
	if (colors < 1 || colors > 256) { return NULL; }

	buffer_t *buffer = buffer_create((colors * (4 * 3)) + 4 + 4);
	if (!buffer) { return NULL; }

	unsigned int j = 0;

	buffer_set_byte(buffer, j++, (colors >> 8) & 255);
	buffer_set_byte(buffer, j++, (colors) & 255);
	buffer_set_byte(buffer, j++, 0);
	buffer_set_byte(buffer, j++, 0);

	for (unsigned int i = 0; i < colors * 4; i += 4) {
		unsigned char r = buffer_get_byte(image->palette, i + 0);
		unsigned char g = buffer_get_byte(image->palette, i + 1);
		unsigned char b = buffer_get_byte(image->palette, i + 2);

		for (unsigned int k = 0; k < 4; k++) {
			buffer_set_byte(buffer, j++, r);
		}

		for (unsigned int k = 0; k < 4; k++) {
			buffer_set_byte(buffer, j++, g);
		}

		for (unsigned int k = 0; k < 4; k++) {
			buffer_set_byte(buffer, j++, b);
		}
	}

	buffer_set_byte(buffer, j++, 0);
	buffer_set_byte(buffer, j++, 0);
	buffer_set_byte(buffer, j++, 0);
	buffer_set_byte(buffer, j++, 0);

	return buffer;
}
