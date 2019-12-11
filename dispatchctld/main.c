#include <czmq.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    int major, minor, patch;
    zmq_version(&major, &minor, &patch);
    printf("Using version %d.%d.%d of zmq\n", major, minor, patch);
}
