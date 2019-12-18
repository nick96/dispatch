#define WIN32_LEAN_AND_MEAN

#if defined(WIN32) || defined(_WIN32)
#include <windows.h>
#include <direct.h>
#else
#include <error.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <msgpack.h>
#include <zmq.h>

#include "constants.h"
#include "sig_handler.h"

const char *IPC_PATH_DEFAULT = "/tmp/dispatch/0";
const char *LOG_FILE_DEFAULT = "stderr";
const char *PID_FILE_DEFAULT = "/var/run/dispatch/dispatch.pid";

struct Args {
    int help;
};

void info(void);
int setup_signal_handlers(void);
int listen_for_cmds(void);
int ensure_fifo_exists(char *path);
void parent_path(char *path, char **parent);

int main(int argc, char *argv[]) {
    char *app_name = argv[0];
    struct Args args = (struct Args){
        .help = 0,
    };
    static struct option long_opts[] = {{"help", no_argument, 0, 'h'},
                                        {0, 0, 0, 0}};
    int value, option_index = 0;
    while ((value = getopt_long(argc, argv, "c::h", long_opts,
                                &option_index)) != -1) {
        switch (value) {
        case 'h':
            info();
            return EXIT_FAILURE;
        default:
            fprintf(stderr, "Unknown argument %s, ignoring\n", optarg);
        }
    }

    if (setup_signal_handlers() != 0) {
        fprintf(stderr, "Could not register signal handlers\n");
        return EXIT_FAILURE;
    }

    listen_for_cmds();
}

void info() {
    puts("dispatchctld - Daemon for the controller node");

    int major, minor, patch;
    zmq_version(&major, &minor, &patch);
    printf("zmq: v%d.%d.%d\n", major, minor, patch);
    printf("msgpack: v%s\n", MSGPACK_VERSION);
}

int listen_for_cmds() {
    void *ctx = zmq_ctx_new();
    void *resp_socket = zmq_socket(ctx, ZMQ_REP);

    if (ensure_fifo_exists(CTL_ENDPOINT) != 0) {
        fprintf(stderr, "Could not create fifo at %s: %s\n", CTL_ENDPOINT,
                strerror(errno));
        return 1;
    }

    if (zmq_bind(resp_socket, CTL_URI) != 0) {
        fprintf(stderr, "Could not bind to controller endpoint %s: %s\n",
                CTL_ENDPOINT, strerror(errno));
        return 1;
    }

    char buf[2048];
    char *resp_msg = "response from controller daemon";
    while (true) {
        zmq_recv(resp_socket, buf, 2048, 0);
        printf("Received: %s\n", buf);
        zmq_send(resp_socket, resp_msg, strlen(resp_msg), 0);
    }
    return 0;
}

int ensure_fifo_exists(char *path) {
    char *parent;
    parent_path(path, &parent);
    if (access(parent, F_OK) == -1) {
        if (mkdir(parent, 0666)) {
            fprintf(stderr, "Could not create directory %s\n", parent);
            return -1;
        }
    }
    return mkfifo(path, 0666);
}

void parent_path(char *path, char **parent) {
    char *slash = path, *next;
    while ((next = strpbrk(slash + 1, "\\/"))) {
        slash = next;
    }
    if (path != slash) {
        slash++;
    }
    *parent = strndup(path, slash - path);
}
