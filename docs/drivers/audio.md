# Audio Driver {#audio-driver}

The [Audio feature](../features/audio) breaks the hardware specifics out into separate, exchangeable driver units, with a common interface to the audio-"core" - which itself handles playing songs and notes while tracking their progress in an internal state, initializing/starting/stopping the driver as needed.

Not all MCUs support every available driver, either the platform-support is not there (yet?) or the MCU simply does not have the required hardware peripheral.


## AVR {#avr}

Boards built around an Atmega32U4 can use two sets of PWM capable pins, each driving a separate speaker.
The possible configurations are:

|              | Timer3      | Timer1       |
|--------------|-------------|--------------|
| one speaker  | C4,C5 or C6 |              |
| one speaker  |             | B4, B5 or B7 |
| two speakers | C4,C5 or C6 | B4, B5 or B7 |

Currently there is only one/default driver for AVR based boards, which is automatically configured to:

```make
AUDIO_DRIVER = pwm_hardware
```


## ARM {#arm}

For Arm based boards, QMK depends on ChibiOS - hence any MCU supported by the later is likely usable, as long as certain hardware peripherals are available.

Supported wiring configurations, with their ChibiOS/MCU peripheral requirement are listed below;
piezo speakers are marked with :one: for the first/primary and :two: for the secondary.

  | driver       | GPTD6<br>Tim6                            | GPTD7<br>Tim7          | GPTD8<br>Tim8 | PWMD1<sup>1</sup><br>Tim1_Ch1 |
  |--------------|------------------------------------------|------------------------|---------------|-------------------------------|
  | dac_basic    | A4+DACD1 = :one:                         | A5+DACD2 = :one:       | state         |                               |
  |              | A4+DACD1 = :one: + Gnd                   | A5+DACD2 = :two: + Gnd | state         |                               |
  |              | A4+DACD1 = :two: + Gnd                   | A5+DACD2 = :one: + Gnd | state         |                               |
  |              | A4+DACD1 = :one: + Gnd                   |                        | state         |                               |
  |              |                                          | A5+DACD2 = :one: + Gnd | state         |                               |
  | dac_additive | A4+DACD1 = :one: + Gnd                   |                        |               |                               |
  |              | A5+DACD2 = :one: + Gnd                   |                        |               |                               |
  |              | A4+DACD1 + A5+DACD2 = :one: <sup>2</sup> |                        |               |                               |
  | pwm_software | state-update                             |                        |               | any = :one:                   |
  | pwm hardware | state-update                             |                        |               | A8 = :one: <sup>3</sup>       |


<sup>1</sup>: the routing and alternate functions for PWM differ sometimes between STM32 MCUs, if in doubt consult the data-sheet  
<sup>2</sup>: one piezo connected to A4 and A5, with AUDIO_PIN_ALT_AS_NEGATIVE set  
<sup>3</sup>: TIM1_CH1 = A8 on STM32F103C8, other combinations are possible, see Data-sheet. configured with: AUDIO_PWM_DRIVER and AUDIO_PWM_CHANNEL



### DAC basic {#dac-basic}

The default driver for ARM boards, in absence of an overriding configuration.
This driver needs one Timer per enabled/used DAC channel, to trigger conversion; and a third timer to trigger state updates with the audio-core.

Additionally, in the board config, you'll want to make changes to enable the DACs, GPT for Timers 6, 7 and 8:

::: code-group
```c [halconf.h]
#pragma once

#define HAL_USE_DAC TRUE // [!code focus]
#define HAL_USE_GPT TRUE // [!code focus]

#include_next <halconf.h>
```
```c [mcuconf.h]
#pragma once

#include_next <mcuconf.h>

#undef STM32_DAC_USE_DAC1_CH1 // [!code focus]
#define STM32_DAC_USE_DAC1_CH1 TRUE // [!code focus]
#undef STM32_DAC_USE_DAC1_CH2 // [!code focus]
#define STM32_DAC_USE_DAC1_CH2 TRUE // [!code focus]
#undef STM32_GPT_USE_TIM6 // [!code focus]
#define STM32_GPT_USE_TIM6 TRUE // [!code focus]
#undef STM32_GPT_USE_TIM7 // [!code focus]
#define STM32_GPT_USE_TIM7 TRUE // [!code focus]
#undef STM32_GPT_USE_TIM8 // [!code focus]
#define STM32_GPT_USE_TIM8 TRUE // [!code focus]
```
:::

::: tip
Note: DAC1 (A4) uses TIM6, DAC2 (A5) uses TIM7, and the audio state timer uses TIM8 (configurable). 
:::

You can also change the timer used for the overall audio state by defining the driver.  For instance: 

```c
#define AUDIO_STATE_TIMER GPTD9
```

### DAC additive {#dac-additive}

only needs one timer (GPTD6, Tim6) to trigger the DAC unit to do a conversion; the audio state updates are in turn triggered during the DAC callback.

Additionally, in the board config, you'll want to make changes to enable the DACs, GPT for Timer 6:

::: code-group
```c [halconf.h]
#pragma once

#define HAL_USE_DAC TRUE // [!code focus]
#define HAL_USE_GPT TRUE // [!code focus]

#include_next <halconf.h>
```
```c [mcuconf.h]
#pragma once

#include_next <mcuconf.h>

#undef STM32_DAC_USE_DAC1_CH1 // [!code focus]
#define STM32_DAC_USE_DAC1_CH1 TRUE // [!code focus]
#undef STM32_DAC_USE_DAC1_CH2 // [!code focus]
#define STM32_DAC_USE_DAC1_CH2 TRUE // [!code focus]
#undef STM32_GPT_USE_TIM6 // [!code focus]
#define STM32_GPT_USE_TIM6 TRUE // [!code focus]
```
:::

### DAC Config

| Define                           | Defaults                   | Description                                                                                                                                                           |
| -------------------------------- | -------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `AUDIO_DAC_SAMPLE_MAX`           | `4095U`                    | Highest value allowed. Lower value means lower volume. And 4095U is the upper limit, since this is limited to a 12 bit value. Only effects non-pregenerated samples.  |
| `AUDIO_DAC_OFF_VALUE`            | `AUDIO_DAC_SAMPLE_MAX / 2` | The value of the DAC when not playing anything. Some setups may require a high (`AUDIO_DAC_SAMPLE_MAX`) or low (`0`) value here.                                      |
| `AUDIO_MAX_SIMULTANEOUS_TONES`   | __see next table__         | The number of tones that can be played simultaneously.  A value that is too high may freeze the controller or glitch out when too many tones are being played.        |
| `AUDIO_DAC_SAMPLE_RATE`          | __see next table__         | Effective bit rate of the DAC (in hertz), higher limits simultaneous tones, and lower sacrifices quality.                                                             |
| `AUDIO_DAC_BUFFER_SIZE`          | __see next table__         | Number of samples generated every refill. Too few may cause excessive CPU load; too many may cause freezes, RAM or flash exhaustion or lags during matrix scanning.   |

There are a number of predefined quality settings that you can use, with "sane minimum" being the default.  You can use custom values by simply defining the sample rate, number of simultaneous tones and buffer size, instead of using one of the listed presets.

| Define                            | Sample Rate | Simultaneous tones  | Buffer size |
| --------------------------------- | ----------- | ------------------- | ----------- |
| `AUDIO_DAC_QUALITY_VERY_LOW`      | `11025U`    | `8`                 | `64U`       |
| `AUDIO_DAC_QUALITY_LOW`           | `22050U`    | `4`                 | `128U`      |
| `AUDIO_DAC_QUALITY_HIGH`          | `44100U`    | `2`                 | `256U`      |
| `AUDIO_DAC_QUALITY_VERY_HIGH`     | `88200U`    | `1`                 | `256U`      |
| `AUDIO_DAC_QUALITY_SANE_MINIMUM`  | `16384U`    | `8`                 | `64U`       |

#### Notes on buffer size {#buffer-size}

By default, the buffer size attempts to keep to these constraints:

* The interval between buffer refills can't be too short, since the microcontroller would then only be servicing buffer refills and would freeze up.
* On the additive driver, the interval between buffer refills can't be too long, since matrix scanning would suffer lengthy pauses every so often, which would delay key presses or releases or lose some short taps altogether.
* The interval between buffer refills is kept to a minimum, which allows notes to stop as soon as possible after they should.
* For greater compatibility, the buffer size should be a power of 2.
* The buffer size being too large causes resource exhaustion leading to build failures or freezing at runtime: RAM usage (on the additive driver) or flash usage (on the basic driver).

You can lower the buffer size if you need a bit more space in your firmware, or raise it if your keyboard freezes up.


```c
        /* zero crossing (or approach, whereas zero == DAC_OFF_VALUE, which can be configured to anything from 0 to DAC_SAMPLE_MAX)
         * ============================*=*========================== AUDIO_DAC_SAMPLE_MAX
         *                          *       *
         *                        *           *
         * ---------------------------------------------------------
         *                     *                 *                  } AUDIO_DAC_SAMPLE_MAX/100
         * --------------------------------------------------------- AUDIO_DAC_OFF_VALUE
         *                  *                       *               } AUDIO_DAC_SAMPLE_MAX/100
         * ---------------------------------------------------------
         *               *
         * *           *
         *   *       *
         * =====*=*================================================= 0x0
         */
```


### PWM hardware {#pwm-hardware}

This driver uses the ChibiOS-PWM system to produce a square-wave on specific output pins that are connected to the PWM hardware.
The hardware directly toggles the pin via its alternate function. See your MCU's data-sheet for which pin can be driven by what timer - looking for TIMx_CHy and the corresponding alternate function.

A configuration example for the STM32F103C8 would be:

::: code-group
```c [halconf.h]
#pragma once

#define HAL_USE_PWM TRUE // [!code focus]
#define HAL_USE_PAL TRUE // [!code focus]

#include_next <halconf.h>
```
```c [mcuconf.h]
#pragma once

#include_next <mcuconf.h>

#undef STM32_PWM_USE_TIM1 // [!code focus]
#define STM32_PWM_USE_TIM1 TRUE // [!code focus]
```
:::

If we now target pin A8, looking through the data-sheet of the STM32F103C8, for the timers and alternate functions
- TIM1_CH1 = PA8 <- alternate0
- TIM1_CH2 = PA9
- TIM1_CH3 = PA10
- TIM1_CH4 = PA11

with all this information, the configuration would contain these lines:
```c
//config.h:
#define AUDIO_PIN A8
#define AUDIO_PWM_DRIVER PWMD1
#define AUDIO_PWM_CHANNEL 1
```

ChibiOS uses GPIOv1 for the F103, which only knows of one alternate function.
On 'larger' STM32s, GPIOv2 or GPIOv3 are used; with them it is also necessary to configure `AUDIO_PWM_PAL_MODE` to the correct alternate function for the selected pin, timer and timer-channel.

You can also use the Complementary output (`TIMx_CHyN`) for PWM on supported controllers.  To enable this functionality, you will need to make the following changes:
```c
// config.h:
#define AUDIO_PWM_COMPLEMENTARY_OUTPUT
```

### PWM software {#pwm-software}

This driver uses the PWM callbacks from PWMD1 with TIM1_CH1 to toggle the selected AUDIO_PIN in software.
During the same callback, with AUDIO_PIN_ALT_AS_NEGATIVE set, the AUDIO_PIN_ALT is toggled inversely to AUDIO_PIN. This is useful for setups that drive a piezo from two pins (instead of one and Gnd).

You can also change the timer used for software PWM by defining the driver.  For instance: 

```c
#define AUDIO_STATE_TIMER GPTD8
```


### Testing Notes {#testing-notes}

While not an exhaustive list, the following table provides the scenarios that have been partially validated:

|                          |     DAC basic      |    DAC additive    |    PWM hardware    |    PWM software    |
| ------------------------ | ------------------ | ------------------ | ------------------ | ------------------ |
| Atmega32U4               | :o:                | :o:                | :heavy_check_mark: | :o:                |
| RP2040                   | :x:                | :x:                | :heavy_check_mark: | ?                  |
| STM32F103C8 (bluepill)   | :x:                | :x:                | :heavy_check_mark: | :heavy_check_mark: |
| STM32F303CCT6 (proton-c) | :heavy_check_mark: | :heavy_check_mark: | ?                  | :heavy_check_mark: |
| STM32F405VG              | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: |
| L0xx                     | :x: (no Tim8)      | ?                  | ?                  | ?                  |

:heavy_check_mark: : works and was tested  
:o: : does not apply  
:x: : not supported by MCU

*Other supported ChibiOS boards and/or pins may function, it will be highly chip and configuration dependent.*
