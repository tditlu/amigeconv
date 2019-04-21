#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "buffer.h"

buffer_t *buffer_create(unsigned int size) {
	buffer_t *buffer = malloc(sizeof(buffer_t));
	if (!buffer) { return NULL; }

	unsigned char *data = malloc(size);
	if (!data) { free(buffer); return NULL; }

	buffer->data = data;
	buffer->size = size;

	buffer_clear(buffer);

	return buffer;
}

bool buffer_clear(buffer_t *const buffer) {
	if (buffer->data != NULL && buffer->size > 0) {
		memset(buffer->data, 0, buffer->size);
		return true;
	}
	return false;
}

unsigned char buffer_get_byte(buffer_t *const buffer, unsigned int position) {
	if (buffer->data != NULL && position < buffer->size) {
		return buffer->data[position];
	}
	return 0;
}

void buffer_set_byte(buffer_t *const buffer, unsigned int position, unsigned char value) {
	if (buffer->data != NULL && position < buffer->size) {
		buffer->data[position] = value;
	}
}

void buffer_free(buffer_t *const buffer) {
	if (buffer->data != NULL) { free(buffer->data); }
	free(buffer);
}

bool buffer_write(buffer_t *const buffer, const char *outfile) {
	FILE *f = fopen(outfile, "wb");
	if (!f) { return false; }

	fwrite(buffer->data, sizeof(unsigned char), buffer->size, f);
	fclose(f);

	return true;
}

