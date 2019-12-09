SRCS=$(wildcard *.c)
OBJS=$(pathsubst %.c,%.d, $(SRCS))
CFLAGS=-I$(PWD)/static-libs/include -L$(PWD)/static-libs/lib

all:
	$(CC) $(CFLAGS) -c $(SRCS) -lczmq -lzmq
