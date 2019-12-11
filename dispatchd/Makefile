SRC=$(shell find $(CWD) -name "*.c" ! -name "*_test.c")
OBJ=$(patsubst %.c,%.o,$(SRC))

TST_SRC=$(shell find $(CWD) -name "*_test.c")
TST_OBJ=$(patsubst %.c,%.o,$(TST_SRC))

BIN=dispatchd
BIN_TEST=dispatchd-test

all: test build

build:
	$(CC) $(PKG_CONFIG_LIBZMQ) $(CFLAGS) -c $(SRC)
	$(CC) $(PKG_CONFIG_LIBZMQ) $(CFLAGS) -o $(BIN) $(OBJ)

test: build
	$(CC) $(PKG_CONFIG_CRITERION) $(CFLAGS) -c $(TST_SRC)
	$(CC) $(PKG_CONFIG_CRITERION) $(CFLAGS) -o $(BIN_TEST) $(TST_OBJ)
	./$(BIN_TEST)

clean:
	find . -name '*.o' -delete
	rm $(BIN)
	rm $(BIN_TEST)
