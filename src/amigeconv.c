#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

#include "image.h"
#include "buffer.h"

#include "formats/chunky.h"
#include "formats/bitplane.h"
#include "formats/sprite.h"
#include "formats/palette.h"

#define AMIGECONV_VERSION "1.0.6"
#define AMIGECONV_VERSION_DATE "2023-03-17"

typedef enum {
	PALETTE_UNKNOWN = 0,
	PALETTE_PAL4 = 1,
	PALETTE_PAL4_COPPER = 2,
	PALETTE_PAL8 = 3,
	PALETTE_PAL8_COPPER = 4,
	PALETTE_PAL32 = 5,
	PALETTE_LOADRGB4 = 6,
	PALETTE_LOADRGB32 = 7
} palette_t;

typedef enum {
	FORMAT_UNKNOWN = 0,
	FORMAT_BITPLANE = 1,
	FORMAT_CHUNKY = 2,
	FORMAT_SPRITE = 3,
	FORMAT_PALETTE = 4
} format_t;

static bool write_chunky(
	const char *outfile,
	image_t *const image
) {
	buffer_t *buffer = chunky_convert(image);
	if (!buffer) { return false; }

	const bool error = buffer_write(buffer, outfile);
	buffer_free(buffer);

	return error;
}

static bool write_bitplane(
	const char *outfile,
	image_t *const image,
	const unsigned int depth,
	const bool interleaved
) {
	buffer_t *buffer = NULL;
	if (interleaved) {
		buffer = bitplane_convert_interleaved(image, depth);
	} else {
		buffer = bitplane_convert(image, depth);
	}
	if (!buffer) { return false; }

	const bool error = buffer_write(buffer, outfile);
	buffer_free(buffer);

	return error;
}

static bool write_sprite(
	const char *outfile,
	image_t *const image,
	const unsigned int width,
	const bool controlword,
	const bool attached
) {
	buffer_t *buffer = NULL;
	if (attached) {
		buffer = sprite_convert_attached(image, width, controlword);
	} else {
		buffer = sprite_convert(image, width, controlword);
	}
	if (!buffer) { return false; }

	const bool error = buffer_write(buffer, outfile);
	buffer_free(buffer);

	return error;
}

static bool write_palette(
	const char *outfile,
	image_t *const image,
	palette_t palette,
	const unsigned int colors,
	bool copper,
	const bool piccon_compatibility
) {
	buffer_t *buffer = NULL;
	if (palette == PALETTE_PAL4) {
		if (copper) {
			buffer = palette_convert_pal4_copper(image, colors, piccon_compatibility);
		} else {
			buffer = palette_convert_pal4(image, colors, piccon_compatibility);
		}
	}

	if (palette == PALETTE_PAL8) {
		if (copper) {
			buffer = palette_convert_pal8_copper(image, colors);
		} else {
			buffer = palette_convert_pal8(image, colors);
		}
	}

	if (palette == PALETTE_PAL32) {
		buffer = palette_convert_pal32(image, colors);
	}

	if (palette == PALETTE_LOADRGB4) {
		buffer = palette_convert_pal4(image, colors, piccon_compatibility);
	}

	if (palette == PALETTE_LOADRGB32) {
		buffer = palette_convert_loadrgb32(image, colors);
	}

	if (!buffer) { return false; }

	const bool error = buffer_write(buffer, outfile);
	buffer_free(buffer);

	return error;
}

static void usage() {
	printf("Amigeconv (Amiga Image Converter) by Todi / Tulou - version %s (%s)\n\n", AMIGECONV_VERSION, AMIGECONV_VERSION_DATE);
	printf("Usage: amigeconv <options> <input> <output>\n");
	printf("\n");
	printf("Available options are:\n");
	printf(" -f, --format [bitplane|chunky|palette|sprite]         Desired output file format.\n");
	printf(" -p, --palette [pal8|pal4|pal32|loadrgb4|loadrgb32]    Desired palette file format.\n");
	printf(" -l, --interleaved                                     Data in output file is stored in interleaved format, only valid with bitplane output file format.\n");
	printf(" -d, --depth [1-8]                                     Number of bitplane saved in the output file, only valid with bitplane or sprite output file format.\n");
	printf(" -c, --colors [1-256]                                  Number of colors saved in the output file, only valid with palette output file format.\n");
	printf(" -x, --copper                                          Generate copper list, only valid with palette output file format.\n");
	printf(" -w, --width [16,32,64]                                Width, only valid with sprite output file format.\n");
	printf(" -t, --controlword                                     Write control word, only valid with sprite output file format.\n");
	printf(" -a, --attached                                        Attach mode sprite, only valid with sprite output file format.\n");
	printf(" -n, --piccon                                          Use PicCon compatible color conversion for 4 bit palette, only valid with palette output file format.\n");
	printf("\n");
}

int main(int argc, char *argv[]) {
	bool interleaved = false, copper = false, controlword = false, attached = false, piccon_compatibility = false;
	int depth = -1, colors = -1, width = -1;
	palette_t palette = PALETTE_UNKNOWN;
	format_t format = FORMAT_UNKNOWN;

	const struct option longopts[] = {
		{"format", required_argument, 0, 'f' },
		{"palette", required_argument, 0, 'p' },
		{"interleaved", no_argument, 0, 'l' },
		{"depth", required_argument, 0, 'd' },
		{"colors", required_argument, 0, 'c' },
		{"copper", required_argument, 0, 'x' },
		{"width", required_argument, 0, 'w' },
		{"controlword", no_argument, 0, 't' },
		{"attached", no_argument, 0, 'a' },
		{"piccon", no_argument, 0, 'n' },
		{0, 0, 0, 0}
	};

	const char *optstring = "f:p:ld:c:xw:ta";

	if (argc <= 1) {
		usage();
		exit(EXIT_FAILURE);
	}

	int opt = 0;
	while ((opt = getopt_long(argc, argv, optstring, longopts, 0)) != EOF) {
		switch (opt) {
			case 'f':
				if (!strcmp("bitplane", optarg)) {
					format = FORMAT_BITPLANE;
					break;
				}
				if (!strcmp("chunky", optarg)) {
					format = FORMAT_CHUNKY;
					break;
				}
				if (!strcmp("sprite", optarg)) {
					format = FORMAT_SPRITE;
					break;
				}
				if (!strcmp("palette", optarg)) {
					format = FORMAT_PALETTE;
					break;
				}
				break;
			case 'p':
				if (!strcmp("pal4", optarg)) {
					palette = PALETTE_PAL4;
					break;
				}
				if (!strcmp("pal8", optarg)) {
					palette = PALETTE_PAL8;
					break;
				}
				if (!strcmp("pal32", optarg)) {
					palette = PALETTE_PAL32;
					break;
				}
				if (!strcmp("loadrgb4", optarg)) {
					palette = PALETTE_LOADRGB4;
					break;
				}
				if (!strcmp("loadrgb32", optarg)) {
					palette = PALETTE_LOADRGB32;
					break;
				}
				break;
			case 'l':
				interleaved = true;
				break;
			case 'd':
				depth = atoi(optarg);
				break;
			case 'c':
				colors = atoi(optarg);
				break;
			case 'x':
				copper = true;
				break;
			case 'w':
				width = atoi(optarg);
				break;
			case 't':
				controlword = true;
				break;
			case 'a':
				attached = true;
				break;
			case 'n':
				piccon_compatibility = true;
				break;
			default:
				usage();
				exit(EXIT_FAILURE);
		}
	}

	if (format == FORMAT_UNKNOWN) {
		usage();
		printf("Error: No format specified.\n\n");
		exit(EXIT_FAILURE);
	}

	if ((argc - optind) == 0) {
		usage();
		printf("Error: No input file specified.\n\n");
		exit(EXIT_FAILURE);
	}

	if ((argc - optind) == 1) {
		usage();
		printf("Error: No output file specified.\n\n");
		exit(EXIT_FAILURE);
	}

	if ((argc - optind) > 2) {
		usage();
		printf("Error: Too many files specified.\n\n");
		exit(EXIT_FAILURE);
	}

	const char *infile = argv[optind++];
	const char *outfile = argv[optind++];

	image_t image;
	bool error = false;

	const image_error_t image_error = image_load(&image, infile);
	if (image_error) {
		error = true;
		printf("Error: Could not load input file \"%s\". %s\n\n", infile, image_error_text(image_error));
		goto error;
	}

	if (format == FORMAT_CHUNKY && !write_chunky(outfile, &image)) {
		error = true;
		printf("Error: Could not write output file \"%s\".\n\n", outfile);
		goto error;
	}

	if (format == FORMAT_BITPLANE) {
		if (image.width % 8 != 0) {
			error = true;
			printf("Error: Invalid input file width.\n\n");
			goto error;
		}

		bool depth_not_set = false;
		if (depth == -1) {
			depth = image.depth;
			depth_not_set = true;
		}

		if (depth < 1 || depth > 8) {
			error = true;
			if (depth_not_set) {
				printf("Error: Invalid input file image depth.\n\n");
			} else {
				printf("Error: Invalid depth specified.\n\n");
			}
			goto error;
		}

		if (!write_bitplane(outfile, &image, depth, interleaved)) {
			error = true;
			printf("Error: Could not write output file \"%s\".\n\n", outfile);
			goto error;
		}
	}

	if (format == FORMAT_SPRITE) {
		if (image.width % 8 != 0) {
			error = true;
			printf("Error: Invalid input file width.\n\n");
			goto error;
		}

		bool depth_not_set = false;
		if (depth == -1) {
			depth = image.depth;
			depth_not_set = true;
		}

		if ((!attached && depth != 2) || (attached && depth != 4)) {
			error = true;
			if (depth_not_set) {
				printf("Error: Invalid input file image depth.\n\n");
			} else {
				printf("Error: Invalid depth specified.\n\n");
			}
			goto error;
		}

		bool width_not_set = false;
		if (width == -1) {
			width = image.width;
			width_not_set = true;
		}

		if (width != 16 && width != 32 && width != 64) {
			error = true;
			if (width_not_set) {
				printf("Error: Invalid input file image width.\n\n");
			} else {
				printf("Error: Invalid width specified.\n\n");
			}
			goto error;
		}

		if (!write_sprite(outfile, &image, width, controlword, attached)) {
			error = true;
			printf("Error: Could not write output file \"%s\".\n\n", outfile);
			goto error;
		}
	}

	if (format == FORMAT_PALETTE) {
		if (palette == PALETTE_UNKNOWN) {
			error = true;
			printf("Error: Invalid palette specified.\n\n");
			goto error;
		}

		bool colors_not_set = false;
		if (colors == -1) {
			colors = image.colors;
			colors_not_set = true;
		}

		if (colors < 1 || colors > 256) {
			error = true;
			if (colors_not_set) {
				printf("Error: Invalid input file image colors.\n\n");
			} else {
				printf("Error: Invalid colors specified.\n\n");
			}
			goto error;
		}

		if (!write_palette(outfile, &image, palette, colors, copper, piccon_compatibility)) {
			error = true;
			printf("Error: Could not write output file \"%s\".\n\n", outfile);
			goto error;
		}
	}

error:
	if (!image_error) {
		image_free(&image);
	}

	if (error) {
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}

