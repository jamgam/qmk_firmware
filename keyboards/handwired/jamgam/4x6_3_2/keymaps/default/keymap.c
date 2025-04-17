// Copyright 2024 Adam Tombleson (@rekarnar)
// SPDX-License-Identifier: GPL-1.0-or-later
#include <stdint.h>
#include "action.h"
#include "keycodes.h"
#include "keymap_us.h"
#include "process_combo.h"
#include QMK_KEYBOARD_H
#include ".build/obj_handwired_jamgam_4x6_3_2_default/src/default_keyboard.h"

enum custom_keycodes { PREV_WORD = SAFE_RANGE, NEXT_WORD, SELECT_LINE, MOD };

enum layer_names {
    _BASE,
    _GAMING,
    _SYM,
    _NUM,
    _SHORTCUTS,
};

enum combos {
    DELETE_COMBO,
    DELETE_WORD_COMBO,
    SHORTCUTS_COMBO,
    OPEN_APPLICATION_ONE,
    GAMING_COMBO
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌───────────────┬───┬──────┬──────┬───────────────┬─────┐   ┌─────┬────────────────┬──────┬────┬───┬──────┐
//    │      tab      │ q │  w   │  f   │       p       │  b  │   │  j  │       l        │  u   │ y  │ ; │  \   │
//    ├───────────────┼───┼──────┼──────┼───────────────┼─────┤   ├─────┼────────────────┼──────┼────┼───┼──────┤
//    │ LT(_NUM, esc) │ a │  r   │  s   │       t       │  g  │   │  m  │       n        │  e   │ i  │ o │  '   │
//    ├───────────────┼───┼──────┼──────┼───────────────┼─────┤   ├─────┼────────────────┼──────┼────┼───┼──────┤
//    │     rctl      │ z │  x   │  c   │       d       │  v  │   │  k  │       h        │  ,   │ .  │ / │ lgui │
//    └───────────────┴───┼──────┼──────┼───────────────┴─────┘   └─────┴────────────────┼──────┼────┼───┴──────┘
//                        │ left │ rght │                                                │ down │ up │
//                        └──────┼──────┼───────────────┬─────┐   ┌─────┬────────────────┼──────┼────┘
//                               │ lalt │ OSM(MOD_LSFT) │ MOD │   │ ent │ LT(_SYM, bspc) │ spc  │
//                               └──────┴───────────────┴─────┘   └─────┴────────────────┴──────┘
[_BASE] = LAYOUT(
  KC_TAB           , KC_Q , KC_W    , KC_F     , KC_P          , KC_B ,     KC_J   , KC_L              , KC_U    , KC_Y   , KC_SCLN , KC_BSLS,
  LT(_NUM, KC_ESC) , KC_A , KC_R    , KC_S     , KC_T          , KC_G ,     KC_M   , KC_N              , KC_E    , KC_I   , KC_O    , KC_QUOT,
  KC_RCTL          , KC_Z , KC_X    , KC_C     , KC_D          , KC_V ,     KC_K   , KC_H              , KC_COMM , KC_DOT , KC_SLSH , KC_LGUI,
                            KC_LEFT , KC_RIGHT ,                                                         KC_DOWN , KC_UP                     ,
                                      KC_LALT  , OSM(MOD_LSFT) , MOD  ,     KC_ENT , LT(_SYM, KC_BSPC) , KC_SPC
),

//    ┌─────┬──────┬──────┬─────┬─────┬───┐   ┌─────┬───────────┬─────────────┬──────┬───┬───┐
//    │ tab │  t   │  q   │  w  │  e  │ r │   │  t  │     y     │      u      │  i   │ o │ p │
//    ├─────┼──────┼──────┼─────┼─────┼───┤   ├─────┼───────────┼─────────────┼──────┼───┼───┤
//    │  m  │ lsft │  a   │  s  │  d  │ f │   │  g  │     h     │      j      │  k   │ l │ ; │
//    ├─────┼──────┼──────┼─────┼─────┼───┤   ├─────┼───────────┼─────────────┼──────┼───┼───┤
//    │  3  │ lctl │  z   │  x  │  c  │ v │   │  b  │     n     │      m      │  ,   │ . │ / │
//    └─────┴──────┼──────┼─────┼─────┴───┘   └─────┴───────────┼─────────────┼──────┼───┴───┘
//                 │ lalt │ esc │                               │     up      │ rght │
//                 └──────┼─────┼─────┬───┐   ┌─────┬───────────┼─────────────┼──────┘
//                        │  1  │ spc │ 2 │   │ ent │ DF(_BASE) │ LT(_NUM, 4) │
//                        └─────┴─────┴───┘   └─────┴───────────┴─────────────┘
[_GAMING] = LAYOUT(
  KC_TAB , KC_T    , KC_Q    , KC_W   , KC_E     , KC_R ,     KC_T   , KC_Y      , KC_U           , KC_I    , KC_O   , KC_P   ,
  KC_M   , KC_LSFT , KC_A    , KC_S   , KC_D     , KC_F ,     KC_G   , KC_H      , KC_J           , KC_K    , KC_L   , KC_SCLN,
  KC_3   , KC_LCTL , KC_Z    , KC_X   , KC_C     , KC_V ,     KC_B   , KC_N      , KC_M           , KC_COMM , KC_DOT , KC_SLSH,
                     KC_LALT , KC_ESC ,                                            KC_UP          , KC_RGHT                   ,
                               KC_1   , KC_SPACE , KC_2 ,     KC_ENT , DF(_BASE) , LT(_NUM, KC_4)
),

//    ┌─────────┬───┬───────────┬───────────┬─────┬─────┐   ┌──────┬─────┬──────┬────┬───┬─────────┐
//    │  volu   │ { │     (     │     )     │  }  │ ins │   │ pgup │  ~  │  _   │ `  │ : │  mute   │
//    ├─────────┼───┼───────────┼───────────┼─────┼─────┤   ├──────┼─────┼──────┼────┼───┼─────────┤
//    │  vold   │ ! │     @     │     #     │  $  │  %  │   │  ^   │  &  │  *   │ =  │ - │    "    │
//    ├─────────┼───┼───────────┼───────────┼─────┼─────┤   ├──────┼─────┼──────┼────┼───┼─────────┤
//    │ LGUI(`) │ < │     [     │     ]     │  >  │ del │   │ pgdn │  \  │  |   │ +  │ ? │ QK_BOOT │
//    └─────────┴───┼───────────┼───────────┼─────┴─────┘   └──────┴─────┼──────┼────┼───┴─────────┘
//                  │ PREV_WORD │ NEXT_WORD │                            │ down │ up │
//                  └───────────┼───────────┼─────┬─────┐   ┌──────┬─────┼──────┼────┘
//                              │           │     │     │   │      │     │      │
//                              └───────────┴─────┴─────┘   └──────┴─────┴──────┘
[_SYM] = LAYOUT(
  KC_VOLU      , KC_LCBR , KC_LPRN   , KC_RPRN   , KC_RCBR , KC_INS  ,     KC_PGUP , KC_TILDE , KC_UNDS , KC_GRV  , KC_COLN , KC_MUTE,
  KC_VOLD      , KC_EXLM , KC_AT     , KC_HASH   , KC_DLR  , KC_PERC ,     KC_CIRC , KC_AMPR  , KC_ASTR , KC_EQL  , KC_MINS , KC_DQUO,
  LGUI(KC_GRV) , KC_LT   , KC_LBRC   , KC_RBRC   , KC_GT   , KC_DEL  ,     KC_PGDN , KC_BSLS  , KC_PIPE , KC_PLUS , KC_QUES , QK_BOOT,
                           PREV_WORD , NEXT_WORD ,                                              KC_DOWN , KC_UP                      ,
                                       KC_TRNS   , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_TRNS  , KC_TRNS
),

//    ┌─────┬─────┬─────────────┬─────────────┬─────┬───────────┐   ┌───────────┬─────┬─────┬───┬───┬─────┐
//    │     │ f12 │     f7      │     f8      │ f9  │  EE_CLR   │   │ caps_LOCK │  7  │  8  │ 9 │ * │  /  │
//    ├─────┼─────┼─────────────┼─────────────┼─────┼───────────┤   ├───────────┼─────┼─────┼───┼───┼─────┤
//    │     │ f11 │     f4      │     f5      │ f6  │ QK_REBOOT │   │           │  4  │  5  │ 6 │ - │     │
//    ├─────┼─────┼─────────────┼─────────────┼─────┼───────────┤   ├───────────┼─────┼─────┼───┼───┼─────┤
//    │     │ f10 │     f1      │     f2      │ f3  │  QK_BOOT  │   │     0     │  1  │  2  │ 3 │ + │  ,  │
//    └─────┴─────┼─────────────┼─────────────┼─────┴───────────┘   └───────────┴─────┼─────┼───┼───┴─────┘
//                │ TO(_GAMING) │ TO(_GAMING) │                                       │  0  │ . │
//                └─────────────┼─────────────┼─────┬───────────┐   ┌───────────┬─────┼─────┼───┘
//                              │             │     │           │   │           │     │     │
//                              └─────────────┴─────┴───────────┘   └───────────┴─────┴─────┘
[_NUM] = LAYOUT(
  KC_TRNS , KC_F12 , KC_F7       , KC_F8       , KC_F9   , EE_CLR    ,     KC_CAPS_LOCK , KC_7    , KC_8    , KC_9   , KC_ASTR , KC_SLASH,
  KC_TRNS , KC_F11 , KC_F4       , KC_F5       , KC_F6   , QK_REBOOT ,     KC_TRNS      , KC_4    , KC_5    , KC_6   , KC_MINS , KC_TRNS ,
  KC_TRNS , KC_F10 , KC_F1       , KC_F2       , KC_F3   , QK_BOOT   ,     KC_0         , KC_1    , KC_2    , KC_3   , KC_PLUS , KC_COMMA,
                     TO(_GAMING) , TO(_GAMING) ,                                                    KC_0    , KC_DOT                     ,
                                   KC_TRNS     , KC_TRNS , KC_TRNS   ,     KC_TRNS      , KC_TRNS , KC_TRNS
),

//    ┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
//    │     │     │     │     │     │     │   │     │     │     │     │     │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │  1  │  2  │  3  │  4  │  5  │   │     │     │     │     │     │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │  6  │  7  │     │     │     │   │     │     │     │     │     │     │
//    └─────┴─────┼─────┼─────┼─────┴─────┘   └─────┴─────┼─────┼─────┼─────┴─────┘
//                │     │     │                           │     │     │
//                └─────┼─────┼─────┬─────┐   ┌─────┬─────┼─────┼─────┘
//                      │     │     │     │   │     │     │     │
//                      └─────┴─────┴─────┘   └─────┴─────┴─────┘
[_SHORTCUTS] = LAYOUT(
  KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
  KC_TRNS , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
  KC_TRNS , KC_6    , KC_7    , KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
                      KC_TRNS , KC_TRNS ,                                             KC_TRNS , KC_TRNS                    ,
                                KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS
)
};

static bool is_mac(void) {
    return detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS;
}

static void delete_word(bool pressed) {
    const uint16_t kc = is_mac() ? LALT(KC_BSPC) : LCTL(KC_BSPC);
    if (pressed) {
        register_code16(kc);
    } else {
        unregister_code16(kc);
    }
}

enum { LEFT = 0, RIGHT = 1 };
static void adjacent_word(bool pressed, uint8_t direction) {
    const uint8_t  kc     = direction == LEFT ? KC_LEFT : KC_RIGHT;
    const uint16_t code16 = is_mac() ? LALT(kc) : LCTL(kc);
    if (pressed) {
        register_code16(code16);
    } else {
        unregister_code16(code16);
    }
}

static void select_line(bool pressed) {
    if (is_mac()) {
        tap_code16(G(KC_LEFT));
        tap_code16(S(G(KC_RIGHT)));
    } else {
        tap_code16(KC_HOME);
        tap_code16(S(KC_END));
    }
}

static void main_modifier(bool pressed) {
    const uint16_t code16 = is_mac() ? KC_LGUI : KC_LCTL;
    if (pressed) {
        register_code(code16);
    } else {
        unregister_code(code16);
    }
}

// COMBO DEFS
combo_t                key_combos[]        = {
    [DELETE_WORD_COMBO] = COMBO_ACTION(((uint16_t[]){LT(_SYM, KC_BSPC), KC_SPC, COMBO_END})),
    [SHORTCUTS_COMBO]   = COMBO_ACTION(((uint16_t[]){KC_RCTL, MOD, COMBO_END})),
    COMBO(((uint16_t[]){KC_D, KC_V, COMBO_END}), KC_DEL),
    COMBO(((uint16_t[]){KC_B, KC_V, COMBO_END}), DF(_GAMING)),
    COMBO(((uint16_t[]){KC_P, KC_T, COMBO_END}), KC_HOME),
    COMBO(((uint16_t[]){KC_T, KC_D, COMBO_END}), KC_END),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case DELETE_WORD_COMBO:
            delete_word(pressed);
            break;
        case SHORTCUTS_COMBO:
            if (pressed) {
                register_code(KC_LGUI);
                is_mac() ? register_code(KC_LCTL) : layer_on(_SHORTCUTS);
            } else {
                unregister_code(KC_LGUI);
                is_mac() ? unregister_code(KC_LCTL) : layer_off(_SHORTCUTS);
            }
            break;
        default:
            break;
    }
}

// CUSTOM KEY HANDLERS
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    const bool pressed = record->event.pressed;
    switch (keycode) {
        case PREV_WORD:
            adjacent_word(pressed, LEFT);
            return false;
        case NEXT_WORD:
            adjacent_word(pressed, RIGHT);
            return false;
        case SELECT_LINE:
            select_line(pressed);
            return false;
        case MOD:
            main_modifier(pressed);
            return true;
        default:
            return true;
    }
}

