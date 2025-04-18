#pragma once

#define OS_DETECTION_KEYBOARD_RESET
#define OS_DETECTION_DEBOUNCE 200
#define ONESHOT_TIMEOUT 1000
#define TAPPING_TERM 140
#define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS

#define EE_HANDS // Store which side I am in EEPROM
/* Reset */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
