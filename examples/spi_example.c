#include "../tinkerboard_io.h"

int main(int argc, const char *argv[]) {

  if (tinkerboard_init() == 1) {
    printf("Successfully initialized\n");

    uint8_t tx_buff[] = {0xBE, 0XEF, 0xBE, 0XEF, 0x00, 0XEF, 0xBE, 0XFF,
                         0xBE, 0XEF, 0xBE, 0XEF, 0x00, 0XEF, 0xFF, 0XEF,
                         0xBE, 0XEF, 0xBE, 0XEF, 0x00, 0XFF, 0xBE, 0XEF,
                         0x11, 0X11, 0x11, 0X11, 0xFF, 0X11, 0x11, 0X11,
                         0xBE, 0XEF, 0xBE, 0XFF, 0x00, 0XEF, 0xBE, 0XEF,
                         0xBE, 0XEF, 0xFF, 0XEF, 0x00, 0XEF, 0xBE, 0XEF,
                         0xBE, 0XFF, 0xBE, 0XEF, 0x00, 0XEF, 0xBE, 0XEF,
                         0xFF, 0XEF, 0xBE, 0XEF, 0x00, 0XEF, 0xBE, 0XEF
    };

    uint8_t rx_buff[64] = {};

    /*
     * The slave select of the spi is not bound to
     * specific pins. Any pin as long as it is a valid
     * gpio and not part of the spi controller can be used.
     * If no slave select is needed the define "NO_SS" will
     * set non.
     */
    struct spi_mode_config_t mode = {
        .clk_mode = 1,
        .clk_divider = 8,
        .data_frame_size = DFS_8,
        .slave_select = NO_SS,
        .transfer_mode = TRANSMIT_RECEIVE,
        .byte_order = MSB_FIRST,
    };

    unsigned long error = 0;
    tinkerboard_spi_init(SPI2, mode);
    tinkerboard_set_gpio_mode(26, OUTPUT);
    tinkerboard_set_gpio_state(26, HIGH);


    for (unsigned int j = 0; j < 1000; j++) {
      tinkerboard_set_gpio_state(26, LOW);
      tinkerboard_spi_transfer(SPI2, tx_buff, rx_buff, 64, mode);
      tinkerboard_set_gpio_state(26, HIGH);
      for (unsigned int i = 0; i < 64; i++) {
        if (rx_buff[i] != tx_buff[i]) {
          printf("%02X is not %02X\n", rx_buff[i], tx_buff[i]);
          error++;
        }
      }
    }

    if (error) {
      printf("Transfer failed with %lu errors\n", error);
    } else {
      printf("Transfer successful\n");
    }


    tinkerboard_spi_end(SPI2);
    tinkerboard_end();

  }
}
