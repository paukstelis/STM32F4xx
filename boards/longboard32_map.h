/*
  longboard32_map.h - driver code for STM32F4xx ARM processors

  Part of grblHAL

  Copyright (c) 2022 Expatria Technologies

  grblHAL is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  grblHAL is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with grblHAL. If not, see <http://www.gnu.org/licenses/>.
*/

#if N_ABC_MOTORS > 2
#error "Axis configuration is not supported!"
#endif

#if !(defined(STM32F412Vx) && HSE_VALUE == 25000000) && !(defined(DEBUG) && IS_NUCLEO_DEVKIT == 144)
#error "This board has STM32F412 processor with a 25MHz crystal, select a corresponding build!"
#endif

#if ETHERNET_ENABLE && _WIZCHIP_ != 5500
#error "Board has a WZ5500 ethernet chip, please uncomment _WIZCHIP_ in my_machine.h!"
#endif

#ifndef BOARD_NAME
#ifdef BOARD_LONGBOARD32_EXT
#define BOARD_NAME "SuperLongBoard Ext"
#else
#define BOARD_NAME "SuperLongBoard"
#endif
#endif

#if (EEPROM_ENABLE || SLB_EEPROM_ENABLE) && !IS_NUCLEO_DEVKIT
#undef I2C_ENABLE
#undef EEPROM_ENABLE
#define I2C_ENABLE 1
#define EEPROM_ENABLE 128
#endif

#if I2C_ENABLE
#define I2C_PORT 1
#define I2C1_ALT_PINMAP 1
#endif

#define SERIAL_PORT     34   // GPIOD: TX = 8, GPIOC: RX = 6
#define SERIAL1_PORT    21   // GPIOD: TX = 5,        RX = 6

#define HAS_BOARD_INIT
#define WIZCHIP_SPI_PRESCALER   SPI_BAUDRATEPRESCALER_4
#define FATFS_SPI_PRESCALER     SPI_BAUDRATEPRESCALER_8

#if defined(BOARD_LONGBOARD32) && !IS_NUCLEO_DEVKIT
#undef TRINAMIC_ENABLE
#define TRINAMIC_ENABLE      2660
#define TRINAMIC_SPI_PORT       2
#elif TRINAMIC_ENABLE
#error "SLB EXT does not have Trinamic drivers!"
#endif

#if MODBUS_ENABLE
#define MODBUS_RTU_STREAM       1
#undef MODBUS_ENABLE
#define MODBUS_ENABLE           (MODBUS_RTU_ENABLED|MODBUS_RTU_DIR_ENABLED)
#endif

#ifdef MODBUS_DIR_AUX
#undef MODBUS_DIR_AUX
#endif
#define MODBUS_DIR_AUX          4

#if MPG_ENABLE == 1 && !ETHERNET_ENABLE
#define MPG_MODE_PORT           GPIOA
#define MPG_MODE_PIN            4
#endif

// Define step pulse output pins.
#define X_STEP_PORT             GPIOE
#define X_STEP_PIN              2
#define Y_STEP_PORT             GPIOE
#define Y_STEP_PIN              3
#define Z_STEP_PORT             GPIOE
#define Z_STEP_PIN              4
#define STEP_OUTMODE            GPIO_BITBAND

// Define step direction output pins.
#define X_DIRECTION_PORT        GPIOE
#define X_DIRECTION_PIN         7
#define Y_DIRECTION_PORT        GPIOE
#define Y_DIRECTION_PIN         8
#define Z_DIRECTION_PORT        GPIOE
#define Z_DIRECTION_PIN         9
#define DIRECTION_OUTMODE       GPIO_BITBAND

// Define stepper driver enable/disable output pin.
#define X_ENABLE_PORT           GPIOD
#define X_ENABLE_PIN            4
#define Y_ENABLE_PORT           GPIOC
#define Y_ENABLE_PIN            7
#define Z_ENABLE_PORT           GPIOD
#define Z_ENABLE_PIN            3
#define STEPPERS_ENABLE_OUTMODE GPIO_BITBAND

// Define homing/hard limit switch input pins.
#define X_LIMIT_PORT            GPIOB
#define X_LIMIT_PIN             5
#define Y_LIMIT_PORT            GPIOB
#define Y_LIMIT_PIN             9
#define Z_LIMIT_PORT            GPIOC
#define Z_LIMIT_PIN             13
#define LIMIT_INMODE            GPIO_BITBAND

// Define ganged axis or A axis step pulse and step direction output pins.
// Note that because of how grblHAL iterates the axes, the M3 and M4 need to swap

#ifdef BOARD_LONGBOARD32

#if N_GANGED && N_AXIS == 4

#define TRINAMIC_MIXED_DRIVERS  1
#define TRINAMIC_DRIVER_MASK    0b111

#define M3_AVAILABLE
#define M3_STEP_PORT            GPIOB
#define M3_STEP_PIN             10
#define M3_DIRECTION_PORT       GPIOE
#define M3_DIRECTION_PIN        11
#define M3_ENABLE_PORT          GPIOC
#define M3_ENABLE_PIN           10
#define M3_LIMIT_PORT           GPIOE
#define M3_LIMIT_PIN            14

// TMC2660 driver
#define M4_AVAILABLE
#define M4_STEP_PORT            GPIOE
#define M4_STEP_PIN             5
#define M4_DIRECTION_PORT       GPIOE
#define M4_DIRECTION_PIN        10
#ifndef Y_GANGED
#define M4_ENABLE_PORT          GPIOC
#define M4_ENABLE_PIN           7
#endif
#define M4_LIMIT_PORT           GPIOE
#define M4_LIMIT_PIN            6
#define M4_HOME_PORT            GPIOA
#define M4_HOME_PIN             3

#else

#if N_ABC_MOTORS > 0
// TMC2660 driver
#define M3_AVAILABLE
#define M3_STEP_PORT            GPIOE
#define M3_STEP_PIN             5
#define M3_DIRECTION_PORT       GPIOE
#define M3_DIRECTION_PIN        10
#define M3_LIMIT_PORT           GPIOE
#define M3_LIMIT_PIN            6
#define M3_ENABLE_PORT          GPIOC
#define M3_ENABLE_PIN           7
#define M3_HOME_PORT            GPIOA
#define M3_HOME_PIN             3
#endif

#if N_ABC_MOTORS == 2

#define TRINAMIC_MIXED_DRIVERS  1
#define TRINAMIC_DRIVER_MASK    0b1111

#define M4_AVAILABLE
#define M4_STEP_PORT            GPIOB
#define M4_STEP_PIN             10
#define M4_DIRECTION_PORT       GPIOE
#define M4_DIRECTION_PIN        11
#define M4_ENABLE_PORT          GPIOC
#define M4_ENABLE_PIN           10
#define M4_LIMIT_PORT           GPIOE
#define M4_LIMIT_PIN            14
#else
#define TRINAMIC_MIXED_DRIVERS  0
#endif

#endif

#else // SLB EXT

#if N_GANGED && N_AXIS == 4

#define M3_AVAILABLE
#define M3_STEP_PORT            GPIOB
#define M3_STEP_PIN             10
#define M3_DIRECTION_PORT       GPIOE
#define M3_DIRECTION_PIN        11
#define M3_ENABLE_PORT          GPIOC
#define M3_ENABLE_PIN           10
#define M3_LIMIT_PORT           GPIOE
#define M3_LIMIT_PIN            14

#define M4_AVAILABLE
#define M4_STEP_PORT            GPIOE
#define M4_STEP_PIN             5
#define M4_DIRECTION_PORT       GPIOE
#define M4_DIRECTION_PIN        10
#ifndef Y_GANGED
#define M4_ENABLE_PORT          GPIOC
#define M4_ENABLE_PIN           7
#endif
#define M4_LIMIT_PORT           GPIOE
#define M4_LIMIT_PIN            6

#else

#if N_ABC_MOTORS > 0
#define M3_AVAILABLE
#define M3_STEP_PORT            GPIOE
#define M3_STEP_PIN             5
#define M3_DIRECTION_PORT       GPIOE
#define M3_DIRECTION_PIN        10
#define M3_LIMIT_PORT           GPIOE
#define M3_LIMIT_PIN            6
#define M3_ENABLE_PORT          GPIOC
#define M3_ENABLE_PIN           7
#endif

#if N_ABC_MOTORS == 2
#define M4_AVAILABLE
#define M4_STEP_PORT            GPIOB
#define M4_STEP_PIN             10
#define M4_DIRECTION_PORT       GPIOE
#define M4_DIRECTION_PIN        11
#define M4_ENABLE_PORT          GPIOC
#define M4_ENABLE_PIN           10
#endif

#endif

#endif

//*****Switchbank will always claim the first 4 aux outputs******
#define AUXOUTPUT3_PORT         GPIOC
#define AUXOUTPUT3_PIN          14
#define AUXOUTPUT2_PORT         GPIOC
#define AUXOUTPUT2_PIN          0
#define AUXOUTPUT1_PORT         GPIOC
#define AUXOUTPUT1_PIN          1
#define AUXOUTPUT0_PORT         GPIOC
#define AUXOUTPUT0_PIN          8
#define AUXOUTPUT4_PORT         GPIOB // Modbus direction
#define AUXOUTPUT4_PIN          0

#define AUXOUTPUT7_PORT         GPIOC // Spindle 2 on
#define AUXOUTPUT7_PIN          12
#define AUXOUTPUT8_PORT         GPIOC // Spindle 2 PWM
#define AUXOUTPUT8_PIN          6
#define AUXOUTPUT9_PORT         GPIOE // Spindle 1 on
#define AUXOUTPUT9_PIN          13
#define AUXOUTPUT10_PORT        GPIOA // Spindle 1 PWM
#define AUXOUTPUT10_PIN         8
#define AUXOUTPUT11_PORT        GPIOB // Spindle 1 direction
#define AUXOUTPUT11_PIN         1
#define AUXOUTPUT12_PORT        GPIOB // Coolant flood
#define AUXOUTPUT12_PIN         14
#define AUXOUTPUT13_PORT        GPIOB // Coolant mist
#define AUXOUTPUT13_PIN         4

#define EVENTOUT_1_ACTION       1
#define EVENTOUT_2_ACTION       4
#define EVENTOUT_3_ACTION       1
#define EVENTOUT_4_ACTION       4

#if DRIVER_SPINDLE_ENABLE & SPINDLE_ENA
#define SPINDLE_ENABLE_PORT     AUXOUTPUT9_PORT
#define SPINDLE_ENABLE_PIN      AUXOUTPUT9_PIN
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_PWM
#define SPINDLE_PWM_PORT        AUXOUTPUT10_PORT
#define SPINDLE_PWM_PIN         AUXOUTPUT10_PIN
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_DIR
#define SPINDLE_DIRECTION_PORT  AUXOUTPUT11_PORT
#define SPINDLE_DIRECTION_PIN   AUXOUTPUT11_PIN
#endif

#if DRIVER_SPINDLE1_ENABLE & SPINDLE_ENA
#define SPINDLE1_ENABLE_PORT    AUXOUTPUT7_PORT
#define SPINDLE1_ENABLE_PIN     AUXOUTPUT7_PIN
#endif
#if DRIVER_SPINDLE1_ENABLE & SPINDLE_PWM
#define SPINDLE1_PWM_PORT       AUXOUTPUT8_PORT
#define SPINDLE1_PWM_PIN        AUXOUTPUT8_PIN
#endif

// Define flood and mist coolant enable output pins.
#if COOLANT_ENABLE & COOLANT_FLOOD
#define COOLANT_FLOOD_PORT      AUXOUTPUT12_PORT
#define COOLANT_FLOOD_PIN       AUXOUTPUT12_PIN
#endif
#if COOLANT_ENABLE & COOLANT_MIST
#define COOLANT_MIST_PORT       AUXOUTPUT13_PORT
#define COOLANT_MIST_PIN        AUXOUTPUT13_PIN
#endif

#define NEOPIXEL_PWM
#define LED_PORT                GPIOC // rail LED strip (PWM), does not work when debugging due to U14/R96 chopping output
#define LED_PIN                 9
#if !defined(DEBUG) && RGB_LED_ENABLE
#define NEOPIXEL_GPO
#define LED1_PORT               GPIOA // ring LED strip (GPO), when enabled SWD debugging is blocked (use $DFU to reenable)
#define LED1_PIN                13
#endif

#define AUXINPUT0_ANALOG_PORT  GPIOA
#define AUXINPUT0_ANALOG_PIN   0

#define AUXINPUT0_PORT          GPIOD // AUX_IN_0
#define AUXINPUT0_PIN           12
#define AUXINPUT1_PORT          GPIOD // AUX_IN_1
#define AUXINPUT1_PIN           13
#define AUXINPUT2_PORT          GPIOD // AUX_IN_2
#define AUXINPUT2_PIN           14

#define AUXINPUT3_PORT          GPIOC // TLS/PRB DET
#define AUXINPUT3_PIN           15

#define AUXINPUT4_PORT          GPIOE // MACRO1
#define AUXINPUT4_PIN           1

#define AUXINPUT5_PORT          GPIOE // MACRO2
#define AUXINPUT5_PIN           0

#define AUXINPUT6_PORT          GPIOC // CYC/ST, MACRO3
#define AUXINPUT6_PIN           11

#define AUXINPUT7_PORT          GPIOD // AUX_IN_3
#define AUXINPUT7_PIN           15

#define AUXINPUT8_PORT          GPIOB // SPIN_SPEED, Spindle at speed or spindle encoder index
#define AUXINPUT8_PIN           8

#define AUXINPUT9_PORT          GPIOD // Safety door
#define AUXINPUT9_PIN           7

#define AUXINPUT10_PORT         GPIOB // I2C strobe
#define AUXINPUT10_PIN          3

#define AUXINPUT11_PORT         GPIOC // Probe
#define AUXINPUT11_PIN          4

#define AUXINPUT13_PORT         GPIOB //  // Reset/EStop
#define AUXINPUT13_PIN          12

#if CONTROL_ENABLE & CONTROL_HALT
#define RESET_PORT              AUXINPUT13_PORT
#define RESET_PIN               AUXINPUT13_PIN
#endif

#if SAFETY_DOOR_ENABLE
#define SAFETY_DOOR_PORT        AUXINPUT9_PORT
#define SAFETY_DOOR_PIN         AUXINPUT9_PIN
#endif

// Define probe switch input pin.
#if PROBE_ENABLE
#define PROBE_PORT              AUXINPUT11_PORT
#define PROBE_PIN               AUXINPUT11_PIN
#endif

#if TOOLSETTER_ENABLE
#define TOOLSETTER_PORT         AUXINPUT3_PORT
#define TOOLSETTER_PIN          AUXINPUT3_PIN
#endif

#if I2C_STROBE_ENABLE
#define I2C_STROBE_PORT         AUXINPUT10_PORT
#define I2C_STROBE_PIN          AUXINPUT10_PIN
#endif

#if SPINDLE_ENCODER_ENABLE
// Possible only with pulse lengthening?
#define SPINDLE_PULSE_PORT      GPIOD // AUXINPUT12_PORT
#define SPINDLE_PULSE_PIN       2 // AUXINPUT12_PIN
#if SPINDLE_SYNC_ENABLE
#define SPINDLE_INDEX_PORT      AUXINPUT8_PORT
#define SPINDLE_INDEX_PIN       AUXINPUT8_PIN
#endif
#endif

#define CONTROL_INMODE GPIO_BITBAND

#ifdef BOARD_LONGBOARD32

#define AUXINPUT12_PORT         GPIOD // External stepper driver alarm (A) or spindle encoder pulse
#define AUXINPUT12_PIN          2

#if MOTOR_FAULT_ENABLE && ((N_GANGED && N_AXIS == 4) || N_AXIS == 5)
#define MOTOR_FAULT_ENABLE      1
#define MOTOR_FAULT_PORT        AUXINPUT12_PORT
#define MOTOR_FAULT_PIN         AUXINPUT12_PIN
#endif

#define TMC_STEALTHCHOP         0

#define X_HOME_PORT             GPIOA
#define X_HOME_PIN              15
#define Y_HOME_PORT             GPIOA
#define Y_HOME_PIN              1
#define Z_HOME_PORT             GPIOA
#define Z_HOME_PIN              2
#define HOME_INMODE             GPIO_BITBAND

// SPI2 is used: GPIOB pin 12 (SCK) GPIOC pin 2 (MISO) and 3 (MOSI)
#define MOTOR_CSX_PORT          GPIOD
#define MOTOR_CSX_PIN           11
#define MOTOR_CSY_PORT          GPIOE
#define MOTOR_CSY_PIN           15
#define MOTOR_CSZ_PORT          GPIOD
#define MOTOR_CSZ_PIN           9
#if (N_ABC_MOTORS == 2) && (N_AXIS == 4)
#define MOTOR_CSM4_PORT         GPIOE
#define MOTOR_CSM4_PIN          12
#else // since the board has soldered drivers the CS pin has to be set high at startup even when the motor is not used
#define MOTOR_CSM3_PORT         GPIOE
#define MOTOR_CSM3_PIN          12
#endif

#else

#define X_MOTOR_FAULT_PORT      GPIOA
#define X_MOTOR_FAULT_PIN       15
#define Y_MOTOR_FAULT_PORT      GPIOA
#define Y_MOTOR_FAULT_PIN       1
#define Z_MOTOR_FAULT_PORT      GPIOA
#define Z_MOTOR_FAULT_PIN       2
#define MOTOR_FAULT_INMODE      GPIO_BITBAND

#endif

#if SDCARD_ENABLE || ETHERNET_ENABLE
#define SPI_PORT                1 // GPIOA, SCK_PIN = 5, MISO_PIN = 6, MOSI_PIN = 7  probably needs fixing
#endif

#if ETHERNET_ENABLE
#undef SPI_ENABLE
#define SPI_ENABLE              1
#define SPI_CS_PORT             GPIOA // CS_JOG_SW
#define SPI_CS_PIN              4
#define SPI_IRQ_PORT            GPIOA // RXD_INT
#define SPI_IRQ_PIN             10
#define SPI_RST_PORT            GPIOA // TXD_INT
#define SPI_RST_PIN             9
#endif

#if SDCARD_ENABLE
#define SD_CS_PORT              GPIOB
#define SD_CS_PIN               15
#endif

#if MACROS_ENABLE

#define MACRO_1_AUXIN_PORT      AUXINPUT4_PORT
#define MACRO_1_AUXIN_PIN       AUXINPUT4_PIN
#define MACRO_1_BUTTONACTION    1

#define MACRO_2_AUXIN_PORT      AUXINPUT5_PORT
#define MACRO_2_AUXIN_PIN       AUXINPUT5_PIN
#define MACRO_2_BUTTONACTION    2

#define MACRO_3_AUXIN_PORT      AUXINPUT6_PORT
#define MACRO_3_AUXIN_PIN       AUXINPUT6_PIN
#define MACRO_3_BUTTONACTION    4

#endif // MACROS_ENABLE

#define CAN_PORT                GPIOD
#define CAN_RX_PIN              0
#define CAN_TX_PIN              1
