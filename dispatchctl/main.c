#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <zmq.h>

#include "constants.h"

int main(int argc, char *argv[]) {
    char *msg = "default msg";
    if (argc > 1) {
        msg = argv[1];
    }

    void *ctx = zmq_ctx_new();
    void *socket = zmq_socket(ctx, ZMQ_REQ);
    if (zmq_bind(socket, CTL_ENDPOINT) != 0) {
      return EXIT_FAILURE;
    }

    char buf[2048];
    zmq_send(socket, msg, strlen(msg), 0);
    zmq_recv(socket, buf, 2048, 0);
    printf("Received: %s", buf);
    return 0;
}
