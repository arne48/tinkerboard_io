#include "../tinkerboard_io.h"
#include <curses.h>

int main(int argc, const char *argv[]) {

  if (tinkerboard_init() == 1) {
    initscr();
    timeout(0);
    move(0, 0);
    printw("Successfully initialized");


    for (uint32_t idx = 1; idx <= 40; idx++) {
      tinkerboard_set_gpio_mode(idx, OUTPUT);
    }

    move(4, 0);
    printw("All outputs are toggling now, please check.");
    move(5, 0);
    printw("To stop press any key....");

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
    endwin();
  }
}
