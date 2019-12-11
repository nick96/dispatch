export CFLAGS+=-Wall -Werror -Wextra\
	-Wduplicated-cond \
	-Wduplicated-branches \
	-Wnull-dereference \
	-Wshadow \
	-Wformat=2 \
	-Wuninitialized \
	-Wimplicit-fallthrough \
	-Wswitch-enum

export PKG_CONFIG_LIBZMQ=$(shell pkg-config --cflags --libs libczmq)
export PKG_CONFIG_CRITERION=$(shell pkg-config --cflags --libs criterion)

all: build test

check:
	command -v pkg-config
	pkg-config libczmq
	pkg-config criterion

build: dispatchd dispatchctld

dispatchctld:
	$(MAKE) -C dispatchctld build

dispatchd:
	$(MAKE) -C dispatchd build

dispatchctld-test:
	CFLAGS="$(CFLAGS) -fsanitize=address -fsanitize=leak" $(MAKE) -C dispatchctld test

dispatchd-test:
	CFLAGS="$(CFLAGS) -fsanitize=address -fsanitize=leak" $(MAKE) -C dispatchd test

test: dispatchctld-test dispatchd-test

clean:
	$(MAKE) -C dispatchctld clean
	$(MAKE) -C dispatchd clean

.PHONY: dispatchctld dispatchd
