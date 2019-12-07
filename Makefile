BIN=bin
DISPATCHCTLD=$(BIN)/dispatchctld
DISPATCHD=$(BIN)/dispatchd

STATIC_LIB_DIR=$(PWD)/static-libs
LIBZMQ_STATIC_DIR=$(PWD)/static-libs/zmq
LIBZMQ_STATIC_LIB=$(LIBZMQ_STATIC_DIR)/lib/libzmq.a

LIBZMQ_SRC=$(PWD)/libzmq
DISPATCHCTLD_SRC=$(PWD)/dispatchctld
DISPATCHD_SRC=$(PWD)/dispatchd

CFLAGS=-L$(LIBZMQ_STATIC_LIB)

all: statics dispatchd dispatchctld

statics: static-libzmq

static-libzmq:
	cd $(LIBZMQ_SRC) && ./autogen.sh &>/dev/null
	cd $(LIBZMQ_SRC) && ./configure --enable-static --disable-shared --prefix=$(STATIC_LIB_DIR)/zmq &>/dev/null
	$(MAKE) -C $(LIBZMQ_SRC) install &>/dev/null
	libtool --finish $(STATIC_LIB_DIR)/zmq/lib &>/dev/null

dispatchctld: dispatchctld_objs
	$(CC) $(CFLAGS) -o "$(DISPATCHCTLD)" $(wildcard $(DISPATCHCTLD_SRC)/*.o) $(LIBZMQ_STATIC)

dispatchd: dispatchd_objs
	$(CC) $(CFLAGS) -o "$(DISPATCHD)" $(wildcard $(DISPATCHD_SRC)/*.o) $(LIBZMQ_STATIC)

dispatchctld_objs:
	$(MAKE) -C $(DISPATCHCTLD_SRC)


dispatchd_objs:
	$(MAKE) -C $(DISPATCHD_SRC)

clean:
	find -name *.o -delete
	rm -rf $(STATIC_LIB_DIR)
	rm $(DISPATCHCTLD)
	rm $(DISPATCHD)
