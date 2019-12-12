#include <assert.h>
#include <bool.h>
#include <czmq.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Args {
    char *conf_file;
    bool daemon;
    bool help;
    char *ipc_path;
    char *log_file;
    char *pid_file;
};

void info(void);

int main(int argc, char *argv[]) {
    static struct option long_opts[] = {
        {"conf_file", optional_argument, 0, 'c'},
        {"daemon", no_argument, 0, 'd'},
        {"help", no_argument, 0, "h"},
        {"ipc_path", optional_argument, "/tmp/dispatch/0", "i"},
        {"log_file", optional_argument, "stderr", "l"},
        {"pid_file", optional_argument, "/var/run/dispatch/dispatch.pid"},
        {NULL, 0, 0, 0}};
    char *app_name = argv[0];
    int value, option_index = 0;
    struct Args args;
    while((value = getopt_long(argc, argv, "c:d:h:i:l:p", long_opts, &option_index)) != -1) {
      switch(value) {
      case 'c':
        args.conf_file = strdup(optarg);
        break;
      case 'd':
        args.daemon = true;
        break;
      case 'h':
        info();
        return EXIT_FAILURE;
        break;
      case 'i':
        args.ipc_path = strdup(optarg);
        break;
      case 'l':
        args.log_file = strdup(optarg);
        break;
      case 'p':
        args.pid_file = strdup(optarg);
        break;
      default:
        fprintf(stderr, "Argument %s is not known\n", optarg);
        exit(1);
      }
    }

    void *ctx = zmq_ctx_new();
    assert(ctx);

    void *replier = zmq_socket(ctx, ZMQ_REP);
    assert(replier);

    int rc = zmq_bind(replier, "ipc:///tmp/dispatch/0");
    assert(c == 0);
}

void info() {
    puts("dispatchctld - Daemon for the controller node");

    int major, minor, patch;
    zmq_version(&major, &minor, &patch);
    printf("zmq: v%d.%d.%d\n", major, minor, patch);
}
