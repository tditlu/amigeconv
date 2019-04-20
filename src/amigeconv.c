#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <math.h>

#include "image.h"
#include "lodepng.h"

typedef enum {
	FORMAT_UNKNOWN = 0,
	FORMAT_BITPLANES = 1,
	FORMAT_CHUNKY = 2,
	FORMAT_SPRITES = 3
} format_t;

static bool write_data(
	const char *outfile,
	const unsigned char *data,
	const unsigned size
) {
	FILE *f = fopen(outfile, "wb");
	if (!f) { return false; }

	fwrite(data, sizeof(unsigned char), size, f);
	fclose(f);

	return true;
}

static bool write_chunky(
	const char *outfile,
	const image_t *image
) {
	int size = image->bitmap_width * image->bitmap_height;
	return write_data(outfile, image->bitmap, size);
}

static bool write_bitplanes(
	const char *outfile,
	const image_t *image,
	const unsigned depth,
	const bool interleaved
) {
	if (image->bitmap_width % 8 != 0) { return false; }

	int size = (image->bitmap_width >> 3) * image->bitmap_height * depth;

	unsigned char *data = malloc(size);
	if (!data) { return false; }
	memset(data, 0, size);

	int i = 0;
	if (interleaved) {
		for (int y = 0; y < image->bitmap_height; y++) {
			for (int j = 0; j < depth; j++) {
				for (int x = 0; x < image->bitmap_width; x += 8) {
					unsigned char c = 0;
					for (int k = 0; k < 8; k++) {
						c += ((image->bitmap[(y * image->bitmap_width) + x + k] >> j) & 1) << ((8 - 1) - k);
					}

					data[i++] = c;
				}
			}
		}
	} else {
		for (int j = 0; j < depth; j++) {
			for (int y = 0; y < image->bitmap_height; y++) {
				for (int x = 0; x < image->bitmap_width; x += 8) {
					unsigned char c = 0;
					for (int k = 0; k < 8; k++) {
						c += ((image->bitmap[(y * image->bitmap_width) + x + k] >> j) & 1) << ((8 - 1) - k);
					}

					data[i++] = c;
				}
			}
		}
	}

	bool error = write_data(outfile, data, size);
	free(data);

	return error;
}

static void usage(int status) {
	printf("Usage: amigeconv <options> <input> <output>\n");
	printf("\n");
	printf("Available options are:\n");
	//      --------------------------------------------------------------------------------
	printf(" -i, --interleaved                          Data in output file is stored\n");
	printf("                                            in interleaved format.\n\n");

	printf(" -d, --depth [1-8]                          Number of bitplanes to be saved\n");
	printf("                                            in output file, only valid for\n");
	printf("                                            bitplanes & sprites format.\n\n");

	printf(" -f, --format [bitplanes|chunky|sprites]    Desired output file format.\n\n");

	exit(status);
}

int main(int argc, char *argv[]) {
	bool interleaved = false;
	signed depth = -1;
	format_t format = FORMAT_UNKNOWN;

	static struct option long_options[] = {
		{"interleaved", no_argument, 0, 'i' },
		{"depth", required_argument, 0, 'd' },
		{"format", required_argument, 0, 'f' },
		{0, 0, 0, 0}
	};

	int opt = 0;
	while ((opt = getopt_long(argc, argv, "id:f:", long_options, NULL)) != EOF) {
		switch (opt) {
			case 'd':
				depth = atoi(optarg);
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
				break;
			default:
				usage(EXIT_FAILURE);
		}
	}

	if (format == FORMAT_UNKNOWN) {
		printf("Error: No format specified.\n\n");
		usage(EXIT_FAILURE);
	}

	if (format == FORMAT_BITPLANES && (depth < 1 || depth > 8)) {
		printf("Error: Invalid depth specified.\n\n");
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
	unsigned error = image_load(&image, infile);
	if (error) {
		printf("Error: Could not load input file \"%s\".\n", infile);
		image_free(&image);
		exit(EXIT_FAILURE);
	}

	if (format == FORMAT_CHUNKY && !write_chunky(outfile, &image)) {
		printf("Error: Could not write output file \"%s\".\n", outfile);
		image_free(&image);
		exit(EXIT_FAILURE);
	}



	if (format == FORMAT_BITPLANES) {
		if (depth == -1) {
			depth = image.bitmap_depth;
		}
		if (depth < 1 || depth > 8) {
			printf("Error: Invalid depth specified.\n\n");
			usage(EXIT_FAILURE);
		}
		if (!write_bitplanes(outfile, &image, depth, interleaved)) {
			printf("Error: Could not write output file \"%s\".\n", outfile);
			image_free(&image);
			exit(EXIT_FAILURE);
		}
	}

	image_free(&image);
	return EXIT_SUCCESS;
}

