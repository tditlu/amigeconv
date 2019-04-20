#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "image.h"
#include "lodepng.h"

unsigned image_load(image_t *image, const char *infile) {
	unsigned char *png = NULL;
	size_t png_size;
	LodePNGState png_state;

	unsigned char *png_image = NULL;
	unsigned int width = 0, height = 0;

	lodepng_state_init(&png_state);
	png_state.decoder.color_convert = 0;

	unsigned error;
	error = lodepng_load_file(&png, &png_size, infile);
	if (error) {
		printf("Error: Could not open input file \"%s\".\n", infile);
	} else {
		error = lodepng_decode(&png_image, &width, &height, &png_state, png, png_size);
		if (error) {
			printf("Error: Could not decode input file \"%s\".\n", infile);
		} else {
			unsigned colortype = png_state.info_png.color.colortype;
			if (colortype != LCT_PALETTE && colortype != LCT_GREY) {
				error = 1001;
				printf("Error: Could not decode input file \"%s\", invalid color type.\n", infile);
			} else {
				unsigned bitdepth = png_state.info_png.color.bitdepth;
				if (!(bitdepth == 1 || bitdepth == 2 || bitdepth == 4 || bitdepth == 8)) {
						error = 1002;
						printf("Error: Could not decode input file \"%s\", invalid bit depth.\n", infile);
				} else {
					unsigned size = width * height;
					unsigned char *data = (unsigned char *)malloc(size);
					if (!data) {
						error = 1003;
						printf("Error: Could not decode input file \"%s\", out of memory.\n", infile);
					} else {
						memset(data, 0, size);

						unsigned char *palette = (unsigned char *)malloc(256 * 4);
						if (!palette) {
							error = 1004;
							printf("Error: Could not decode input file \"%s\", out of memory.\n", infile);
						} else {
							memset(palette, 0, 256 * 4);

							unsigned bitdepth = png_state.info_png.color.bitdepth;
							unsigned p = 1, q = 0, r = 0, a = 256, s = 0; // bitdepth == 8
							if (bitdepth == 4) {
								p = 2; q = 4; r = 4; a = 16; s = 1;
							} else if (bitdepth == 2) {
								p = 4; q = 6; r = 2; a = 4; s = 2;
							} else if (bitdepth == 1) {
								p = 8; q = 7; r = 1; a = 2; s = 3;
							}

							for (unsigned y = 0; y < height; y++) {
								for (unsigned x = 0; x < width >> s; x++) {
									unsigned c = png_image[(y * (width >> s)) + x];
									for (unsigned i = 0, j = q; i < p; i++, j -= r) {
										data[(y * width) + (x << s) + i] = (c >> j) & (a - 1);
									}
								}
							}

							unsigned depth = 0;
							unsigned i = png_state.info_png.color.palettesize;
							while (i >>= 1) { depth++; }

							unsigned char *palette = (unsigned char *)malloc(256 * 4);
							unsigned palette_size = png_state.info_png.color.palettesize;
							for (unsigned i = 0; i < palette_size; i++) {
								for (unsigned j = 0; j < 4; j++) {
									palette[(i * 4) + j] = png_state.info_png.color.palette[(i * 4) + j];
								}
							}

							image->bitmap = data;
							image->bitmap_width = width;
							image->bitmap_height = height;
							image->bitmap_depth = depth;

							image->palette = palette;
							image->palette_size = palette_size;
						}
					}
				}
			}
		}
	}
	free(png);
	lodepng_state_cleanup(&png_state);
	free(png_image);

	return error;
}

void image_free(image_t *image) {
	image->bitmap_width = image->bitmap_height = image->bitmap_depth = image->palette_size = 0;
	if (image->bitmap != NULL) { free(image->bitmap); }
	if (image->palette != NULL) { free(image->palette); }
	image->bitmap = image->palette = NULL;
}

