#include "../tinkerboard_io.h"
#include <curses.h>

int main(int argc, const char *argv[]) {

  if (tinkerboard_init() == 1) {
    initscr();
    timeout(0);
    printf("Successfully initialized\n");

    // Not really needed as the initialization is setting all gpios as input
    // but not all gpios are using pullups initially
    for (uint32_t idx = 1; idx <= 40; idx++) {
      tinkerboard_set_gpio_mode(idx, INPUT);
      tinkerboard_set_gpio_pud(idx, PULLUP);
    }

    enum IOState last_states[40] = {[0 ... 39] = HIGH};
    printf("Please bridge Pin 9 (GND) to any gpio to check input function\n");
    printf("To stop press any key....\n");

    int input = ERR;
    while (input == ERR) {
      for (uint32_t idx = 1; idx <= 40; idx++) {

        input = getch();

        enum IOState current_state = tinkerboard_get_gpio_state(idx);
        if (current_state != last_states[idx - 1] && NO_POWER_PIN(idx)) {
          last_states[idx - 1] = current_state;
          printf("Pin %d toggled its state\n", idx);
        }
      }
    }

    tinkerboard_end();
  }
}
