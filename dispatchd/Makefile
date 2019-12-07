SRCS=$(wildcard *.c)
OBJS=$(pathsubst %.c,%.d, $(SRCS))
INC_PATH=-I$(PWD)/../static-libs/zmq/include

all:
	$(CC) $(CFLAGS) -c $(SRCS) $(INC_PATH)
