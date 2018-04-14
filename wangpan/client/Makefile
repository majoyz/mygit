SOURCES:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,${SOURCES})
main:${OBJS}
	gcc $^ -o $@ -pthread -lcrypt -l crypto

clean:
	rm main ${OBJS}
