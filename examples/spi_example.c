#include "../tinkerboard_io.h"

int main(int argc, const char *argv[]) {

  if (tinkerboard_init() == 1) {
    printf("Successfully initialized\n");

    uint8_t tx_buff[] = {0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF,
                         0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF,
                         0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF,
                         0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF,
                         0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF,
                         0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF};
    uint8_t rx_buff[48] = {};

    struct spi_mode_config_t mode = {
        .clk_mode = 1,
        .clk_divider = 8,
        .data_frame_size = DFS_8,
        .slave_select = 0,
        .transfer_mode = TRANSMIT_RECEIVE,
        .byte_order = MSB_FIRST,
    };

    uint64_t error = 0;
    tinkerboard_spi_init(SPI2, mode);
    tinkerboard_set_gpio_mode(26, OUTPUT);
    tinkerboard_set_gpio_state(26, HIGH);


    for (int j = 0; j < 1000; j++) {
      tinkerboard_set_gpio_state(26, LOW);
      tinkerboard_spi_transfer(SPI2, tx_buff, rx_buff, 48, mode);
      tinkerboard_set_gpio_state(26, HIGH);
      for (int i = 0; i < 48; i++) {
        if (rx_buff[i] != tx_buff[i]) {
          printf("%02X is not %02X\n", rx_buff[i], tx_buff[i]);
          error++;
        }
      }
    }

    if (error) {
      printf("Transfer failed with %llu errors", error);
    } else {
      printf("Transfer successful\n");
    }


    tinkerboard_spi_end(SPI2);
    tinkerboard_end();

  }
}
