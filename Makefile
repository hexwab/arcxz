CFILES=arch.s adec.c stdlib.c xz_crc32.c xz_dec_bcj.c xz_dec_stream.c \
	xz_crc64.c xz_dec_lzma2.c

adec: ${CFILES}
	 arm-none-eabi-gcc -N -Tlinker -march=armv2 -mcpu=arm2 -mtune=arm2 -nostdlib ${CFILES} -Wall -g -O2 -o adec.o
	arm-none-eabi-objcopy adec.o -O binary adec

reloc:
	arm-none-eabi-as -march=armv2 -mcpu=arm2 reloc.s -o reloc.o
	arm-none-eabi-objcopy reloc.o -O binary reloc

xztest:	stniccc,ff8
	cat stniccc,ff8 reloc |	xz -e -0 -C crc32 --lzma2=dict=32K >xztest
