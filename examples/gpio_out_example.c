#include "../tinkerboard_io.h"
#include <curses.h>

int main(int argc, const char *argv[]) {

  if (tinkerboard_init() == 1) {
    initscr();
    timeout(0);
    printf("Successfully initialized\n");


    for (uint32_t idx = 1; idx <= 40; idx++) {
      tinkerboard_set_gpio_mode(idx, OUTPUT);
    }

    printf("All outputs are toggling now, please check.\n");
    printf("To stop press any key....\n");

    int input = ERR;
    while (input == ERR) {
      input = getch();

      for (uint32_t idx = 1; idx <= 40; idx++) {
        tinkerboard_set_gpio_state(idx, HIGH);
      }

      for (uint32_t idx = 1; idx <= 40; idx++) {
        tinkerboard_set_gpio_state(idx, LOW);
      }
    }

    tinkerboard_end();
  }
}
