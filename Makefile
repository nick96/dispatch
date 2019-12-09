BIN=bin
DISPATCHCTLD=$(BIN)/dispatchctld
DISPATCHD=$(BIN)/dispatchd
DISPATCHCTLD_SRC=$(PWD)/dispatchctld
DISPATCHD_SRC=$(PWD)/dispatchd

all: dispatchd dispatchctld

dispatchctld: dispatchctld_objs
	$(CC) $(CFLAGS) -o "$(DISPATCHCTLD)" $(wildcard $(DISPATCHCTLD_SRC)/*.o) -lzmq -lczmq

dispatchd: dispatchd_objs
	$(CC) $(CFLAGS) -o "$(DISPATCHD)" $(wildcard $(DISPATCHD_SRC)/*.o) -lzmq -lczmq

dispatchctld_objs:
	$(MAKE) -C $(DISPATCHCTLD_SRC)

dispatchd_objs:
	$(MAKE) -C $(DISPATCHD_SRC)

clean:
	find -name *.o -delete
	rm $(DISPATCHCTLD)
	rm $(DISPATCHD)
