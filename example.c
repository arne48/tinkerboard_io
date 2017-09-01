#include "tinkerboard_io.h"

int main(int argc, const char *argv[]) {

  if (tinkerboard_init() == 1) {
    printf("Successfully initialized\n");


    for (uint32_t idx = 1; idx <= 40; idx++) {
      tinkerboard_set_gpio_mode(idx, OUTPUT);
    }



    /*while(1) {
        for (uint32_t idx = 1; idx <= 40; idx++) {
    tinkerboard_set_gpio_state(idx, HIGH);
        }

        for (uint32_t idx = 1; idx <= 40; idx++) {
    tinkerboard_set_gpio_state(idx, LOW);
        }
      }*/


    uint8_t tx_buff[] = {0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF,
                         0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF,
                         0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF,
                         0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF,
                         0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF,
                         0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF, 0xBE, 0XEF};
    uint8_t rx_buff[48];

    struct spi_mode_config_t mode = {
        .clk_mode = 1,
        .clk_divider = 2,
        .data_frame_size = DFS_8,
        .slave_select = SS0,
        .transfer_mode = TRANSMIT,
        .byte_order = MSB_FIRST,
    };

    tinkerboard_spi_init(SPI2, mode);
    tinkerboard_spi_transfer(SPI2, tx_buff, rx_buff, 48, mode);
    tinkerboard_spi_end(SPI2);

    uint8_t error = 0;
    for(int i=0; i < 48; i++) {
      if(rx_buff[i] != tx_buff[i]){
        printf("%08X is not %08X", rx_buff[i], tx_buff[i]);
        error++;
      }
    }

    if(error) {
      printf("Transfer failed with %d errors", error);
    }

    tinkerboard_end();

  }
}
