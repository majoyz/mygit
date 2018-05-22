OBJS:=$(wildcard *.c)
EXE:=main
CC:=gcc
$(EXE):$(patsubst %.c, %.o,$(OBJS))
	$(CC) -o $@ $^
main.o:main.c
	$(CC) -c $^
multi.o:multi.c
	$(CC) -c $^
clean:
	rm $(OBJS) $(EXE)
