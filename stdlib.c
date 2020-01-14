#include "xz_config.h"
bool memeq(const void *a, const void *b, size_t size)
{
        const uint8_t *x = a;
        const uint8_t *y = b;
        size_t i;

        for (i = 0; i < size; ++i)
                if (x[i] != y[i])
                        return false;

        return true;
}

void memzero(void *buf, size_t size)
{
        uint8_t *b = buf;
        uint8_t *e = b + size;

        while (b != e)
                *b++ = '\0';
}
void *memset(void *s, int c, size_t n)
{
        uint8_t *b = s;
        uint8_t *e = b + n;

        while (b != e)
                *b++ = c;
	return s;
}
void *memmove(void *dest, const void *src, size_t size)
{
        uint8_t *d = dest;
        const uint8_t *s = src;
        size_t i;

        if (d < s) {
                for (i = 0; i < size; ++i)
                        d[i] = s[i];
        } else if (d > s) {
                i = size;
                while (i-- > 0)
                        d[i] = s[i];
        }

        return dest;
}
