#include "../tinkerboard_io.h"

int main(int argc, const char *argv[]) {

  if (tinkerboard_init() == 1) {
    printf("Successfully initialized\n");


    for (uint32_t idx = 1; idx <= 40; idx++) {
      tinkerboard_set_gpio_mode(idx, OUTPUT);
    }


    for (uint64_t i = 0; i < 10000; i++) {
      for (uint32_t idx = 1; idx <= 40; idx++) {
        tinkerboard_set_gpio_state(idx, HIGH);
      }

      for (uint32_t idx = 1; idx <= 40; idx++) {
        tinkerboard_set_gpio_state(idx, LOW);
      }
    }

    printf("All gpios were toggled 10000 times\n");

    tinkerboard_end();

  }
}
