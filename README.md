# Yet another IO library for the Asus Tinker Board

## Introduction
Due to some shortcomings with the wiringTB library which Asus provides and my need for direct SPI access without the spidev subsystem I decided to write this minimalistic IO library for the Tinker Board. This is done by the consistent utilization of direct memory access _(via virtual memory mapping)_.
The need for direct access was based on the requirements of my project.
So I implemented the features I needed plus some nice to have ones for the completeness of feature groups. E.g. including reading from gpios even when I just use them for their output functionality.

### Side Note:
In my project I am using a RT Preempt enabled linux kernel _(4.4.79)_ with the Armbian distribution. Due to problems of rt-patching the kernel provided by  Asus _(tag/1.9 at that time, haven't tried since)_ I started with a vanilla kernel and backported a lot of changes to re-enable all functionalities I needed _(see the following link for additional information)_.
The forked and updated package of armbian can be found here:
[https://github.com/arne48/armbian_build](https://github.com/arne48/armbian_build) 

__This might be helpful for you too. And interfaces that might interfere with the gpio header are disabled.__

## Features
### GPIO
- __Input & Output__

The library provides easy to use functions to setup any non-power pin to either an Input or an Output.

- __Pullup & Down settings for Inputs__

Functions are provided to set the pulling resistors of pins. The supported types are normal, pullup, pulldown and buskeeper.

- __Drivestrength (mA) for Outputs__

For pins operating as an output the max. drive strength can be set to 2, 4, 8 or 12 mA.

### SPI
- __SPI0 and SPI2 usable__

The image provided by Asus just enables SPI2 which then can be used by _spidev_ via _ioctl_. This library allows it to utilize both SPI controllers.

- __Up to 66.7MHz clockspeed__

The clock-sources of the clock-reset-unit for the SPI controllers are set in a way that they don't depend on the general PLL clock but are using the codec PLL which should be always stable. Further the divider setting allows a maximum clockspeed for the SPI controllers of up to 66.7MHz.

- __Slave Select can be set to any free gpio or none__

One functionality which I already missed in wiringPi was to disable the hardware slave select so it can be set by software to a wide variety of pins without sacrificing the still active hardware pin to be disconnected. To allow the most possible flexibility the slave selects were decided to be set by software internally alltogether. By implementing it like this it is possible to use any pin as a slave select which is then automatically operated by the library. Or it is also possible to set no slave select at all and handle it by yourself with as much slaves as needed. 

- __SPI modes 0, 1, 2, 3 are supported__

The SPI controllers themself support all 4 available SPI modes and so does the library.

- __MSB first and LSB first mode can be set__

Via the configuration provided by the library it is possible to set the byte-order if needed.

### Examples
The examples are located in the _examples_ directory. They provide a reference to the usage of the library.

- __GPIO Input__

In this example all pins are set as inputs with pullups. Once a pin gets toggled by bridging them to GND or releasing them from GND a message will be prompted to the command-line. (End with any key)

- __GPIO Output__

In this examples all pins are set to ouput mode and are toggled in an infinite loop. (End with any key)

- __SPI__

This example is meant to be a loopback test and sends 64kb via SPI while checking the received data for corruptions.

## Brief Documentation
__Pin numbering:__

The pins are numbered intuitively by their position on the header from 1 (3.3V) to 40 (last gpio). 
For an overview of the header please check this image from Asus: [Link](https://dlcdnimgs.asus.com/websites/global/products/UUSx6FPuqP3uZrhv/images/pic_gpio.png)

__Error Handling:__

To prevent spamming of the console errors are handled quiete and gracefully. If an operation is illegal it will neither crash or print an error message in those cases no operation will be executed and in case of a non-void function a default value will be returned.

#### Board Init
_Maps the hardware into virtual memory and resets header pins to inputs_

__returns:__ 1 if initialization was successful otherwise returns 0
```cpp
int tinkerboard_init(void);
```
#### Board De-Init
_If gpio memory is available it resets the header and finally will unmap the virtual memory of gpio, cru and spi_
```cpp
void tinkerboard_end(void);
```
#### Resetting all pins as Inputs
_Resets all pins of header to inputs using pullups_
```cpp
void tinkerboard_reset_header(void);
```

#### Get current grf (IOMUX) configuration of pin
_Reads the current configuration value of the requested pin from the corresponding grf register.
If requested pin is a power-pin it returns 0_

__pin_number:__ number of pin to read the grf config of

__returns:__ configuration (IOMUX) of pin. Contact appropriate documentation for further details
```cpp
uint32_t tinkerboard_get_grf_config(uint32_t pin_number);
```

#### Get data direction mode of pin
_Reads the data direction register for specified pin and returns its mode as enum.
If requested pin is a power-pin it returns Input_

__pin_number:__ number of pin to read the data direction config of

__returns:__ data direction of gpio. This can be either _Input_ or _Output_
```cpp
enum IOMode tinkerboard_get_gpio_mode(uint32_t pin_number);
```

#### Set data direction mode of pin
_Sets the data direction of specified pin to Input or Output and also the grf register to gpio_

__pin_number:__ number of pin to set the data direction for

__mode:__ direction (_Input_ or _Output_) to set the pin to
```cpp
void tinkerboard_set_gpio_mode(uint32_t pin_number, enum IOMode mode);
```

#### Set state of pin (if Output)
_If gpio is set as an Output this function will set its voltage level to either HIGH or LOW_

__pin_number:__ number of output pin to set the voltage level for

__state:__ state to set the pin to (_HIGH_ or _LOW_)
```cpp
void tinkerboard_set_gpio_state(uint32_t pin_number, enum IOState state);
```

#### Get state of pin (if Input)
_If gpio is set as an Input this function will return the current state sensed on Input_

__pin_number:__ number of pin to request the current state for

__returns:__ current state that was sensed on _Input_ (_HIGH_ or _LOW_)
```cpp
enum IOState tinkerboard_get_gpio_state(uint32_t pin_number);
```

#### Setup pullup & down configuration of pin (relevant for Inputs)
_This function allows to configure a pulling behaviour for a pin to prevent it from floating eventually.
Available configurations are NORMAL_Z, PULLUP, PULLDOWN, BUSKEEPER._

__pin_number:__ number of pin to set the pulling behaviour for

__mode:__ pulling mode to set the specified pin to
```cpp
void tinkerboard_set_gpio_pud(uint32_t pin_number, enum PUDMode mode);
```

#### Set drive strength of pin (relevant for Outputs)
_Sets the output drive strength of the specified pin. Available options are DRV2MA, DRV4MA, DRV8MA, DRV12MA._

__pin_number:__ pin to set the output driving strength of

__strength:__ strength to set the specified pin to
```cpp
void tinkerboard_set_gpio_drive_strength(uint32_t pin_number, enum DriveStrength strength);
```

#### Initialize SPI controller
_Initializes the requested SPI controller with the configuration passed._

__controller:__ enum of SPI controller to initialize (_SPI0_ or _SPI2_)

__mode_config:__ configuration for the SPI controller
```cpp
void tinkerboard_spi_init(enum SPIController controller, struct spi_mode_config_t mode_config);
```

#### De-Initialize SPI controller
_Disables specified SPI controller_

__controller:__ enum of SPI controller to disable (_SPI0_ or _SPI2_)
```cpp
void tinkerboard_spi_end(enum SPIController controller);
```

#### Transfer (send & receive) n-bytes via SPI
_Transfers a passed buffer of specified length by using the requested SPI controller and writes received data into receive buffer._

__controller:__ enum of SPI controller to transfer data with (_SPI0_ or _SPI2_)

__tx_buff:__ pointer to transfer buffer

__rx_buff:__ pointer to receive buffer

__length:__ length of transfer buffer

__mode_config:__ configuration the SPI controller was initialized with
```cpp
void tinkerboard_spi_transfer(enum SPIController controller, uint8_t* tx_buff, uint8_t* rx_buff, uint32_t length, struct spi_mode_config_t mode_config);
```

#### SPI Configuration struct
_This struct contains the configurations to initialize the SPI controller with._

__Important:__ _data_frame_size and transfer_mode are exposed for eventual customizations.
If their handling is not added the defaults DFS_8 and TRANSMIT_RECEIVE must be used._

__clk_divider:__ defines any even divider >=2 (66.7MHz) to reduce the SPI clock with

__clk_mode:__ defines the SPI clock mode (_0, 1, 2 or 3_)

__data_frame_size:__ specifies the size of the data frame (_DFS_4_, _DFS_8_ or _DFS_16_)

__slave_select:__ specifies the pin to use as slave select. This can be any free pin. Or if no slave select is needed use define _NO_SS_.

__transfer_mode:__ transfer mode of SPI controller. (_TRANSMIT_RECEIVE_, _TRANSMIT_, _RECEIVE_). Please read important note.

__byte_order:__ Sets the order the controller transfers bytes by (_MSB_FIRST_, _LSB_FIRST_)
```cpp
struct spi_mode_config_t {
  uint32_t clk_divider;
  uint32_t clk_mode;
  enum SPIDataFrameSize data_frame_size;
  uint32_t slave_select;
  enum SPITransferMode transfer_mode;
  enum SPIByteOrder  byte_order;
};
```

## Installation
For compilation and installation cmake is used.
Besides building the library this also supports its installation.
By installing the library it is possible to use the provided cmake module to easily make use of the library within your own projects.

### CMake make & install
1. ```$mkdir build && cd build```
2. ```$cmake ..```
3. ```$make```
4. ```$sudo make install```

### Usage of _find_package()_ in own project's CMakeLists.txt
1. Place the cmake module _(FindTINKERBOARD_IO.cmake)_ found in the cmake_module directory somewhere inside of your project.
2. add ```set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/PATH_TO_CMAKE_MODULE/")``` where __"PATH_TO_CMAKE_MODULE"__ is the relative path to the directory containing the module within your project.
3. now you can use ```find_package(TINKERBOARD_IO REQUIRED)``` to get the ${TINKERBOARD_IO_LIBRARIES} and ${TINKERBOARD_IO_INCLUDE_DIRS} variables for further usage.
