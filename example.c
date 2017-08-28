#include "tinkerboard_io.h"

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
