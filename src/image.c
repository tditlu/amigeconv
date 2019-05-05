#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "image.h"
#include "lodepng.h"

image_error_t image_load(image_t *const image, const char *infile) {
	image_error_t error = IMAGE_ERROR_NO_ERROR;

	unsigned char *png = NULL;
	size_t png_size;
	LodePNGState png_state;

	unsigned char *png_image = NULL;
	unsigned int width = 0, height = 0;

	lodepng_state_init(&png_state);
	png_state.decoder.color_convert = 0;

	if (lodepng_load_file(&png, &png_size, infile)) {
		error = IMAGE_ERROR_OPEN;
		goto error;
	}

	if (lodepng_decode(&png_image, &width, &height, &png_state, png, png_size)) {
		error = IMAGE_ERROR_DECODE;
		goto error;
	}

	const unsigned int colortype = png_state.info_png.color.colortype;
	if (colortype != LCT_PALETTE && colortype != LCT_GREY) {
		error = IMAGE_ERROR_COLOR_TYPE;
		goto error;
	}

	const unsigned int bitdepth = png_state.info_png.color.bitdepth;
	if (!(bitdepth == 1 || bitdepth == 2 || bitdepth == 4 || bitdepth == 8)) {
		error = IMAGE_ERROR_BIT_DEPTH;
		goto error;
	}

	buffer_t *bitmap = buffer_create(width * height);
	if (!bitmap) {
		error = IMAGE_ERROR_INIT_BITMAP;
		goto error;
	}
	image->bitmap = bitmap;

	buffer_t *palette = buffer_create(256 * 4);
	if (!palette) {
		error = IMAGE_ERROR_INIT_PALETTE;
		goto error;
	}
	image->palette = palette;

	unsigned int p = 1, q = 0, r = 0, a = 256, s = 0; // bitdepth == 8
	if (bitdepth == 4) {
		p = 2; q = 4; r = 4; a = 16; s = 1;
	} else if (bitdepth == 2) {
		p = 4; q = 6; r = 2; a = 4; s = 2;
	} else if (bitdepth == 1) {
		p = 8; q = 7; r = 1; a = 2; s = 3;
	}

	for (unsigned int y = 0; y < height; y++) {
		for (unsigned int x = 0; x < width >> s; x++) {
			unsigned int c = png_image[(y * (width >> s)) + x];
			for (unsigned int i = 0, j = q; i < p; i++, j -= r) {
				buffer_set_byte(image->bitmap, (y * width) + (x << s) + i, (c >> j) & (a - 1));
			}
		}
	}

	unsigned int depth = 0;
	unsigned int i = png_state.info_png.color.palettesize;
	while (i >>= 1) { depth++; }

	const unsigned int palette_size = png_state.info_png.color.palettesize;
	if (colortype == LCT_GREY) {
		for (unsigned int i = 0; i < palette_size; i++) {
			for (unsigned int j = 0; j < 3; j++) {
				buffer_set_byte(image->palette, (i * 4) + j, (i / (palette_size - 1)) * 255);
			}
			buffer_set_byte(image->palette, (i * 4) + 3, 255);
		}
	} else {
		for (unsigned int i = 0; i < palette_size; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				buffer_set_byte(image->palette, (i * 4) + j, png_state.info_png.color.palette[(i * 4) + j]);
			}
		}
	}

	image->width = width;
	image->height = height;
	image->depth = depth;
	image->colors = palette_size;

error:
	free(png);
	lodepng_state_cleanup(&png_state);
	free(png_image);

	return error;
}

void image_free(image_t *const image) {
	image->width = image->height = image->depth = 0;
	buffer_free(image->bitmap);
	buffer_free(image->palette);
}

const char *image_error_text(image_error_t error) {
	switch(error) {
		case IMAGE_ERROR_NO_ERROR: return "No error";
		case IMAGE_ERROR_OPEN: return "Unable to open input file";
		case IMAGE_ERROR_DECODE: return "Unable to decode input file";
		case IMAGE_ERROR_COLOR_TYPE: return "Invalid color type, only palette or grayscale supported";
		case IMAGE_ERROR_BIT_DEPTH: return "Invalid bit depth, only 1, 2, 4 & 8 supported";
		case IMAGE_ERROR_INIT_BITMAP: return "Couldn't allocate memory for bitmap";
		case IMAGE_ERROR_INIT_PALETTE: return "Couldn't allocate memory for palette";
	}

	return "Unknown error";
}
