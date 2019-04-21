#ifndef _BUFFER_H
#define _BUFFER_H

#include <stdbool.h>

typedef struct {
	unsigned char *data;
	unsigned int size;
} buffer_t;

buffer_t *buffer_create(unsigned int size);
bool buffer_clear(buffer_t *const buffer);
unsigned char buffer_get_byte(buffer_t *const buffer, unsigned int position);
void buffer_set_byte(buffer_t *const buffer, unsigned int position, unsigned char value);
void buffer_free(buffer_t *const buffer);
bool buffer_write(buffer_t *const buffer, const char *outfile);

#endif /* _BUFFER_H */
