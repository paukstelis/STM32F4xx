/*
  btt_skr_2.0_map.h - driver code for STM32F407 ARM processors

  Part of grblHAL

  Copyright (c) 2021 fitch22

  GrblHAL is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  GrblHAL is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with GrblHAL. If not, see <http://www.gnu.org/licenses/>.
*/

#if N_ABC_MOTORS > 3
#error "FLY-CDY supports 6 motors max."
#endif

#if IS_NUCLEO_DEVKIT
// When debugging with Nucleo-144
#elif !(defined(STM32F407xx) || defined(STM32F429xx)) || HSE_VALUE != 8000000
#error "This board has a STM32F407 or STM32F429 processor with a 8MHz crystal, select a corresponding build!"
#endif

#define BOARD_NAME "FLY-CDY-V3"
#define BOARD_URL ""
//#define HAS_BOARD_INIT

//Several Limit pins GPIOC, Pin6 and GPIOD, Pin10 seem to be being used in some other capacity

#define SERIAL_PORT     12   // GPIOA: TX = 9, RX = 10 *
#define I2C_PORT        2   // GPIOB: SCL = 8, SDA = 9 ???????
//#if ETHERNET_ENABLE
//#define SPI_PORT        2   // GPIOB, SCK_PIN = 13, MISO_PIN = 14, MOSI_PIN = 15
//#endif

#if TRINAMIC_SPI_ENABLE && ETHERNET_ENABLE
#error "Trinamic SPI driver plugin and networking plugins cannot be enabled together!"
#endif

// If we want to debug, we need to use USART1
#if defined(DEBUG) && defined(USB_SERIAL_CDC)
//#undef USB_SERIAL_CDC
#endif

// Define step pulse output pins.
#define X_STEP_PORT                 GPIOE
#define X_STEP_PIN                  5                   // X
#define X_DIRECTION_PORT            GPIOC
#define X_DIRECTION_PIN             0
#define X_ENABLE_PORT               GPIOC
#define X_ENABLE_PIN                1
#define X_LIMIT_PORT                GPIOC
#define X_LIMIT_PIN                 7                           // X- Limit

#define Y_STEP_PORT                 GPIOE
#define Y_STEP_PIN                  1                   // Y
#define Y_DIRECTION_PORT            GPIOD
#define Y_DIRECTION_PIN             3
#define Y_ENABLE_PORT               GPIOD
#define Y_ENABLE_PIN                4
#define Y_LIMIT_PORT                GPIOD
#define Y_LIMIT_PIN                 11                           // Y- Limit

#define Z_STEP_PORT                 GPIOE
#define Z_STEP_PIN                  4                  // Z
#define Z_DIRECTION_PORT            GPIOC
#define Z_DIRECTION_PIN             13
#define Z_ENABLE_PORT               GPIOC
#define Z_ENABLE_PIN                14
#define Z_LIMIT_PORT                GPIOD
#define Z_LIMIT_PIN                 10  

#define STEP_OUTMODE                GPIO_BITBAND
//#define STEP_PINMODE                PINMODE_OD // Uncomment for open drain outputs
#define DIRECTION_OUTMODE           GPIO_BITBAND
//#define DIRECTION_PINMODE           PINMODE_OD // Uncomment for open drain outputs
//#define STEPPERS_ENABLE_PINMODE   PINMODE_OD // Uncomment for open drain outputs
#define LIMIT_INMODE                GPIO_BITBAND

#if N_ABC_MOTORS > 0
#define M3_AVAILABLE                // E0
#define M3_STEP_PORT                GPIOE
#define M3_STEP_PIN                 3
#define M3_DIRECTION_PORT           GPIOB
#define M3_DIRECTION_PIN            7
#define M3_ENABLE_PORT              GPIOB
#define M3_ENABLE_PIN               8
//#define M3_LIMIT_PORT               GPIOB
//#define M3_LIMIT_PIN                2
#endif

// Define ganged axis or B axis step pulse and step direction output pins.
#if N_ABC_MOTORS > 2
#define M4_AVAILABLE                // E1
#define M4_STEP_PORT                GPIOE
#define M4_STEP_PIN                 2
#define M4_DIRECTION_PORT           GPIOD
#define M4_DIRECTION_PIN            6
#define M4_ENABLE_PORT              GPIOD
#define M4_ENABLE_PIN               7
//#define M4_LIMIT_PORT               GPIOE                       // orig GPIOA
//#define M4_LIMIT_PIN                15                          // orig 0
#endif

// Define ganged axis or B axis step pulse and step direction output pins.
#if N_ABC_MOTORS == 3
#define M5_AVAILABLE                // E1
#define M5_STEP_PORT                GPIOE
#define M5_STEP_PIN                 0
#define M5_DIRECTION_PORT           GPIOA
#define M5_DIRECTION_PIN            15
#define M5_ENABLE_PORT              GPIOD
#define M5_ENABLE_PIN               0
//#define M5_LIMIT_PORT               GPIOE                       
//#define M5_LIMIT_PIN                15                          
#endif

#define AUXOUTPUT0_PORT             GPIOB // Laser/Spindle PWM
#define AUXOUTPUT0_PIN              10
#define AUXOUTPUT1_PORT             GPIOD // Spindle direction, FAN2
#define AUXOUTPUT1_PIN              13
#define AUXOUTPUT2_PORT             GPIOD // Spindle enable, E0HEAT
#define AUXOUTPUT2_PIN              12
#define COPROC_RESET_PORT           GPIOE //None of these are correct yet
#define COPROC_BOOT0_PORT           GPIOE
#define COPROC_RESET_PIN            11
#define COPROC_BOOT0_PIN            10

// Define driver spindle pins
#if DRIVER_SPINDLE_ENABLE
#define SPINDLE_ENABLE_PORT         AUXOUTPUT2_PORT
#define SPINDLE_ENABLE_PIN          AUXOUTPUT2_PIN
#if DRIVER_SPINDLE_PWM_ENABLE
#define SPINDLE_PWM_PORT            AUXOUTPUT0_PORT
#define SPINDLE_PWM_PIN             AUXOUTPUT0_PIN
#endif
#if DRIVER_SPINDLE_DIR_ENABLE
#define SPINDLE_DIRECTION_PORT      AUXOUTPUT1_PORT
#define SPINDLE_DIRECTION_PIN       AUXOUTPUT1_PIN
#endif
#endif //DRIVER_SPINDLE_ENABLE

// Define flood and mist coolant enable output pins.
#define COOLANT_FLOOD_PORT          GPIOD
#define COOLANT_FLOOD_PIN           12                           // HEAT0
#define COOLANT_MIST_PORT           GPIOA
#define COOLANT_MIST_PIN            0                           // HEAT1

// Define user-control controls (cycle start, reset, feed hold) input pins.
// These are all available on EXP2 along with electrical RESET* (EXP2-8)
#define CONTROL_PORT                GPIOA
#define RESET_PIN                   4                           // Exp2-4
#define FEED_HOLD_PIN               13                           // Exp2-2
#define CYCLE_START_PIN             5                           // Exp2-1
#define CONTROL_INMODE              GPIO_BITBAND

#define AUXINPUT0_PORT              GPIOA
#define AUXINPUT0_PIN               7                           // EXP2-6
#define AUXINPUT1_PORT              GPIOC
#define AUXINPUT1_PIN               2                         // BLTouch PE6

#if PROBE_ENABLE
#define PROBE_PORT                  AUXINPUT1_PORT
#define PROBE_PIN                   AUXINPUT1_PIN
#endif

#if SAFETY_DOOR_ENABLE
#define SAFETY_DOOR_PORT            AUXINPUT0_PORT
#define SAFETY_DOOR_PIN             AUXINPUT0_PIN
#endif

#if MOTOR_FAULT_ENABLE
#define MOTOR_FAULT_PORT            AUXINPUT0_PORT
#define MOTOR_FAULT_PIN             AUXINPUT0_PIN
#endif

// Safe Power Control
//#define STEPPERS_POWER_PORT         GPIOC
//#define STEPPERS_POWER_PIN          2

#if SDCARD_ENABLE
#define SDCARD_SDIO                 1
#endif

#if ETHERNET_ENABLE
#undef SPI_ENABLE
#define SPI_ENABLE 					0 // GPIOA: SCK = 5, MISO = 6, MOSI = 7
//#define SPI_CS_PORT                 GPIOB
//#define SPI_CS_PIN                  12                              // ESP-CS
//#define SPI_IRQ_PORT                GPIOB
//#define SPI_IRQ_PIN                 9                              // ESP-IO4
//#define SPI_RST_PORT                GPIOC
//#define SPI_RST_PIN                 14                              // ESP-RST
#endif

#if TRINAMIC_UART_ENABLE

#undef TRINAMIC_UART_ENABLE
#define TRINAMIC_UART_ENABLE        2

#define MOTOR_UARTX_PORT            GPIOC
#define MOTOR_UARTX_PIN             15
#define MOTOR_UARTY_PORT            GPIOD
#define MOTOR_UARTY_PIN             1
#define MOTOR_UARTZ_PORT            GPIOA
#define MOTOR_UARTZ_PIN             8

#ifdef  M3_AVAILABLE
#define MOTOR_UARTM3_PORT           GPIOB
#define MOTOR_UARTM3_PIN            6
#endif

#ifdef  M4_AVAILABLE
#define MOTOR_UARTM4_PORT           GPIOD
#define MOTOR_UARTM4_PIN            5
#endif

#ifdef  M5_AVAILABLE
#define MOTOR_UARTM5_PORT           GPIOE
#define MOTOR_UARTM5_PIN            9
#endif

#elif TRINAMIC_SPI_ENABLE

//SPI has not been tested
// MISO pin is also SWCLK from JTAG port, so can't debug with Trinamic SPI drivers:-(
#define TRINAMIC_MOSI_PORT          GPIOB
#define TRINAMIC_MOSI_PIN           5
#define TRINAMIC_SCK_PORT           GPIOB
#define TRINAMIC_SCK_PIN            3

// For debugging, change this to PA6 (on EXP2) and jumper directly to MISO pins on TMC2130s.
#ifdef DEBUG
#define TRINAMIC_MISO_PORT          GPIOB
#define TRINAMIC_MISO_PIN           4		// temporary EXP2-3 to use while debugging.  real one is PA14
#else
#define TRINAMIC_MISO_PORT          GPIOB
#define TRINAMIC_MISO_PIN           4
#endif

#define MOTOR_CSX_PORT              GPIOC
#define MOTOR_CSX_PIN               15
#define MOTOR_CSY_PORT              GPIOD
#define MOTOR_CSY_PIN               1
#define MOTOR_CSZ_PORT              GPIOA
#define MOTOR_CSZ_PIN               8

#ifdef  M3_AVAILABLE
#define MOTOR_CSM3_PORT             GPIOB
#define MOTOR_CSM3_PIN              6
#endif

#ifdef  M4_AVAILABLE
#define MOTOR_CSM4_PORT             GPIOD
#define MOTOR_CSM4_PIN              5
#endif

#endif
// EOF
