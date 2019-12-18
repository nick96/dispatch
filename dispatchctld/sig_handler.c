#include <signal.h>
#include <stdlib.h>

#include "log.h"
#include "sig_handler.h"

static void handle_SIGTERM(int signo) {
    // TODO: Implement graceful shutoown as necessary
    LOG("Received SIGTERM signal (%d), exiting now", signo);
    exit(EXIT_FAILURE);
}

int setup_signal_handlers() {
    if (signal(SIGTERM, handle_SIGTERM) == SIG_ERR) {
        return 1;
    }

    return 0;
}
