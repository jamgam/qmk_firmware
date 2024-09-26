// Copyright 2023 Adam Tombleson (@rekarnar)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_keycodes {  TO_WIN = SAFE_RANGE, TO_MAC,PREV_WORD, NEXT_WORD, DELETE_WORD, SELECT_LINE, MOD };

enum layer_names {
    _BASE,
    _SYM,
    _NUM,
    _SHORTCUTS,
};

enum combos {
    DELETE_WORD_COMBO,
    OPEN_APPLICATION_ONE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌───────────────┬───┬──────┬──────┬───────────────┬─────┐   ┌───────────────┬────────────────┬──────┬────┬───┬──────┐
//    │ LT(_SYM, tab) │ q │  w   │  f   │       p       │  b  │   │       j       │       l        │  u   │ y  │ ; │  \   │
//    ├───────────────┼───┼──────┼──────┼───────────────┼─────┤   ├───────────────┼────────────────┼──────┼────┼───┼──────┤
//    │ LT(_NUM, esc) │ a │  r   │  s   │       t       │  g  │   │       m       │       n        │  e   │ i  │ o │  '   │
//    ├───────────────┼───┼──────┼──────┼───────────────┼─────┤   ├───────────────┼────────────────┼──────┼────┼───┼──────┤
//    │     rctl      │ z │  x   │  c   │       d       │  v  │   │       k       │       h        │  ,   │ .  │ / │ lgui │
//    └───────────────┴───┼──────┼──────┼───────────────┴─────┘   └───────────────┴────────────────┼──────┼────┼───┴──────┘
//                        │ left │ rght │                                                          │ down │ up │
//                        └──────┼──────┼───────────────┬─────┐   ┌───────────────┬────────────────┼──────┼────┘
//                               │ lalt │ OSM(MOD_LSFT) │ MOD │   │ LT(_NUM, ent) │ LT(_SYM, bspc) │ spc  │
//                               └──────┴───────────────┴─────┘   └───────────────┴────────────────┴──────┘
[_BASE] = LAYOUT(
  LT(_SYM, KC_TAB) , KC_Q , KC_W    , KC_F     , KC_P          , KC_B ,     KC_J             , KC_L              , KC_U    , KC_Y   , KC_SCLN , KC_BSLS,
  LT(_NUM, KC_ESC) , KC_A , KC_R    , KC_S     , KC_T          , KC_G ,     KC_M             , KC_N              , KC_E    , KC_I   , KC_O    , KC_QUOT,
  KC_RCTL          , KC_Z , KC_X    , KC_C     , KC_D          , KC_V ,     KC_K             , KC_H              , KC_COMM , KC_DOT , KC_SLSH , KC_LGUI,
                            KC_LEFT , KC_RIGHT ,                                                                   KC_DOWN , KC_UP                     ,
                                      KC_LALT  , OSM(MOD_LSFT) , MOD  ,     LT(_NUM, KC_ENT) , LT(_SYM, KC_BSPC) , KC_SPC
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

//    ┌─────┬─────┬─────┬─────┬─────┬─────────┐   ┌─────┬─────┬─────┬───┬─────┬─────┐
//    │     │ f12 │ f7  │ f8  │ f9  │ EE_CLR  │   │     │  7  │  8  │ 9 │  *  │  /  │
//    ├─────┼─────┼─────┼─────┼─────┼─────────┤   ├─────┼─────┼─────┼───┼─────┼─────┤
//    │     │ f11 │ f4  │ f5  │ f6  │         │   │     │  4  │  5  │ 6 │     │  -  │
//    ├─────┼─────┼─────┼─────┼─────┼─────────┤   ├─────┼─────┼─────┼───┼─────┼─────┤
//    │     │ f10 │ f1  │ f2  │ f3  │ QK_BOOT │   │  0  │  1  │  2  │ 3 │  +  │     │
//    └─────┴─────┼─────┼─────┼─────┴─────────┘   └─────┴─────┼─────┼───┼─────┴─────┘
//                │     │     │                               │  0  │ . │
//                └─────┼─────┼─────┬─────────┐   ┌─────┬─────┼─────┼───┘
//                      │     │     │         │   │     │     │     │
//                      └─────┴─────┴─────────┘   └─────┴─────┴─────┘
[_NUM] = LAYOUT(
  KC_TRNS , KC_F12 , KC_F7   , KC_F8   , KC_F9   , EE_CLR  ,     KC_TRNS , KC_7    , KC_8    , KC_9   , KC_ASTR , KC_SLASH,
  KC_TRNS , KC_F11 , KC_F4   , KC_F5   , KC_F6   , KC_TRNS ,     KC_TRNS , KC_4    , KC_5    , KC_6   , KC_TRNS , KC_MINS ,
  KC_TRNS , KC_F10 , KC_F1   , KC_F2   , KC_F3   , QK_BOOT ,     KC_0    , KC_1    , KC_2    , KC_3   , KC_PLUS , KC_TRNS ,
                     KC_TRNS , KC_TRNS ,                                             KC_0    , KC_DOT                     ,
                               KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS
),

//    ┌─────┬─────┬─────┬─────┬─────┬─────────┐   ┌─────┬─────┬─────┬───┬─────┬─────┐
//    │     │ f12 │ f7  │ f8  │ f9  │ EE_CLR  │   │     │  7  │  8  │ 9 │  *  │  /  │
//    ├─────┼─────┼─────┼─────┼─────┼─────────┤   ├─────┼─────┼─────┼───┼─────┼─────┤
//    │     │ f11 │ f4  │ f5  │ f6  │         │   │     │  4  │  5  │ 6 │     │  -  │
//    ├─────┼─────┼─────┼─────┼─────┼─────────┤   ├─────┼─────┼─────┼───┼─────┼─────┤
//    │     │ f10 │ f1  │ f2  │ f3  │ QK_BOOT │   │  0  │  1  │  2  │ 3 │  +  │     │
//    └─────┴─────┼─────┼─────┼─────┴─────────┘   └─────┴─────┼─────┼───┼─────┴─────┘
//                │     │     │                               │  0  │ . │
//                └─────┼─────┼─────┬─────────┐   ┌─────┬─────┼─────┼───┘
//                      │     │     │         │   │     │     │     │
//                      └─────┴─────┴─────────┘   └─────┴─────┴─────┘
[_SHORTCUTS] = LAYOUT(
  KC_TRNS , KC_F12 , KC_F7   , KC_F8   , KC_F9   , EE_CLR  ,     KC_TRNS , KC_7    , KC_8    , KC_9   , KC_ASTR , KC_SLASH,
  KC_TRNS , KC_F11 , KC_F4   , KC_F5   , KC_F6   , KC_TRNS ,     KC_TRNS , KC_4    , KC_5    , KC_6   , KC_TRNS , KC_MINS ,
  KC_TRNS , KC_F10 , KC_F1   , KC_F2   , KC_F3   , QK_BOOT ,     KC_0    , KC_1    , KC_2    , KC_3   , KC_PLUS , KC_TRNS ,
                     KC_TRNS , KC_TRNS ,                                             KC_0    , KC_DOT                     ,
                               KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS
)
};

bool is_mac(void) {
    return detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS;
}

void delete_word(bool pressed) {
    const uint16_t kc = is_mac() ? LALT(KC_BSPC) : LCTL(KC_BSPC);
    if (pressed) {
        register_code16(kc);
    } else {
        unregister_code16(kc);
    }
}

enum { LEFT = 0, RIGHT = 1 };
void adjacent_word(bool pressed, uint8_t direction) {
    const uint8_t  kc     = direction == LEFT ? KC_LEFT : KC_RIGHT;
    const uint16_t code16 = is_mac() ? LALT(kc) : LCTL(kc);
    if (pressed) {
        register_code16(code16);
    } else {
        unregister_code16(code16);
    }
}

void select_line(bool pressed) {
    if (is_mac()) {
        tap_code16(G(KC_LEFT));
        tap_code16(S(G(KC_RIGHT)));
    } else {
        tap_code16(KC_HOME);
        tap_code16(S(KC_END));
    }
}

void main_modifier(bool pressed) {
    const uint16_t code16 = is_mac() ? KC_LGUI : KC_LCTL;
    if (pressed) {
        register_code(code16);
    } else {
        unregister_code(code16);
    }
}

// COMBO DEFS
const uint16_t PROGMEM delete_word_combo[]    = {LT(_SYM, KC_BSPC), KC_SPC, COMBO_END};
combo_t                key_combos[]           = {
    [DELETE_WORD_COMBO]    = COMBO_ACTION(delete_word_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case DELETE_WORD_COMBO:
            delete_word(pressed);
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

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
	&delete_key_override
};


