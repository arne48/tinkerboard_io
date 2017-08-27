#include "tinkerboard_io.h"

int main(int argc, const char * argv[]){
	
	if(tinkerboard_init() == 1){
		printf("Successfully initialized\n");
		for(uint32_t idx = 1; idx<=40; idx++){
			tinkerboard_set_gpio_mode(idx, OUTPUT);
		}
		
		tinkerboard_get_gpio_mode(8);
		tinkerboard_get_gpio_mode(10);
		tinkerboard_get_gpio_mode(16);
		tinkerboard_get_gpio_mode(18);
		
		tinkerboard_get_gpio_mode(11);
		tinkerboard_get_gpio_mode(13);
		tinkerboard_get_gpio_mode(15);
		tinkerboard_get_gpio_mode(29);

		tinkerboard_get_gpio_mode(32);
		tinkerboard_get_gpio_mode(36);
		
		tinkerboard_get_gpio_mode(33);
		tinkerboard_get_gpio_mode(37);

		
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
