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

#include "defines.h"

uint32_t *_rk3288_gpio_block_base = (uint32_t *)RK3288_GPIO_BLOCK_BASE;
uint32_t *_rk3288_gpio_grf_base = (uint32_t *)MAP_FAILED;
uint32_t *_rk3288_gpio_0_base = (uint32_t *)MAP_FAILED;
uint32_t *_rk3288_gpio_5_base = (uint32_t *)MAP_FAILED;
uint32_t *_rk3288_gpio_6_base = (uint32_t *)MAP_FAILED;
uint32_t *_rk3288_gpio_7_base = (uint32_t *)MAP_FAILED;
uint32_t *_rk3288_gpio_8_base = (uint32_t *)MAP_FAILED;
uint32_t _rk3288_gpio_block_size = RK3288_GPIO_BLOCK_SIZE;

uint32_t *_rk3288_spi0_base = (uint32_t *)MAP_FAILED;
uint32_t *_rk3288_spi1_base = (uint32_t *)MAP_FAILED;
uint32_t *_rk3288_spi2_base = (uint32_t *)MAP_FAILED;
uint32_t _rk3288_spi_block_size = RK3288_GPIO_BLOCK_SIZE;

uint32_t *_rk3288_rk_pwm_base = (uint32_t *)MAP_FAILED;
uint32_t *_rk3288_dw_pwm_base = (uint32_t *)MAP_FAILED;
uint32_t _rk3288_pmw_block_size = RK3288_GPIO_BLOCK_SIZE;

uint32_t *_rk3288_i2c1_base = (uint32_t *)MAP_FAILED;
uint32_t *_rk3288_i2c4_base = (uint32_t *)MAP_FAILED;

struct gpio_pin_t _gpio_pins[] = {
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},

	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},

	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},

	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},

	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .is_gpio = 1, .mode = INPUT}
};

void _write_mem(volatile uint32_t* mem_addr, uint32_t value){
	//printf("Wrote %08X at %08X\n", value, (unsigned) mem_addr);
	__sync_synchronize();
	*mem_addr = value;
	__sync_synchronize();
}

uint32_t _read_mem(volatile uint32_t* mem_addr){
	uint32_t ret = 0;
	__sync_synchronize();
	ret = *mem_addr;
	__sync_synchronize();
	//printf("Read %08X at %08X\n", ret, (unsigned) mem_addr);
	return ret;
}

uint32_t _set_bit(uint32_t value, uint8_t bit) {
	value |= 1 << bit;
	return value;
}

uint32_t _clear_bit(uint32_t value, uint8_t bit) {
	value &= ~(1 << bit);
	return value;
}

void tinkerboard_set_gpio_mode(uint8_t pin_number, enum IOMode mode) {
	if(VALID_GPIO(pin_number) && _gpio_pins[pin_number-1].is_gpio) {

	}
}

void tinkerboard_set_gpio_state(uint8_t pin_number, enum IOState state) {
	if(VALID_GPIO(pin_number) && _gpio_pins[pin_number-1].is_gpio && _gpio_pins[GPIO_NUMBER_TO_INDEX(pin_number)].mode == OUTPUT) {

	}
}

enum IOState tinkerboard_get_gpio_state(uint8_t pin_number) {
	if(VALID_GPIO(pin_number) && _gpio_pins[pin_number-1].is_gpio && _gpio_pins[GPIO_NUMBER_TO_INDEX(pin_number)].mode == INPUT) {

	}
	return INPUT;
}

int tinkerboard_init(void){
	int memfd;
	int retcode;

	memfd = -1;
	retcode = 0;

	if((memfd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) {
		printf("Couldn't open /dev/mem: %s", strerror(errno));
		goto end;
	}

	_rk3288_gpio_block_base = mmap(NULL, _rk3288_gpio_block_size, (PROT_READ | PROT_WRITE), MAP_SHARED, memfd, RK3288_GPIO_BLOCK_BASE);
	if(_rk3288_gpio_block_base == MAP_FAILED){
		printf("Error while mapping gpio block into virtual memory");
	}

	_rk3288_gpio_grf_base = _rk3288_gpio_block_base + ALIGN_TO_UINT32T(RK3288_GPIO_GRF_OFFSET);
	_rk3288_gpio_0_base = _rk3288_gpio_block_base + ALIGN_TO_UINT32T(RK3288_GPIO0_OFFSET);
	_rk3288_gpio_5_base = _rk3288_gpio_block_base + ALIGN_TO_UINT32T(RK3288_GPIO5_OFFSET);
	_rk3288_gpio_6_base = _rk3288_gpio_block_base + ALIGN_TO_UINT32T(RK3288_GPIO6_OFFSET);
	_rk3288_gpio_7_base = _rk3288_gpio_block_base + ALIGN_TO_UINT32T(RK3288_GPIO7_OFFSET);
	_rk3288_gpio_8_base = _rk3288_gpio_block_base + ALIGN_TO_UINT32T(RK3288_GPIO8_OFFSET);

	retcode = 1;

end:
	if(memfd >= 0) {
		close(memfd);
	}
	return retcode;
}

void tinkerboard_end(void) {

	if(_rk3288_gpio_block_base == MAP_FAILED) {
		return;
	}

	munmap((void**)_rk3288_gpio_block_base, _rk3288_gpio_block_size);
	_rk3288_gpio_block_base = MAP_FAILED;
	_rk3288_gpio_grf_base = MAP_FAILED;
	_rk3288_gpio_0_base = MAP_FAILED;
	_rk3288_gpio_5_base = MAP_FAILED;
	_rk3288_gpio_6_base = MAP_FAILED;
	_rk3288_gpio_7_base = MAP_FAILED;
	_rk3288_gpio_8_base = MAP_FAILED;

	return;
}

int main(int argc, const char * argv[]){
/*printf("%d", VALID_GPIO(0));
printf("%d", VALID_GPIO(3));
printf("%d", VALID_GPIO(41));
printf("%d", VALID_GPIO(GPIO_NUMBER_TO_INDEX(41)));
printf("%d", ALIGN_TO_UINT32T(16));*/
	if(tinkerboard_init() == 1){
		printf("Successfully initialized\n");

		_write_mem(_rk3288_gpio_grf_base + 0x0054 / 4, (uint32_t) 0x02000000);
		_read_mem(_rk3288_gpio_grf_base + 0x0054 / 4);
		_write_mem(_rk3288_gpio_5_base + 0x0001, (uint32_t) 1<<19);
		_write_mem(_rk3288_gpio_0_base + 0x0001, (uint32_t) 1<<17);
		_read_mem(_rk3288_gpio_5_base + 0x0001);
		printf("GPIO init\n");

		_write_mem(_rk3288_gpio_0_base, (uint32_t) 1<<17);
		_write_mem(_rk3288_gpio_5_base, (uint32_t) 1<<19);
		_write_mem(_rk3288_gpio_0_base, (uint32_t) 0);
		_write_mem(_rk3288_gpio_5_base, (uint32_t) 0);
	}

	tinkerboard_end();
}
