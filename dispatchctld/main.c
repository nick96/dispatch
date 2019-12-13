#include <assert.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <zmq.h>
#include <msgpack.h>

const char *IPC_PATH_DEFAULT = "/tmp/dispatch/0";
const char *LOG_FILE_DEFAULT = "stderr";
const char *PID_FILE_DEFAULT = "/var/run/dispatch/dispatch.pid";

struct Args {
    char *conf_file;
    int daemon;
    int help;
    char *ipc_path;
    char *log_file;
    char *pid_file;
};

void info(void);

int main(int argc, char *argv[]) {
    char *app_name = argv[0];
    struct Args args = (struct Args){
                              .conf_file = NULL,
                              .daemon = 0,
                              .help = 0,
                              .ipc_path = "/tmp/dispatch/0",
                              .log_file = "stderr",
                              .pid_file = "/var/run/dispatch/dispatch.pid",
    };
    static struct option long_opts[] = {
        {"conf-file", optional_argument, 0, 'c'},
        {"daemon", no_argument, 0, 'd'},
        {"help", no_argument, 0, 'h'},
        {"ipc-path", optional_argument, 0, 'i'},
        {"log-file", optional_argument, 0, 'l'},
        {"pid-file", optional_argument, 0, 'p'},
        {0, 0, 0, 0}
    };
    int value, option_index = 0;
    while ((value = getopt_long(argc, argv, "c::dhi::l::p::", long_opts,
                                &option_index)) != -1) {
        switch (value) {
        case 'h':
            info();
            return EXIT_FAILURE;
        case 'c':
            args.conf_file = strdup(optarg);
            break;
        case 'd':
            args.daemon = true;
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
        }
    }

    puts("Settings");
    printf("config file: %s\n", args.conf_file);
    printf("daemon: %s", args.daemon ? "yes" : "no");
    printf("ipc path: %s\n", args.ipc_path);
    printf("log file: %s\n", args.log_file);
    printf("pid file: %s\n", args.pid_file);
}

void info() {
    puts("dispatchctld - Daemon for the controller node");

    int major, minor, patch;
    zmq_version(&major, &minor, &patch);
    printf("zmq: v%d.%d.%d\n", major, minor, patch);
    printf("msgpack: v%s\n", MSGPACK_VERSION);
}
