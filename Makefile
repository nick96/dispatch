CFLAGS=-Wall -Werror

BIN=bin
DISPATCHD=$(BIN)/dispatchd


DISPATCHCTLD_SRC=$(shell find $(PWD)/dispatchd -name "*_test.c")
DISPATCHCTLD_OBJ=$(patsubst %.c,%.o,$(DISPATCHD_TST_SRC))

DISPATCHD_TST_SRC=$(shell find $(PWD)/dispatchd -name "*_test.c")
DISPATCHD_TST_OBJ=$(patsubst %.c,%.o,$(DISPATTLD_TST_SRC))

all: build test

build: dispatchd dispatchctld

dispatchctld:
	$(MAKE) -C dispatchctld build

dispatchd:
	$(MAKE) -C dispatchd build

dispatchctld-test:
	$(MAKE) -C dispatchctld test

dispatchd-test:
	$(MAKE) -C dispatchd test

test: dispatchctld-test dispatchd-test

clean:
	$(MAKE) -C dispatchctld clean
	$(MAKE) -C dispatchd clean
