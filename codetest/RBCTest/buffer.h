#ifndef BUFFER_H
#define BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/socket.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdarg.h>
#include <fstream>
#include <stdint.h>
#include <unistd.h>	/* for ssize_t */
using namespace std;

struct buffer {
	unsigned long		start;
	unsigned long		end;
	unsigned long		capacity;
	char			*data;
};

static inline void buffer_reset(struct buffer *buf)
{
        buf->start = buf->end = 0;
}

static inline uint8_t buffer_get_8(struct buffer *self) {
        return self->data[self->start++];
}

static inline uint16_t buffer_get_le16(struct buffer *self) {
	uint16_t x = 0;
	x |= (uint16_t)buffer_get_8(self);
	x |= (uint16_t)buffer_get_8(self) << 8;
	return x;
}

static inline char *buffer_start(const struct buffer *self) {
	return &self->data[self->start];
}

static inline char *buffer_end(const struct buffer *self) {
	return &self->data[self->end];
}

static inline void buffer_advance(struct buffer *self, long n) {
	self->start += n;
}

static inline unsigned long buffer_size(const struct buffer *self) {
	return self->end - self->start;
}

static inline unsigned long buffer_remaining(const struct buffer *self) {
	return self->capacity - self->end;
}

#ifdef __cplusplus
}
#endif
#endif
