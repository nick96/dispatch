#include <signal.h>
#include <stdlib.h>

#include "sig_handler.h"

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

    return 0;
}
