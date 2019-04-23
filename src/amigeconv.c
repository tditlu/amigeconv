#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

#include "image.h"
#include "buffer.h"

#include "formats/chunky.h"
#include "formats/bitplanes.h"
#include "formats/palette.h"

typedef enum {
	PALETTE_UNKNOWN = 0,
	PALETTE_PAL4 = 1,
	PALETTE_PAL8 = 2,
	PALETTE_PAL32 = 3,
	PALETTE_LOADRGB4 = 4,
	PALETTE_LOADRGB32 = 5
} palette_t;

typedef enum {
	FORMAT_UNKNOWN = 0,
	FORMAT_BITPLANES = 1,
	FORMAT_CHUNKY = 2,
	FORMAT_SPRITES = 3,
	FORMAT_PALETTE = 4
} format_t;

static bool write_chunky(
	const char *outfile,
	image_t *const image
) {
	buffer_t *buffer = chunky_convert(image);
	if (!buffer) { return false; }

	bool error = buffer_write(buffer, outfile);
	buffer_free(buffer);

	return error;
}

static bool write_bitplanes(
	const char *outfile,
	image_t *const image,
	const unsigned int depth,
	const bool interleaved
) {
	buffer_t *buffer;
	if (interleaved) {
		buffer = bitplanes_convert_interleaved(image, depth);
	} else {
		buffer = bitplanes_convert(image, depth);
	}
	if (!buffer) { return false; }

	bool error = buffer_write(buffer, outfile);
	buffer_free(buffer);

	return error;
}

static bool write_palette(
	const char *outfile,
	image_t *const image,
	palette_t palette,
	const unsigned int colors
) {
	buffer_t *buffer;
	if (palette == PALETTE_PAL4 || palette == PALETTE_LOADRGB4) {
		buffer = palette_convert_pal4(image, colors);
	}

	if (palette == PALETTE_PAL8) {
		buffer = palette_convert_pal8(image, colors);
	}

	if (palette == PALETTE_PAL32) {
		buffer = palette_convert_pal32(image, colors);
	}

	if (palette == PALETTE_LOADRGB32) {
		buffer = palette_convert_loadrgb32(image, colors);
	}

	if (!buffer) { return false; }

	bool error = buffer_write(buffer, outfile);
	buffer_free(buffer);

	return error;
}

static void usage(int status) {
	printf("Usage: amigeconv <options> <input> <output>\n");
	printf("\n");
	printf("Available options are:\n");
	//      --------------------------------------------------------------------------------
	printf(" -i, --interleaved                                Data in output file is\n");
	printf("                                                  stored in interleaved format.\n\n");

	//      --------------------------------------------------------------------------------
	printf(" -d, --depth [1-8]                                Number of bitplanes saved\n");
	printf("                                                  in the output file, only valid\n");
	printf("                                                  for bitplanes & sprites.\n\n");

	printf(" -c, --colors [1-256]                             Number of colors saved\n");
	printf("                                                  in the output file, only valid\n");
	printf("                                                  for palette.\n\n");

	printf(" -p, --palette [pal8|pal4]                        Desired palette file format.\n\n");

	printf(" -f, --format [bitplanes|chunky|palette]          Desired output file format.\n\n");

	exit(status);
}

int main(int argc, char *argv[]) {
	bool interleaved = false;
	int depth = -1, colors = -1;
	palette_t palette = PALETTE_UNKNOWN;
	format_t format = FORMAT_UNKNOWN;

	static struct option long_options[] = {
		{"interleaved", no_argument, 0, 'i' },
		{"depth", required_argument, 0, 'd' },
		{"colors", required_argument, 0, 'c' },
		{"palette", required_argument, 0, 'p' },
		{"format", required_argument, 0, 'f' },
		{0, 0, 0, 0}
	};

	int opt = 0;
	while ((opt = getopt_long(argc, argv, "id:c:p:f:", long_options, NULL)) != EOF) {
		switch (opt) {
			case 'd':
				depth = atoi(optarg);
				break;
			case 'c':
				colors = atoi(optarg);
				break;
			case 'i':
				interleaved = true;
				break;
			case 'f':
				if (strcmp("bitplanes", optarg) == 0) {
					format = FORMAT_BITPLANES;
					break;
				}
				if (strcmp("chunky", optarg) == 0) {
					format = FORMAT_CHUNKY;
					break;
				}
				if (strcmp("sprites", optarg) == 0) {
					format = FORMAT_SPRITES;
					break;
				}
				if (strcmp("palette", optarg) == 0) {
					format = FORMAT_PALETTE;
					break;
				}
				break;
			case 'p':
				if (strcmp("pal4", optarg) == 0) {
					palette = PALETTE_PAL4;
					break;
				}
				if (strcmp("pal8", optarg) == 0) {
					palette = PALETTE_PAL8;
					break;
				}
				if (strcmp("pal32", optarg) == 0) {
					palette = PALETTE_PAL32;
					break;
				}
				if (strcmp("loadrgb4", optarg) == 0) {
					palette = PALETTE_LOADRGB4;
					break;
				}
				if (strcmp("loadrgb32", optarg) == 0) {
					palette = PALETTE_LOADRGB32;
					break;
				}
				break;
			default:
				usage(EXIT_FAILURE);
		}
	}

	if (format == FORMAT_UNKNOWN) {
		printf("Error: No format specified.\n\n");
		usage(EXIT_FAILURE);
	}

	if ((argc - optind) == 0) {
		printf("Error: No input file specified.\n\n");
		usage(EXIT_FAILURE);
	}

	if ((argc - optind) == 1) {
		printf("Error: No output file specified.\n\n");
		usage(EXIT_FAILURE);
	}

	if ((argc - optind) > 2) {
		printf("Error: Too many files specified.\n\n");
		usage(EXIT_FAILURE);
	}

	const char *infile = argv[optind++];
	const char *outfile = argv[optind++];

	image_t image;
	bool error = false;

	image_error_t image_error = image_load(&image, infile);
	if (image_error) {
		error = true;
		printf("Error: Could not load input file \"%s\". %s\n", infile, image_error_text(error));
		goto error;
	}

	if (format == FORMAT_CHUNKY && !write_chunky(outfile, &image)) {
		error = true;
		printf("Error: Could not write output file \"%s\".\n", outfile);
		goto error;
	}

	if (format == FORMAT_BITPLANES) {
		if (depth == -1) { depth = image.depth; }

		if (depth < 1 || depth > 8) {
			error = true;
			printf("Error: Invalid depth specified.\n\n");
			goto error;
		}

		if (!write_bitplanes(outfile, &image, depth, interleaved)) {
			error = true;
			printf("Error: Could not write output file \"%s\".\n", outfile);
			goto error;
		}
	}

	if (format == FORMAT_PALETTE) {
		if (palette == PALETTE_UNKNOWN) {
			error = true;
			printf("Error: Invalid palette specified.\n\n");
			goto error;
		}

		if (colors == -1) { colors = image.colors; }

		if (colors < 1 || colors > 256) {
			error = true;
			printf("Error: Invalid colors specified.\n\n");
			goto error;
		}

		if (!write_palette(outfile, &image, palette, colors)) {
			error = true;
			printf("Error: Could not write output file \"%s\".\n", outfile);
			goto error;
		}
	}

error:
	image_free(&image);
	if (error) { exit(EXIT_FAILURE); }

	return EXIT_SUCCESS;
}

