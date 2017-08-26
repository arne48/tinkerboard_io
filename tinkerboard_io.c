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
uint32_t _rk3288_spi_block_size = RK3288_SPI_BLOCK_SIZE;

uint32_t *_rk3288_rk_pwm_base = (uint32_t *)MAP_FAILED;
uint32_t *_rk3288_dw_pwm_base = (uint32_t *)MAP_FAILED;
uint32_t _rk3288_pmw_block_size = RK3288_PWM_BLOCK_SIZE;

uint32_t *_rk3288_i2c1_base = (uint32_t *)MAP_FAILED;
uint32_t *_rk3288_i2c4_base = (uint32_t *)MAP_FAILED;
uint32_t _rk3288_i2c_block_size = RK3288_PWM_BLOCK_SIZE;

struct gpio_pin_t _gpio_header_pins[] = {
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .grf_config_size = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .grf_config_size = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO8_OFFSET, .gpio_control_offset =  4, .grf_bank_offset = RK3288_GPIO8A_GRF_OFFSET, .grf_pin_offset =  8, .grf_config_size = 2, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .grf_config_size = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO8_OFFSET, .gpio_control_offset =  5, .grf_bank_offset = RK3288_GPIO8A_GRF_OFFSET, .grf_pin_offset = 10, .grf_config_size = 2, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .grf_config_size = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO0_OFFSET, .gpio_control_offset = 17, .grf_bank_offset = 0, .grf_pin_offset = 0, .grf_config_size = 0, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO5_OFFSET, .gpio_control_offset =  9, .grf_bank_offset = RK3288_GPIO5B_GRF_OFFSET, .grf_pin_offset =  2, .grf_config_size = 2, .is_gpio = 1, .mode = INPUT},

	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .grf_config_size = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO5_OFFSET, .gpio_control_offset =  8, .grf_bank_offset = RK3288_GPIO5B_GRF_OFFSET, .grf_pin_offset =  0, .grf_config_size = 2, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO5_OFFSET, .gpio_control_offset = 12, .grf_bank_offset = RK3288_GPIO5B_GRF_OFFSET, .grf_pin_offset =  8, .grf_config_size = 2, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO6_OFFSET, .gpio_control_offset =  0, .grf_bank_offset = RK3288_GPIO6A_GRF_OFFSET, .grf_pin_offset =  0, .grf_config_size = 1, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO5_OFFSET, .gpio_control_offset = 14, .grf_bank_offset = RK3288_GPIO5B_GRF_OFFSET, .grf_pin_offset = 12, .grf_config_size = 2, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .grf_config_size = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO5_OFFSET, .gpio_control_offset = 15, .grf_bank_offset = RK3288_GPIO5B_GRF_OFFSET, .grf_pin_offset = 14, .grf_config_size = 2, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO5_OFFSET, .gpio_control_offset = 10, .grf_bank_offset = RK3288_GPIO5B_GRF_OFFSET, .grf_pin_offset =  4, .grf_config_size = 2, .is_gpio = 1, .mode = INPUT},

	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .grf_config_size = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO5_OFFSET, .gpio_control_offset = 11, .grf_bank_offset = RK3288_GPIO5B_GRF_OFFSET, .grf_pin_offset =  6, .grf_config_size = 2, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO8_OFFSET, .gpio_control_offset =  9, .grf_bank_offset = RK3288_GPIO8B_GRF_OFFSET, .grf_pin_offset =  2, .grf_config_size = 2, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .grf_config_size = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO8_OFFSET, .gpio_control_offset =  8, .grf_bank_offset = RK3288_GPIO8B_GRF_OFFSET, .grf_pin_offset =  0, .grf_config_size = 2, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO5_OFFSET, .gpio_control_offset = 19, .grf_bank_offset = RK3288_GPIO5C_GRF_OFFSET, .grf_pin_offset =  6, .grf_config_size = 1, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO8_OFFSET, .gpio_control_offset =  6, .grf_bank_offset = RK3288_GPIO8A_GRF_OFFSET, .grf_pin_offset = 12, .grf_config_size = 2, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO8_OFFSET, .gpio_control_offset =  7, .grf_bank_offset = RK3288_GPIO8A_GRF_OFFSET, .grf_pin_offset = 14, .grf_config_size = 2, .is_gpio = 1, .mode = INPUT},

	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .grf_config_size = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO8_OFFSET, .gpio_control_offset =  3, .grf_bank_offset = RK3288_GPIO8A_GRF_OFFSET, .grf_pin_offset =  6, .grf_config_size = 2, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO7_OFFSET, .gpio_control_offset = 17, .grf_bank_offset = RK3288_GPIO7CL_GRF_OFFSET, .grf_pin_offset = 4, .grf_config_size = 1, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO7_OFFSET, .gpio_control_offset = 18, .grf_bank_offset = RK3288_GPIO7CL_GRF_OFFSET, .grf_pin_offset = 8, .grf_config_size = 1, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO5_OFFSET, .gpio_control_offset = 13, .grf_bank_offset = RK3288_GPIO5B_GRF_OFFSET, .grf_pin_offset = 10, .grf_config_size = 2, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .grf_config_size = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO5_OFFSET, .gpio_control_offset = 16, .grf_bank_offset = RK3288_GPIO5C_GRF_OFFSET, .grf_pin_offset =  0, .grf_config_size = 2, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO7_OFFSET, .gpio_control_offset = 23, .grf_bank_offset = RK3288_GPIO7CH_GRF_OFFSET, .grf_pin_offset = 12, .grf_config_size = 3, .is_gpio = 1, .mode = INPUT},

	{.gpio_bank_offset = RK3288_GPIO7_OFFSET, .gpio_control_offset = 22, .grf_bank_offset = RK3288_GPIO7CH_GRF_OFFSET, .grf_pin_offset = 8, .grf_config_size = 2, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .grf_config_size = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO6_OFFSET, .gpio_control_offset =  1, .grf_bank_offset = RK3288_GPIO6A_GRF_OFFSET, .grf_pin_offset =  2, .grf_config_size = 1, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO7_OFFSET, .gpio_control_offset =  7, .grf_bank_offset = RK3288_GPIO7A_GRF_OFFSET, .grf_pin_offset = 14, .grf_config_size = 2, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO7_OFFSET, .gpio_control_offset =  8, .grf_bank_offset = RK3288_GPIO7B_GRF_OFFSET, .grf_pin_offset =  0, .grf_config_size = 2, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO6_OFFSET, .gpio_control_offset =  3, .grf_bank_offset = RK3288_GPIO6A_GRF_OFFSET, .grf_pin_offset =  6, .grf_config_size = 1, .is_gpio = 1, .mode = INPUT},
	{.gpio_bank_offset = 0, .gpio_control_offset = 0, .grf_bank_offset = 0, .grf_pin_offset = 0, .grf_config_size = 0, .is_gpio = 0, .mode = INPUT},
	{.gpio_bank_offset = RK3288_GPIO6_OFFSET, .gpio_control_offset =  4, .grf_bank_offset = RK3288_GPIO6A_GRF_OFFSET, .grf_pin_offset =  8, .grf_config_size = 1, .is_gpio = 1, .mode = INPUT}
};

void _write_mem(volatile uint32_t* mem_addr, uint32_t value) {
	//printf("Wrote %08X at %08X\n", value, (unsigned) mem_addr);
	__sync_synchronize();
	*mem_addr = value;
	__sync_synchronize();
}

uint32_t _read_mem(volatile uint32_t* mem_addr) {
	__sync_synchronize();
	uint32_t ret = 0;
	ret = *mem_addr;
	__sync_synchronize();
	//printf("Read %08X at %08X\n", ret, (unsigned) mem_addr);
	return ret;
}

void _set_bit(uint32_t* value, uint32_t bit) {
	*value |= 1 << bit;
}

void _clear_bit(uint32_t* value, uint32_t bit) {
	*value &= ~(1 << bit);
}

void _sleep_cyle(int cycles) {
	for(int j=0; j<cycles; j++){
		asm volatile("nop");
	}
}

void tinkerboard_set_gpio_mode(uint32_t pin_number, enum IOMode mode) {
	if(VALID_GPIO(pin_number) && _gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].is_gpio) {
		uint32_t register_data = _read_mem(_rk3288_gpio_block_base + ALIGN_TO_UINT32T(_gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].grf_bank_offset));

		for(uint32_t j = 0; j < _gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].grf_config_size; j++) {
			_clear_bit(&register_data, _gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].grf_pin_offset + j);
			_set_bit(&register_data, _gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].grf_pin_offset + j + RK3288_GRF_WRITEMASK_OFFSET);
		}
		_write_mem(_rk3288_gpio_block_base + ALIGN_TO_UINT32T(_gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].grf_bank_offset), register_data);

		register_data = _read_mem(_rk3288_gpio_block_base + ALIGN_TO_UINT32T(_gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].gpio_bank_offset));
		_clear_bit(&register_data, _gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].gpio_control_offset);
		_write_mem(_rk3288_gpio_block_base + ALIGN_TO_UINT32T(_gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].gpio_bank_offset), register_data);

		register_data = _read_mem(_rk3288_gpio_block_base + ALIGN_TO_UINT32T(_gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].gpio_bank_offset) + 0x01);
		if(mode == INPUT) {
			_clear_bit(&register_data, _gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].gpio_control_offset);
			_gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].mode = INPUT;
		} else if(mode == OUTPUT) {
			_set_bit(&register_data, _gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].gpio_control_offset);
			_gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].mode = OUTPUT;
		}
		_write_mem(_rk3288_gpio_block_base + ALIGN_TO_UINT32T(_gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].gpio_bank_offset) + 0x01, register_data);
	}
}

void tinkerboard_set_gpio_state(uint32_t pin_number, enum IOState state) {
	if(VALID_GPIO(pin_number) && _gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].is_gpio && _gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].mode == OUTPUT) {
		uint32_t register_data = _read_mem(_rk3288_gpio_block_base + ALIGN_TO_UINT32T(_gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].gpio_bank_offset));
		if(state == LOW) {
			_clear_bit(&register_data, _gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].gpio_control_offset);
		} else if(state == HIGH) {
			_set_bit(&register_data, _gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].gpio_control_offset);
		}
		_write_mem(_rk3288_gpio_block_base + ALIGN_TO_UINT32T(_gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].gpio_bank_offset), register_data);
	}
}

enum IOState tinkerboard_get_gpio_state(uint32_t pin_number) {
	if(VALID_GPIO(pin_number) && _gpio_header_pins[pin_number-1].is_gpio && _gpio_header_pins[GPIO_NUMBER_TO_INDEX(pin_number)].mode == INPUT) {

	}
	return INPUT;
}

void reset_header(void) {
	for(uint32_t i = 0; i < 40; i++) {
		if(_gpio_header_pins[i].is_gpio) {
		}
	}

	for(uint32_t i = 0; i < 40; i++) {
		if(_gpio_header_pins[i].is_gpio) {
		}
	}
}

int tinkerboard_init(void) {
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

	if(tinkerboard_init() == 1){
		printf("Successfully initialized\n");
		for(uint32_t idx = 1; idx<=40; idx++){
			tinkerboard_set_gpio_mode(idx, OUTPUT);
		}

		while(1){
			for(uint32_t idx = 1; idx<=40; idx++){
				tinkerboard_set_gpio_state(idx, HIGH);
			}

			for(uint32_t idx = 1; idx<=40; idx++){
				tinkerboard_set_gpio_state(idx, LOW);
			}
		}


	}

	tinkerboard_end();
}
