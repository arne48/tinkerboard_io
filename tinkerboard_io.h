#ifndef DEFINES_H
#define DEFINES_H

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


#define ALIGN_TO_UINT32T(x)  (x / 4)
#define GPIO_NUMBER_TO_INDEX(x)  (x-1)
#define VALID_GPIO(x)  ((x)>0 && (x)<=40 ? 1 : 0)

#define RK3288_GPIO_BLOCK_BASE    0xFF750000
#define RK3288_GPIO_BLOCK_SIZE    0xB0000

#define RK3288_SPI_BLOCK_SIZE     0x30000
#define RK3288_I2C_BLOCK_SIZE     0x40000
#define RK3288_PWM_BLOCK_SIZE     0x10000

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

#define RK3288_GRF_WRITEMASK_OFFSET 16

enum IOState {HIGH = 0x1, LOW = 0x0};
enum IOMode {INPUT = 0x0, OUTPUT = 0x1, SPI = 0x2, I2C = 0x3, PWM = 0x4};

struct gpio_pin_t {
  uint32_t gpio_bank_offset;
  uint32_t gpio_control_offset;
  uint32_t grf_bank_offset;
  uint32_t grf_pin_offset;
  uint32_t grf_config_size;
  enum IOMode mode;
  uint32_t is_gpio;
};

struct spi_config_t {
  struct gpio_pin_t clk;
  struct gpio_pin_t txd;
  struct gpio_pin_t rxd;
  struct gpio_pin_t cs0;
  struct gpio_pin_t cs1;
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


#endif
