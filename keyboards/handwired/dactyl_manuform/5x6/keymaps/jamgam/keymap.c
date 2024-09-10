#include <stdbool.h>
#include <stdint.h>
#include "action.h"
#include "keycodes.h"
#include "quantum.h"
#include QMK_KEYBOARD_H

// layers for windows
#define _WIN 0
#define _MAC 1
#define _SYMBOLS 2
#define _ARROWS 3

// Custom keycodes for layer switching and dynamic symbols
enum custom_keycodes { TO_WIN = SAFE_RANGE, TO_MAC, PREV_WORD, NEXT_WORD, DELETE_WORD, SELECT_LINE };

enum combos {
    DELETE_WORD_COMBO,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌──────┬───┬──────┬──────┬───────────────┬───────────────┐                   ┌────────┬────────┬──────┬────┬───┬──────┐
//    │ lsft │ 1 │  2   │  3   │       4       │       5       │                   │   6    │   7    │  8   │ 9  │ 0 │ home │
//    ├──────┼───┼──────┼──────┼───────────────┼───────────────┤                   ├────────┼────────┼──────┼────┼───┼──────┤
//    │ tab  │ q │  w   │  f   │       p       │       b       │                   │   j    │   l    │  u   │ y  │ ; │  \   │
//    ├──────┼───┼──────┼──────┼───────────────┼───────────────┤                   ├────────┼────────┼──────┼────┼───┼──────┤
//    │ esc  │ a │  r   │  s   │       t       │       g       │                   │   m    │   n    │  e   │ i  │ o │  '   │
//    ├──────┼───┼──────┼──────┼───────────────┼───────────────┤                   ├────────┼────────┼──────┼────┼───┼──────┤
//    │ lctl │ z │  x   │  c   │       d       │       v       │                   │   k    │   h    │  ,   │ .  │ / │ end  │
//    └──────┴───┼──────┼──────┼───────────────┴───────────────┘                   └────────┴────────┼──────┼────┼───┴──────┘
//               │ left │ rght │                                                                     │ down │ up │           
//               └──────┴──────┼───────────────┬───────────────┐                   ┌────────┬────────┼──────┴────┘           
//                             │ OSL(_SYMBOLS) │ OSM(MOD_LSFT) │                   │  bspc  │  spc   │                       
//                             ├───────────────┼───────────────┤                   ├────────┼────────┤                       
//                             │     lalt      │     lctl      │                   │ OSL(3) │  ent   │                       
//                             ├───────────────┼───────────────┤                   ├────────┼────────┤                       
//                             │     lgui      │    OSL(3)     │                   │ TO_WIN │ TO_MAC │                       
//                             └───────────────┴───────────────┘                   └────────┴────────┘                       
[_WIN] = LAYOUT_5x6(
  KC_LSFT , KC_1 , KC_2    , KC_3     , KC_4          , KC_5          ,                     KC_6    , KC_7   , KC_8    , KC_9   , KC_0    , KC_HOME,
  KC_TAB  , KC_Q , KC_W    , KC_F     , KC_P          , KC_B          ,                     KC_J    , KC_L   , KC_U    , KC_Y   , KC_SCLN , KC_BSLS,
  KC_ESC  , KC_A , KC_R    , KC_S     , KC_T          , KC_G          ,                     KC_M    , KC_N   , KC_E    , KC_I   , KC_O    , KC_QUOT,
  KC_LCTL , KC_Z , KC_X    , KC_C     , KC_D          , KC_V          ,                     KC_K    , KC_H   , KC_COMM , KC_DOT , KC_SLSH , KC_END ,
                   KC_LEFT , KC_RIGHT ,                                                                        KC_DOWN , KC_UP                     ,
                                        OSL(_SYMBOLS) , OSM(MOD_LSFT) ,                     KC_BSPC , KC_SPC                                       ,
                                        KC_LALT       , KC_LCTL       ,                     OSL(3)  , KC_ENT                                       ,
                                        KC_LGUI       , OSL(3)        ,                     TO_WIN  , TO_MAC                                       
),

//    ┌──────┬───┬──────┬──────┬───────────────┬───────────────┐                   ┌────────┬────────┬──────┬────┬───┬──────┐
//    │ lsft │ 1 │  2   │  3   │       4       │       5       │                   │   6    │   7    │  8   │ 9  │ 0 │ home │
//    ├──────┼───┼──────┼──────┼───────────────┼───────────────┤                   ├────────┼────────┼──────┼────┼───┼──────┤
//    │ tab  │ q │  w   │  f   │       p       │       b       │                   │   j    │   l    │  u   │ y  │ ; │  \   │
//    ├──────┼───┼──────┼──────┼───────────────┼───────────────┤                   ├────────┼────────┼──────┼────┼───┼──────┤
//    │ esc  │ a │  r   │  s   │       t       │       g       │                   │   m    │   n    │  e   │ i  │ o │  '   │
//    ├──────┼───┼──────┼──────┼───────────────┼───────────────┤                   ├────────┼────────┼──────┼────┼───┼──────┤
//    │ lctl │ z │  x   │  c   │       d       │       v       │                   │   k    │   h    │  ,   │ .  │ / │ end  │
//    └──────┴───┼──────┼──────┼───────────────┴───────────────┘                   └────────┴────────┼──────┼────┼───┴──────┘
//               │ left │ rght │                                                                     │ down │ up │           
//               └──────┴──────┼───────────────┬───────────────┐                   ┌────────┬────────┼──────┴────┘           
//                             │ OSL(_SYMBOLS) │ OSM(MOD_LSFT) │                   │  bspc  │  spc   │                       
//                             ├───────────────┼───────────────┤                   ├────────┼────────┤                       
//                             │     lalt      │     lgui      │                   │ OSL(4) │  ent   │                       
//                             ├───────────────┼───────────────┤                   ├────────┼────────┤                       
//                             │     lctl      │    OSL(4)     │                   │ TO_WIN │ TO_MAC │                       
//                             └───────────────┴───────────────┘                   └────────┴────────┘                       
[_MAC] = LAYOUT_5x6(
  KC_LSFT , KC_1 , KC_2    , KC_3     , KC_4          , KC_5          ,                     KC_6    , KC_7   , KC_8    , KC_9   , KC_0    , KC_HOME,
  KC_TAB  , KC_Q , KC_W    , KC_F     , KC_P          , KC_B          ,                     KC_J    , KC_L   , KC_U    , KC_Y   , KC_SCLN , KC_BSLS,
  KC_ESC  , KC_A , KC_R    , KC_S     , KC_T          , KC_G          ,                     KC_M    , KC_N   , KC_E    , KC_I   , KC_O    , KC_QUOT,
  KC_LCTL , KC_Z , KC_X    , KC_C     , KC_D          , KC_V          ,                     KC_K    , KC_H   , KC_COMM , KC_DOT , KC_SLSH , KC_END ,
                   KC_LEFT , KC_RIGHT ,                                                                        KC_DOWN , KC_UP                     ,
                                        OSL(_SYMBOLS) , OSM(MOD_LSFT) ,                     KC_BSPC , KC_SPC                                       ,
                                        KC_LALT       , KC_LGUI       ,                     OSL(4)  , KC_ENT                                       ,
                                        KC_LCTL       , OSL(4)        ,                     TO_WIN  , TO_MAC                                       
),

//    ┌─────────┬────┬───────────┬───────────┬─────┬─────┐                   ┌─────────────┬────────┬──────┬────┬─────┬─────────┐
//    │   f12   │ f1 │    f2     │    f3     │ f4  │ f5  │                   │     f6      │   f7   │  f8  │ f9 │ f10 │   f11   │
//    ├─────────┼────┼───────────┼───────────┼─────┼─────┤                   ├─────────────┼────────┼──────┼────┼─────┼─────────┤
//    │  volu   │ {  │     (     │     )     │  }  │ ins │                   │    pgup     │   ~    │  _   │ `  │  :  │  mute   │
//    ├─────────┼────┼───────────┼───────────┼─────┼─────┤                   ├─────────────┼────────┼──────┼────┼─────┼─────────┤
//    │  vold   │ !  │     @     │     #     │  $  │  %  │                   │      ^      │   &    │  *   │ =  │  -  │    "    │
//    ├─────────┼────┼───────────┼───────────┼─────┼─────┤                   ├─────────────┼────────┼──────┼────┼─────┼─────────┤
//    │ QK_BOOT │ <  │     [     │     ]     │  >  │ del │                   │    pgdn     │   \    │  |   │ +  │  ?  │ LGUI(`) │
//    └─────────┴────┼───────────┼───────────┼─────┴─────┘                   └─────────────┴────────┼──────┼────┼─────┴─────────┘
//                   │ PREV_WORD │ NEXT_WORD │                                                      │ down │ up │                
//                   └───────────┴───────────┼─────┬─────┐                   ┌─────────────┬────────┼──────┴────┘                
//                                           │     │     │                   │             │        │                            
//                                           ├─────┼─────┤                   ├─────────────┼────────┤                            
//                                           │     │     │                   │ SELECT_LINE │        │                            
//                                           ├─────┼─────┤                   ├─────────────┼────────┤                            
//                                           │     │     │                   │   TO_WIN    │ TO_MAC │                            
//                                           └─────┴─────┘                   └─────────────┴────────┘                            
[_SYMBOLS] = LAYOUT_5x6(
  KC_F12  , KC_F1   , KC_F2     , KC_F3     , KC_F4   , KC_F5   ,                     KC_F6       , KC_F7    , KC_F8   , KC_F9   , KC_F10  , KC_F11      ,
  KC_VOLU , KC_LCBR , KC_LPRN   , KC_RPRN   , KC_RCBR , KC_INS  ,                     KC_PGUP     , KC_TILDE , KC_UNDS , KC_GRV  , KC_COLN , KC_MUTE     ,
  KC_VOLD , KC_EXLM , KC_AT     , KC_HASH   , KC_DLR  , KC_PERC ,                     KC_CIRC     , KC_AMPR  , KC_ASTR , KC_EQL  , KC_MINS , KC_DQUO     ,
  QK_BOOT , KC_LT   , KC_LBRC   , KC_RBRC   , KC_GT   , KC_DEL  ,                     KC_PGDN     , KC_BSLS  , KC_PIPE , KC_PLUS , KC_QUES , LGUI(KC_GRV),
                      PREV_WORD , NEXT_WORD ,                                                                  KC_DOWN , KC_UP                           ,
                                              KC_TRNS , KC_TRNS ,                     KC_TRNS     , KC_TRNS                                              ,
                                              KC_TRNS , KC_TRNS ,                     SELECT_LINE , KC_TRNS                                              ,
                                              KC_TRNS , KC_TRNS ,                     TO_WIN      , TO_MAC                                               
),

//    ┌─────────┬────┬───────────┬───────────┬─────┬─────┐                   ┌─────────────┬────────┬──────┬──────┬─────┬─────────┐
//    │   f12   │ f1 │    f2     │    f3     │ f4  │ f5  │                   │     f6      │   f7   │  f8  │  f9  │ f10 │   f11   │
//    ├─────────┼────┼───────────┼───────────┼─────┼─────┤                   ├─────────────┼────────┼──────┼──────┼─────┼─────────┤
//    │  volu   │ {  │     (     │     )     │  }  │ ins │                   │    pgup     │   ~    │  up  │  `   │  :  │  mute   │
//    ├─────────┼────┼───────────┼───────────┼─────┼─────┤                   ├─────────────┼────────┼──────┼──────┼─────┼─────────┤
//    │  vold   │ !  │     @     │     #     │  $  │  %  │                   │      ^      │   l    │ down │ rght │  -  │    "    │
//    ├─────────┼────┼───────────┼───────────┼─────┼─────┤                   ├─────────────┼────────┼──────┼──────┼─────┼─────────┤
//    │ QK_BOOT │ <  │     [     │     ]     │  >  │ del │                   │    pgdn     │   \    │  |   │  +   │  ?  │ LGUI(`) │
//    └─────────┴────┼───────────┼───────────┼─────┴─────┘                   └─────────────┴────────┼──────┼──────┼─────┴─────────┘
//                   │ PREV_WORD │ NEXT_WORD │                                                      │ down │  up  │                
//                   └───────────┴───────────┼─────┬─────┐                   ┌─────────────┬────────┼──────┴──────┘                
//                                           │     │     │                   │             │        │                              
//                                           ├─────┼─────┤                   ├─────────────┼────────┤                              
//                                           │     │     │                   │ SELECT_LINE │        │                              
//                                           ├─────┼─────┤                   ├─────────────┼────────┤                              
//                                           │     │     │                   │   TO_WIN    │ TO_MAC │                              
//                                           └─────┴─────┘                   └─────────────┴────────┘                              
[_ARROWS] = LAYOUT_5x6(
  KC_F12  , KC_F1   , KC_F2     , KC_F3     , KC_F4   , KC_F5   ,                     KC_F6       , KC_F7    , KC_F8   , KC_F9    , KC_F10  , KC_F11      ,
  KC_VOLU , KC_LCBR , KC_LPRN   , KC_RPRN   , KC_RCBR , KC_INS  ,                     KC_PGUP     , KC_TILDE , KC_UP   , KC_GRV   , KC_COLN , KC_MUTE     ,
  KC_VOLD , KC_EXLM , KC_AT     , KC_HASH   , KC_DLR  , KC_PERC ,                     KC_CIRC     , KC_L     , KC_DOWN , KC_RIGHT , KC_MINS , KC_DQUO     ,
  QK_BOOT , KC_LT   , KC_LBRC   , KC_RBRC   , KC_GT   , KC_DEL  ,                     KC_PGDN     , KC_BSLS  , KC_PIPE , KC_PLUS  , KC_QUES , LGUI(KC_GRV),
                      PREV_WORD , NEXT_WORD ,                                                                  KC_DOWN , KC_UP                            ,
                                              KC_TRNS , KC_TRNS ,                     KC_TRNS     , KC_TRNS                                               ,
                                              KC_TRNS , KC_TRNS ,                     SELECT_LINE , KC_TRNS                                               ,
                                              KC_TRNS , KC_TRNS ,                     TO_WIN      , TO_MAC                                                
)
};

bool isMac(void) {
    return get_highest_layer(layer_state);
}

void delete_word(bool pressed) {
    const uint16_t kc = isMac() ? C(KC_BSPC) : A(KC_BSPC);
    if (pressed) {
        register_code16(kc);
    } else {
        unregister_code16(kc);
    }
}


void to_win(void) {
    set_single_persistent_default_layer(_WIN);
    layer_on(_WIN);
    layer_off(_MAC);
    layer_off(_SYMBOLS);
}

void to_mac(void) {
    set_single_persistent_default_layer(_MAC);
    layer_on(_MAC);
    layer_off(_WIN);
    layer_off(_SYMBOLS);
}

enum { LEFT = 0, RIGHT = 1 };
void adjacent_word(bool pressed, uint8_t direction) {
    const uint8_t  kc     = direction == LEFT ? KC_LEFT : KC_RIGHT;
    const uint16_t code16 = isMac() ? A(kc) : C(kc);
    if (pressed) {
        register_code16(code16);
    } else {
        unregister_code16(code16);
    }
}

void select_line(bool pressed) {
    if (isMac()) {
        tap_code16(G(KC_LEFT));
        tap_code16(S(G(KC_RIGHT)));
    } else {
        tap_code16(KC_HOME);
        tap_code16(S(KC_END));
    }
}

const uint16_t PROGMEM delete_word_combo[] = {KC_BSPC, KC_SPC, COMBO_END};
combo_t                key_combos[]        = {[DELETE_WORD_COMBO] = {.keys = &(delete_word_combo)[0], .keycode = (KC_NO)}};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case DELETE_WORD_COMBO:
            delete_word(pressed);
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    const bool pressed = record->event.pressed;
    switch (keycode) {
        case TO_WIN:
            to_win();
            return false;
        case TO_MAC:
            to_mac();
            return false;
        case PREV_WORD:
            adjacent_word(pressed, LEFT);
            return false;
        case NEXT_WORD:
            adjacent_word(pressed, RIGHT);
            return false;
        case SELECT_LINE:
            select_line(pressed);
            return false;
        default:
            return true;
    }
}
