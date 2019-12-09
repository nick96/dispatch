CFLAGS?=-Wall -Werror

PKG_FLAGS=$(shell pkg-config --cflags --libs libczmq)
TST_PKG_FLAGS=$(shell pkg-config --cflags --libs criterion)

SRC=$(shell find $(CWD) -name "*.c" ! -name "*_test.c")
OBJ=$(patsubst %.c,%.o,$(SRC))

TST_SRC=$(shell find $(CWD) -name "*_test.c")
TST_OBJ=$(patsubst %.c,%.o,$(TST_SRC))

BIN=dispatchctld
BIN_TEST=dispatchctld-test

all: test build

build:
	$(CC) $(PKG_FLAGS) $(CFLAGS) -c $(SRC)
	$(CC) $(PKG_FLAGS) $(CFLGAS) -o $(BIN) $(OBJ)

test: build
	$(CC) $(TST_PKG_FLAGS) $(CFLAGS) -c $(TST_SRC)
	$(CC) $(TST_PKG_FLAGS) $(CFLAGS) -o $(BIN_TEST) $(TST_OBJ)

clean:
	find . -name '*.o' -delete
	rm $(BIN)
	rm $(BIN_TEST)
