#include <assert.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <zmq.h>
#include <msgpack.h>

const char *IPC_PATH_DEFAULT = "/tmp/dispatch/0";
const char *LOG_FILE_DEFAULT = "stderr";
const char *PID_FILE_DEFAULT = "/var/run/dispatch/dispatch.pid";

struct Args {
    char *conf_file;
    int help;
};

void info(void);
int setup_signal_handlers(void);

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
        case 'c':
            args.conf_file = strdup(optarg);
            break;
        }

    }

    if (setup_signal_handlers()) {
      return EXIT_FAILURE;
    }
}

void info() {
    puts("dispatchctld - Daemon for the controller node");

    int major, minor, patch;
    zmq_version(&major, &minor, &patch);
    printf("zmq: v%d.%d.%d\n", major, minor, patch);
    printf("msgpack: v%s\n", MSGPACK_VERSION);
}

static void handle_SIGTERM(int signo) {
  // TODO: Implement graceful shutoown as necessary
  (void)signo;
  exit(EXIT_FAILURE);
}


static void handle_SIGHUP(int signo) {
   // TODO: Implement graceful shutoown as necessary
  (void)signo;
}

int setup_signal_handlers() {
  if (signal(SIGTERM, handle_SIGTERM) == SIG_ERR) {
    return 1;
  }

  if (signal(SIGHUP, handle_SIGHUP) == SIG_ERR) {
    return 1;
  }

  return 0;
}
