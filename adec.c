#include "xz_config.h"
#include "xz.h"
/*#include "xz_private.h"*/
#include <stdbool.h>
int open(const char *fn);
int close(int fd);
int read(int size, int fd, void *buf);
void *memcpy(void *dest, const void *src, size_t n);
void wrch(void *c, int len);
void hex(uint32_t n);
void osexit(void);
void puts(const char *s);
#define RELOC_CODE 646888
#define BUFSIZE 4096
#define OUTSIZE 640*1024
#define HEAPSIZE 64*1024
#define STACKSIZE 4096
/* define DEBUG */
char h[HEAPSIZE], *heap=h;
uint8_t buf[BUFSIZE];
uint8_t out[OUTSIZE];
uint8_t stack[STACKSIZE];

void main(void) {
	struct xz_buf b;
	struct xz_dec *s;
	enum xz_ret ret;
	char *msg;
	xz_crc32_init();
#ifdef XZ_USE_CRC64
        xz_crc64_init();
#endif
        s = xz_dec_init(XZ_DYNALLOC, 1048576);
        b.in = buf;
        b.in_pos = 0;
        b.in_size = 0;
        b.out = out;
        b.out_pos = 0;
        b.out_size = OUTSIZE;
	int sp=0;
	int fd = open ("xztest");
	while (true) {
                if (b.in_pos == b.in_size) {
			/*wrch("<",1);*/
			b.in_size=read(BUFSIZE, fd, buf);
			b.in_pos = 0;
			wrch("/\b|\b\\\b-\b"+(sp=(sp+2)&6),2);
			/*hex(b.in_size);*/
			/*wrch("!",1);*/
		}
		/*wrch("q",1);*/
		ret = xz_dec_run(s, &b);
		if (ret == XZ_OK) {
			/*wrch(".",1);*/
                        continue;
		}
		switch (ret) {
                case XZ_STREAM_END:
			close(fd);
                        xz_dec_end(s);
                        {
				/*puts("done");*/
#if 1
				void (*reloc)(void *,int,void *) = out + RELOC_CODE;
				reloc(out, RELOC_CODE, 0x8000);
#else
				wrch(out, b.out_pos);
				osexit();
#endif
			}
#if DEBUG
		case XZ_MEM_ERROR:
                        msg = "Memory allocation failed\n";
                        goto error;

                case XZ_MEMLIMIT_ERROR:
                        msg = "Memory usage limit reached\n";
                        goto error;

                case XZ_FORMAT_ERROR:
                        msg = "Not a .xz file\n";
                        goto error;

                case XZ_OPTIONS_ERROR:
                        msg = "Unsupported options in the .xz headers\n";
                        goto error;

                case XZ_DATA_ERROR:
                case XZ_BUF_ERROR:
                        msg = "File is corrupt\n";
                        goto error;
                default:
                        msg = "Bug!\n";
                        goto error;
#else
		default:
			msg = ":(";
			goto error;
#endif
		}
	}
error:
	close(fd);
	puts(msg);
	osexit();
}

void *malloc(size_t n) {
	void *ret=heap;
	heap+=n;
	return ret;
}

void free(void *p) {
}
