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

#define AMIGECONV_VERSION "1.1.1"
#define AMIGECONV_VERSION_DATE "2025-08-03"

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
	image_t *const image,
	unsigned int depth
) {
	buffer_t *buffer = chunky_convert(image, depth);
	if (!buffer) { return false; }

	const bool error = buffer_write(buffer, outfile);
	buffer_free(buffer);

	return error;
}

static bool write_bitplane(
	const char *outfile,
	image_t *const image,
	const unsigned int depth,
	const bool interleaved,
	const bool mask,
	const bool mask_inverted
) {
	buffer_t *buffer = NULL;
	if (mask) {
		if (interleaved) {
			buffer = bitplane_convert_mask_interleaved(image, depth, mask_inverted);
		} else {
			buffer = bitplane_convert_mask(image, depth, mask_inverted);
		}
	} else {
		if (interleaved) {
			buffer = bitplane_convert_interleaved(image, depth);
		} else {
			buffer = bitplane_convert(image, depth);
		}
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
    printf("Usage: amigeconv <options> <input> <output>\n");
    printf("\n");
    printf("Available options:\n");
    printf(" -f, --format bitplane,chunky,palette,sprite         Set the desired output file format.\n");
    printf(" -p, --palette pal8,pal4,pal32,loadrgb4,loadrgb32    Set the desired palette format (only valid with palette output).\n");
    printf(" -l, --interleaved                                   Store data in interleaved format (only valid with bitplane output).\n");
    printf(" -m, --mask [inverted]                               Store data as a mask (only valid with bitplane output). Use 'inverted' to invert the mask.\n");
    printf(" -d, --depth 1-8                                     Number of bitplanes to save in the output file (only valid with bitplane, sprite, or chunky output).\n");
    printf(" -c, --colors 1-256                                  Number of colors to save in the output file (only valid with palette output).\n");
    printf(" -x, --copper                                        Generate a copper list (only valid with palette output).\n");
    printf(" -w, --width 16,32,64                                Set the sprite width (only valid with sprite output).\n");
    printf(" -t, --controlword                                   Write the control word (only valid with sprite output).\n");
    printf(" -a, --attached                                      Use attached sprite mode (only valid with sprite output).\n");
    printf(" -n, --piccon                                        Use PicCon-compatible color conversion for 4-bit palettes (only valid with palette output).\n");
    printf("\n");
}

int main(int argc, char *argv[]) {
	bool interleaved = false, mask = false, mask_inverted = false, copper = false, controlword = false, attached = false, piccon_compatibility = false;
	int depth = -1, colors = -1, width = -1;
	palette_t palette = PALETTE_UNKNOWN;
	format_t format = FORMAT_UNKNOWN;

	const struct option longopts[] = {
		{"format", required_argument, 0, 'f' },
		{"palette", required_argument, 0, 'p' },
		{"interleaved", no_argument, 0, 'l' },
		{"mask", optional_argument, 0, 'm' },
		{"depth", required_argument, 0, 'd' },
		{"colors", required_argument, 0, 'c' },
		{"copper", no_argument, 0, 'x' },
		{"width", required_argument, 0, 'w' },
		{"controlword", no_argument, 0, 't' },
		{"attached", no_argument, 0, 'a' },
		{"piccon", no_argument, 0, 'n' },
		{0, 0, 0, 0}
	};

	const char *optstring = "f:p:lm::d:c:xw:tan";

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
			case 'm':
				mask = true;
				mask_inverted = false;
				if (optarg && strcmp(optarg, "inverted") == 0) {
					mask_inverted = true;
				} else if (optind < argc - 2 && strcmp(argv[optind], "inverted") == 0) {
					mask_inverted = true;
					optind++;
				}
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
		printf("Error: No format was specified.\n\n");
		exit(EXIT_FAILURE);
	}

	if ((argc - optind) == 0) {
		usage();
		printf("Error: No input file was specified.\n\n");
		exit(EXIT_FAILURE);
	}

	if ((argc - optind) == 1) {
		usage();
		printf("Error: No output file was specified.\n\n");
		exit(EXIT_FAILURE);
	}

	if ((argc - optind) > 2) {
		usage();
		printf("Error: Too many files were specified.\n\n");
		exit(EXIT_FAILURE);
	}

	const char *infile = argv[optind++];
	const char *outfile = argv[optind++];

	image_t image;
	bool error = false;

	const image_error_t image_error = image_load(&image, infile);
	if (image_error) {
		error = true;
		printf("Error: Could not load the input file \"%s\". %s\n\n", infile, image_error_text(image_error));
		goto error;
	}

	if (format == FORMAT_CHUNKY) {
		if (depth == -1) { depth = 8; }
		if (depth != 2 && depth != 4 && depth != 8) {
			error = true;
			printf("Error: Invalid image depth in the input file.\n\n");
			goto error;
		}

		if ((image.bitmap->size * depth % 8) != 0) {
			error = true;
			printf("Error: Invalid image size in the input file.\n\n");
			goto error;
		}

		if (!write_chunky(outfile, &image, depth)) {
			error = true;
			printf("Error: Could not write the output file \"%s\".\n\n", outfile);
			goto error;
		}
	}

	if (format == FORMAT_BITPLANE) {
		if (image.width % 8 != 0) {
			error = true;
			printf("Error: Invalid image width in the input file.\n\n");
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
				printf("Error: Invalid image depth in the input file.\n\n");
			} else {
				printf("Error: Invalid depth was specified.\n\n");
			}
			goto error;
		}

		if (!write_bitplane(outfile, &image, depth, interleaved, mask, mask_inverted)) {
			error = true;
			printf("Error: Could not write the output file \"%s\".\n\n", outfile);
			goto error;
		}
	}

	if (format == FORMAT_SPRITE) {
		if (image.width % 8 != 0) {
			error = true;
			printf("Error: Invalid image width in the input file.\n\n");
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
				printf("Error: Invalid image depth in the input file.\n\n");
			} else {
				printf("Error: Invalid depth was specified.\n\n");
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
				printf("Error: Invalid image width in the input file.\n\n");
			} else {
				printf("Error: Invalid width was specified.\n\n");
			}
			goto error;
		}

		if (!write_sprite(outfile, &image, width, controlword, attached)) {
			error = true;
			printf("Error: Could not write the output file \"%s\".\n\n", outfile);
			goto error;
		}
	}

	if (format == FORMAT_PALETTE) {
		if (palette == PALETTE_UNKNOWN) {
			error = true;
			printf("Error: Invalid palette was specified.\n\n");
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
				printf("Error: Invalid colors in the input file.\n\n");
			} else {
				printf("Error: Invalid number of colors was specified.\n\n");
			}
			goto error;
		}

		if (!write_palette(outfile, &image, palette, colors, copper, piccon_compatibility)) {
			error = true;
			printf("Error: Could not write the output file \"%s\".\n\n", outfile);
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

