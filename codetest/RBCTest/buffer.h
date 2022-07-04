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

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

struct buffer {
	unsigned long		start;
	unsigned long		end;
	unsigned long		capacity;
	char			*data;
};

struct buffer *buffer_new(unsigned long capacity);
void buffer_delete(struct buffer *self);
ssize_t buffer_read(struct buffer *self, fstream& fd);

static inline u8 buffer_peek_8(const struct buffer *self) {
	return self->data[self->start];
}

static inline u8 buffer_get_8(struct buffer *self) {
	unsigned long index = self->start++;
	return self->data[index];
//	return self->data[(self->start)	+1  ];
}

static inline char buffer_get_char(struct buffer *self) {
	return buffer_get_8(self);
}

static inline u16 buffer_get_le16(struct buffer *self) {
	u16 x = 0;
	x |= (u16)buffer_get_8(self);
	x |= (u16)buffer_get_8(self) << 8;
	return x;
}

static inline u32 buffer_get_le32(struct buffer *self) {
	u32 x = 0;
	x |= (u32)buffer_get_8(self);
	x |= (u32)buffer_get_8(self) << 8;
	x |= (u32)buffer_get_8(self) << 16;
	x |= (u32)buffer_get_8(self) << 24;
	return x;
}

static inline uint64_t buffer_get_le64(struct buffer *self) {
	uint64_t x = 0;
	x |= (uint64_t)buffer_get_8(self);
	x |= (uint64_t)buffer_get_8(self) << 8;
	x |= (uint64_t)buffer_get_8(self) << 16;
	x |= (uint64_t)buffer_get_8(self) << 24;
	x |= (uint64_t)buffer_get_8(self) << 32;
	x |= (uint64_t)buffer_get_8(self) << 40;
	x |= (uint64_t)buffer_get_8(self) << 48;
	x |= (uint64_t)buffer_get_8(self) << 56;
	return x;
}

static inline u16 buffer_get_be16(struct buffer *self) {
	u16 x = 0;
	x |= (u16)buffer_get_8(self) << 8;
	x |= (u16)buffer_get_8(self);
	return x;
}

static inline void buffer_get_n(struct buffer *self, int n, char *dst) {
	int i;
	for (i = 0; i < n; i++)
		*dst++ = buffer_get_8(self);
}

static inline void buffer_put(struct buffer *self, char byte) {
	self->data[self->end++] = byte;
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

static inline void buffer_advance_end(struct buffer *self, long n) {
	self->end += n;
}

static inline unsigned long buffer_size(const struct buffer *self) {
	return self->end - self->start;
}

static inline unsigned long buffer_remaining(const struct buffer *self) {
	return self->capacity - self->end;
}

static inline void buffer_reset(struct buffer *buf) {
	buf->start = buf->end = 0;
}

static inline char *buffer_find(struct buffer *buf, u8 c) {
	while (buffer_size(buf)) {
		if (buffer_peek_8(buf) == c) {
			return buffer_start(buf);
		}
		buffer_advance(buf, 1);
	}
	return NULL;
}

#ifdef __cplusplus
}
#endif
#endif
