#ifndef DEFINES_H
#define DEFINES_H

#define ALIGN_TO_UINT32T(x)  (x / 4)
#define GPIO_NUMBER_TO_INDEX(x)  (x-1)
#define VALID_GPIO(x)  ((x)>0 && (x)<=40 ? 1 : 0)

#define RK3288_GPIO_GRF_BASE      0xFF770000
#define RK3288_GPIO5_OFFSET       0x50000
#define RK3288_GPIO6_OFFSET       0x60000
#define RK3288_GPIO7_OFFSET       0x70000
#define RK3288_GPIO8_OFFSET       0x80000
#define RK3288_GPIO_BLOCK_SIZE    0x90000

#define RK3288_GPIO5B_GRF_OFFSET  0x0050
#define RK3288_GPIO5C_GRF_OFFSET  0x0054

#define RK3288_GPIO6A_GRF_OFFSET  0x005C

#define RK3288_GPIO7A_GRF_OFFSET  0x006C
#define RK3288_GPIO7B_GRF_OFFSET  0x0070
#define RK3288_GPIO7CL_GRF_OFFSET 0x0074
#define RK3288_GPIO7CH_GRF_OFFSET 0x0078

#define RK3288_GPIO8A_GRF_OFFSET  0x0080
#define RK3288_GPIOBB_GRF_OFFSET  0x0084

enum IOState {HIGH = 0x1, LOW = 0x0};
enum IOMode {INPUT = 0x0, OUTPUT = 0x1, SPI = 0x2, I2C = 0x3, PWM = 0x4};

struct gpio_pin_t {
  uint8_t gpio_bank_offset;
  uint8_t gpio_control_offset;
  uint32_t grf_bank_offset;
  uint32_t grf_pin_offset;
  enum IOMode mode;
  uint8_t is_gpio;
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


#endif
