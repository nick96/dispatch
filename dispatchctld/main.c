#define WIN32_LEAN_AND_MEAN

#include <assert.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <zmq.h>
#include <msgpack.h>

#include "sig_handler.h"

#if defined(_WIN32) || defined(WIN32)
#define WINDOWS_OS
#endif

const char *IPC_PATH_DEFAULT = "/tmp/dispatch/0";
const char *LOG_FILE_DEFAULT = "stderr";
const char *PID_FILE_DEFAULT = "/var/run/dispatch/dispatch.pid";

struct Args {
    char *conf_file;
    int help;
};

void info(void);
int setup_signal_handlers(void);
int listen_for_cmds(void);

int main(int argc, char *argv[]) {
    char *app_name = argv[0];
    struct Args args = (struct Args){
                              .conf_file = NULL,
                              .help = 0,
    };
    static struct option long_opts[] = {
        {"conf-file", optional_argument, 0, 'c'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };
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
  return 0;
}
