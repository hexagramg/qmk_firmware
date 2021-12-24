// Copyright 2021 Konstantin (@Konstantin)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _NAV,
    _SYM,
    _GAMING,
    _GAMING_ALT,
};

// Aliases for readability
#define QWERTY DF(_QWERTY)
#define GAMING DF(_GAMING)

#define SYM MO(_SYM)
#define NAV MO(_NAV)
#define GAME_ALT MO(_GAMING_ALT)
#define GAME_ALT_CTRL LM(_GAMING_ALT, MOD_LCTL)

#define CTL_ESC MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT MT(MOD_LALT, KC_ENT)

bool     is_alt_tab_active = false;
uint16_t alt_tab_timer     = 0;
// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY                       
 */
    [_QWERTY] = LAYOUT(\
              //,-----------------------------------------------------------.                                                         ,-----------------------------------------------------------.
                  KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,                                                           KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_LBRC ,\
    //|---------+---------+---------+---------+---------+---------+---------|                                                         |---------+---------+---------+---------+---------+---------+---------|
        KC_ESC  , KC_LCTL , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    ,                                                           KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT , KC_NO   ,\
    //|---------+---------+---------+---------+---------+---------+---------|                                                         |---------+---------+---------+---------+---------+---------+---------|
                  KC_ENT  , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,                                                           KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_BSPC ,\
              //|---------+---------+---------+---------+---------+---------+---------+---------|                 |---------+---------+---------+---------+---------+---------+---------+---------|
                                                GAMING  , KC_RGUI , KC_LALT , NAV     , KC_LSFT ,   KC_NO,KC_NO   , KC_SPC  , SYM     , KC_RGUI , KC_NO   , KC_APP  \
                                            //`-------------------------------------------------'                 `-------------------------------------------------'
    ),
/*
 * MO Layer: NAV This layer is for numbers, arrows and F keys
*/ 
    [_NAV] = LAYOUT(\
              //,-----------------------------------------------------------.                                                         ,-----------------------------------------------------------.
                  KC_TRNS , KC_NO   , KC_7    , KC_8    , KC_9    , KC_CAPS ,                                                           KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   ,\
    //|---------+---------+---------+---------+---------+---------+---------|                                                         |---------+---------+---------+---------+---------+---------+---------|
        KC_TRNS , KC_TRNS , KC_0    , KC_4    , KC_5    , KC_6    , KC_INS  ,                                                           KC_LEFT , KC_DOWN , KC_UP   , KC_RIGHT, KC_TRNS , KC_TRNS , KC_TRNS ,\
    //|---------+---------+---------+---------+---------+---------+---------|                                                         |---------+---------+---------+---------+---------+---------+---------|
                  KC_TRNS , KC_NO   , KC_1    , KC_2    , KC_3    , KC_NO   ,                                                           KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12 ,\
              //|---------+---------+---------+---------+---------+---------+---------+---------|                 |---------+---------+---------+---------+---------+---------+---------+---------|
                                                KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS \
                                            //`-------------------------------------------------'                 `-------------------------------------------------'
    ),
/*
 * MO Layer: Symbol layer
 */
    [_SYM] = LAYOUT(\
              //,-----------------------------------------------------------.                                                         ,-----------------------------------------------------------.
                  KC_GRV  , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC ,                                                           KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN,  KC_RPRN , KC_TILD ,\
    //|---------+---------+---------+---------+---------+---------+---------|                                                         |---------+---------+---------+---------+---------+---------+---------|
        KC_TRNS , KC_TRNS , KC_NO   , KC_HOME , KC_PGUP , KC_DEL  , KC_PSCR ,                                                           KC_MINS , KC_EQL  , KC_LCBR , KC_RCBR , KC_PIPE , KC_TILD , KC_TRNS ,\
    //|---------+---------+---------+---------+---------+---------+---------|                                                         |---------+---------+---------+---------+---------+---------+---------|
                  KC_TRNS , KC_NO   , KC_END  , KC_PGDN , KC_NO   , KC_NO   ,                                                           KC_UNDS , KC_PLUS , KC_LBRC , KC_RBRC , KC_BSLS , KC_TRNS ,\
              //|---------+---------+---------+---------+---------+---------+---------+---------|                 |---------+---------+---------+---------+---------+---------+---------+---------|
                                                KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS \
                                            //`-------------------------------------------------'                 `-------------------------------------------------'
    ),
/*
 * MO Layer: Gaming Layer                             
*/ 
    [_GAMING] = LAYOUT(\
              //,-----------------------------------------------------------.                                                         ,-----------------------------------------------------------.
                  KC_T    , KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    ,                                                           KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_LBRC ,\
    //|---------+---------+---------+---------+---------+---------+---------|                                                         |---------+---------+---------+---------+---------+---------+---------|
        KC_M    , KC_G    , KC_LCTL , KC_A    , KC_S    , KC_D    , KC_F    ,                                                           KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT , KC_TRNS ,\
    //|---------+---------+---------+---------+---------+---------+---------|                                                         |---------+---------+---------+---------+---------+---------+---------|
                  KC_B    , KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V    ,                                                           KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_BSPC ,\
              //|---------+---------+---------+---------+---------+---------+---------+---------|                 |---------+---------+---------+---------+---------+---------+---------+---------|
                                                KC_TRNS , KC_TRNS , KC_LALT , GAME_ALT, KC_SPC  , KC_TRNS,KC_TRNS , QWERTY  , KC_ENT , KC_SPC   , KC_TRNS , KC_LGUI \
                                            //`-------------------------------------------------'                 `-------------------------------------------------'
    ),
/*
 * MO Layer: Gaming ALT Layer                             
*/ 
    [_GAMING_ALT] = LAYOUT( \
              //,-----------------------------------------------------------.                                                         ,-----------------------------------------------------------.
                  KC_T    , KC_1    , KC_2    , KC_TRNS , KC_3    , KC_4    ,                                                           KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   ,\
    //|---------+---------+---------+---------+---------+---------+---------|                                                         |---------+---------+---------+---------+---------+---------+---------|
        KC_ESC  , KC_5    , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_6    ,                                                           KC_LEFT , KC_DOWN , KC_UP   , KC_RIGHT, KC_F12  , KC_TRNS , KC_TRNS ,\
    //|---------+---------+---------+---------+---------+---------+---------|                                                         |---------+---------+---------+---------+---------+---------+---------|
                  KC_J    , KC_TRNS , KC_7    , KC_8    , KC_9    , KC_0    ,                                                           KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_TRNS ,\
              //|---------+---------+---------+---------+---------+---------+---------+---------|                 |---------+---------+---------+---------+---------+---------+---------+---------|
                                                RESET   , KC_TRNS , KC_LGUI , KC_TRNS , KC_TRNS , KC_TRNS,KC_TRNS , NAV     , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS \
                                            //`-------------------------------------------------'                 `-------------------------------------------------'
    )
};


#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    // Left encoder
    if (index == 0) {
        // Alt+Tab
        alt_tab_timer = timer_read();
        if (clockwise) {
            if (!is_alt_tab_active) {
                register_code(KC_LALT);
            }
            tap_code16(KC_TAB);
        } else {
            if (!is_alt_tab_active) {
                register_code(KC_LALT);
                // Fix Alt+Shift+Tab not showing on Mac
                tap_code16(KC_TAB);
            }
            tap_code16(S(KC_TAB));
        }
        if (!is_alt_tab_active) {
            is_alt_tab_active = true;
        }
    // Right encoder
    } else if (index == 1) {
        // Volume control
        if (clockwise) {
            tap_code(KC__VOLDOWN);
        } else {
            tap_code(KC__VOLUP);
        }
    }
    return false;
}



void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 500) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}
#endif