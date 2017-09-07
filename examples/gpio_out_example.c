#include "../tinkerboard_io.h"
#include <signal.h>

void sigint_handler(int signo) {
  if (signo == SIGINT) {
    printf("Closing Tinker Board\n");
    tinkerboard_end();
  }
}

int main(int argc, const char *argv[]) {

  if (tinkerboard_init() == 1) {
    printf("Successfully initialized\n");

    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
      printf("can't catch SIGINT\n");
    }

    for (uint32_t idx = 1; idx <= 40; idx++) {
      tinkerboard_set_gpio_mode(idx, OUTPUT);
    }


    while (1) {
      for (uint32_t idx = 1; idx <= 40; idx++) {
        tinkerboard_set_gpio_state(idx, HIGH);
      }

      for (uint32_t idx = 1; idx <= 40; idx++) {
        tinkerboard_set_gpio_state(idx, LOW);
      }
    }
  }
}
