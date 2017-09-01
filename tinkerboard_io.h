#ifndef TINKERBOARD_IO_H
#define TINKERBOARD_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include "tinkerboard_spi.h"


#define ALIGN(x)  ((x) / 4)
#define TO_INDEX(x)  ((x)-1)
#define VALID_GPIO(x)  ((x)>0 && (x)<=40 ? 1 : 0)

#define RK3288_GPIO_BLOCK_BASE    0xFF750000
#define RK3288_GPIO_BLOCK_SIZE    0xB0000

#define RK3288_GPIO_GRF_OFFSET	  0x20000
#define RK3288_GPIO0_OFFSET       0x00000
#define RK3288_GPIO5_OFFSET       0x70000
#define RK3288_GPIO6_OFFSET       0x80000
#define RK3288_GPIO7_OFFSET       0x90000
#define RK3288_GPIO8_OFFSET       0xA0000

#define RK3288_GPIO5B_GRF_OFFSET  0x20050
#define RK3288_GPIO5C_GRF_OFFSET  0x20054

#define RK3288_GPIO6A_GRF_OFFSET  0x2005C

#define RK3288_GPIO7A_GRF_OFFSET  0x2006C
#define RK3288_GPIO7B_GRF_OFFSET  0x20070
#define RK3288_GPIO7CL_GRF_OFFSET 0x20074
#define RK3288_GPIO7CH_GRF_OFFSET 0x20078

#define RK3288_GPIO8A_GRF_OFFSET  0x20080
#define RK3288_GPIO8B_GRF_OFFSET  0x20084

#define RK3288_SPI_BLOCK_BASE     0xFF110000
#define RK3288_SPI0_BLOCK_OFFSET  0x00000
#define RK3288_SPI1_BLOCK_OFFSET  0x10000
#define RK3288_SPI2_BLOCK_OFFSET  0x20000
#define RK3288_SPI_BLOCK_SIZE     0x30000


#define RK3288_I2C1_BLOCK_BASE    0xFF140000
#define RK3288_I2C4_BLOCK_BASE    0xFF160000
#define RK3288_I2C_BLOCK_SIZE     0x10000

#define RK3288_PWM_BLOCK_SIZE     0x10000

#define RK3288_CONFIG_WRITEMASK_OFFSET 16

#define RK3288_CRU_BLOCK_BASE	  0xFF760000
#define RK3288_CRU_BLOCK_SIZE	  0x10000

#define RK3288_CRU_SOFTRST_OFFSET 0x01CC
#define RK3288_CRU_CLKSEL39_OFFSET 0x00FC
#define RK3288_CRU_CLKSEL25_OFFSET 0x00C4
#define RK3288_CRU_CLKGATE2_OFFSET 0x0168
#define RK3288_CRU_CLKGATE6_OFFSET 0x0178

enum IOState {HIGH = 0x1, LOW = 0x0};
enum IOMode {INPUT = 0x0, OUTPUT = 0x1, SPI = 0x2, I2C = 0x3, PWM = 0x4};
enum SPIController {SPI0 = 0x0, SPI2 = 0x1};
enum SPISlaveSelect {SS_NONE = 0x1, SS0 = 0x2, SS1 = 0x3};
enum SPIDataFrameSize {DFS_4 = 0x0, DFS_8 = 0x1, DFS_16 = 0x2};
enum SPIByteTransform {BT_16_8 = 0x0, BT_8_8 = 0x1};
enum SPITransferMode {TRANSMIT_RECEIVE = 0x0, TRANSMIT = 0x1, RECEIVE = 0x2};
enum SPIByteOrder {MSB_FIRST = 0x0, LSB_FIRST = 0x1};


struct gpio_pin_t {
  uint32_t gpio_bank_offset;
  uint32_t gpio_control_offset;
  uint32_t grf_bank_offset;
  uint32_t grf_pin_offset;
  uint32_t grf_config_size;
  enum IOMode mode;
  uint32_t is_gpio;
};

struct spi_pin_config_t {
  uint32_t clk;
  uint32_t txd;
  uint32_t rxd;
  uint32_t cs0;
  uint32_t cs1;
  uint32_t spi_block_offset;
  uint32_t pll_sel_offset;
  uint32_t clk_src_offset;
  uint32_t clk_gate_flag;
  uint32_t pclk_src_offset;
  uint32_t pclk_gate_flag;
  uint32_t softrst_offset;
  uint32_t softrst_flag;
  uint32_t initialized;
};

struct spi_mode_config_t {
  uint32_t clk_divider;
  uint32_t clk_mode;
  enum SPIDataFrameSize data_frame_size;
  enum SPISlaveSelect slave_select;
  enum SPITransferMode transfer_mode;
  enum SPIByteOrder  byte_order;
};

struct i2c_config_t {
  struct gpio_pin_t scl;
  struct gpio_pin_t sda;
};

struct pwm_config_t {
  struct gpio_pin_t pin;
};

uint32_t tinkerboard_get_gpio_mode(uint32_t pin_number);

void tinkerboard_set_gpio_mode(uint32_t pin_number, enum IOMode mode);

void tinkerboard_set_gpio_state(uint32_t pin_number, enum IOState state);

enum IOState tinkerboard_get_gpio_state(uint32_t pin_number);

void tinkerboard_reset_header(void);

int tinkerboard_init(void);

void tinkerboard_end(void);

void tinkerboard_spi_init(enum SPIController controller, struct spi_mode_config_t mode_config);

void tinkerboard_spi_end(enum SPIController controller);

void tinkerboard_spi_transfer(enum SPIController controller, uint8_t* tx_buff, uint8_t* rx_buff, uint32_t length, struct spi_mode_config_t mode_config);


#endif
