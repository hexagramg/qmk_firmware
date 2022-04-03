// Copyright 2021 Konstantin (@Konstantin)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _MAC_QWERTY,
    _NAV,
    _SYM,
    _GAMING,
    _GAMING_ALT,
};

// Aliases for readability
#define QWERTY DF(_QWERTY)
#define GAMING DF(_GAMING)
#define MAC DF(_MAC_QWERTY)

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
*
 *        ,-------------------------------------------.                                                ,-------------------------------------------.
 *        |  Tab   |   Q  |   W  |   E  |   R  |   T  |                                                |   Y  |   U  |   I  |   O  |   P  |  LBRC  |
 *,-------+--------+------+------+------+------+------|                                                |------+------+------+------+------+--------+-------.
 *|  ESC  | Ctrl |   A  |   S  |   D  |   F  |   G  |                                                |   H  |   J  |   K  |   L  | ;  : |Ctrl/' "| RBRC  |
 *`-------+--------+------+------+------+------+------|                                                |------+------+------+------+------+--------+-------'
 *        | Enter  |   Z  |   X  |   C  |   V  |   B  |                                                |   N  |   M  | ,  < | . >  | /  ? |  Bksp  |
 *        `----------------------+------+------+------+--|-----------------.      .-----------------|--+------+------+------+----------------------'
 *                               | Menu | LALT | NAV  | Shift| Space| LCTL |      | RGUI | Sym  | Space|  SYM | RGUI |GAMING|                                 
 *                               |      |      |      |      |      |      |      |      |      |      |      |      |      |                                 
 *                               `-----------------------------------------'      `-----------------------------------------'                                 
 */
    [_QWERTY] = LAYOUT(\
              KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P , KC_LBRC, \
     KC_ESC , KC_LCTL , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                        KC_H,   KC_J ,  KC_K ,   KC_L ,KC_SCLN,CTL_QUOT, KC_RBRC, \
              KC_ENT  , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B ,                                        KC_N,   KC_M ,KC_COMM, KC_DOT ,KC_SLSH, KC_BSPC, \
                                KC_APP , KC_LALT,   NAV  , KC_LSFT,KC_LCTL,KC_NO,     KC_NO,KC_RGUI, KC_SPC,   SYM  ,KC_RGUI, GAMING),
/*
 * Base Layer: MAC QWERTY Layer 
*
 *        ,-------------------------------------------.                                                ,-------------------------------------------.
 *        |  Tab   |   Q  |   W  |   E  |   R  |   T  |                                                |   Y  |   U  |   I  |   O  |   P  |  LBRC  |
 *,-------+--------+------+------+------+------+------|                                                |------+------+------+------+------+--------+-------.
 *|GRAVE_ESC| Ctrl |   A  |   S  |   D  |   F  |   G  |                                                |   H  |   J  |   K  |   L  | ;  : |Ctrl/' "| RBRC  |
 *`-------+--------+------+------+------+------+------|                                                |------+------+------+------+------+--------+-------'
 *        | Enter  |   Z  |   X  |   C  |   V  |   B  |                                                |   N  |   M  | ,  < | . >  | /  ? |  Bksp  |
 *        `----------------------+------+------+------+--|-----------------.      .-----------------|--+------+------+------+----------------------'
 *                               | Menu | LALT | NAV  | Shift| RGUI |      |      |      | LCTL | Space|  SYM | RGUI |GAMING|                                 
 *                               |      |      |      |      |      |      |      |      |      |      |      |      |      |                                 
 *                               `-----------------------------------------'      `-----------------------------------------'                                 
 */
    [_MAC_QWERTY] = LAYOUT(\
              KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P , KC_LBRC, \
     KC_GESC ,KC_LCTL , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                        KC_H,   KC_J ,  KC_K ,   KC_L ,KC_SCLN,CTL_QUOT, KC_RBRC, \
              KC_ENT  , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B ,                                        KC_N,   KC_M ,KC_COMM, KC_DOT ,KC_SLSH, KC_BSPC, \
                                KC_APP , KC_LALT,   NAV  , KC_LSFT,KC_RGUI,KC_NO,       KC_M,KC_LCTL, KC_SPC,   SYM  ,KC_RGUI , GAMING),
/*

 * MO Layer: NAV This layer is for numbers, arrows and F keys
 *
 *        ,-------------------------------------------.                                                ,-------------------------------------------.
 *        |KC_TRNS_| XXXX |   7  |   8  |   9  | CAPS |                                                |  F1  |  F2  |  F3  |  F4  |  F5  |  F6    |
 *,-------+--------+------+------+------+------+------|                                                |------+------+------+------+------+--------+-------.
 *|KC_TRNS|KC_TRNS_|   0  |   4  |   5  |   6  |INSERT|                                                | LEFT | DOWN |  UP  | RIGHT| F12  |KC_TRNS_| XXXXX |
 *`-------+--------+------+------+------+------+------|                                                |------+------+------+------+------+--------+-------'
 *        |KC_TRNS_| XXXX |   1  |   2  |   3  | XXXX |                                                |  F7  |  F8  | F9   | F10  | F11  |KC_TRNS_|
 *        `----------------------+------+------+------+--|-----------------.      .-----------------|--+------+------+------+----------------------'
 *                               |______|______|______|______|______|______|      |______|______|______|______|______| MAC  |
 *                               |      |      |      |      |      |      |      |      |      |      |      |      |      |
 *                               `-----------------------------------------'      `-----------------------------------------'
*/ 
    [_NAV] = LAYOUT(\
              KC_TRNS,KC_NO,  KC_7   ,  KC_8  ,   KC_9 ,   KC_CAPS,                                        KC_F1  ,   KC_F2,  KC_F3,   KC_F4,  KC_F5,   KC_F6,  \
     KC_TRNS, KC_TRNS, KC_0  ,  KC_4   ,  KC_5  ,   KC_6 ,   KC_INS ,                                        KC_LEFT, KC_DOWN,  KC_UP,KC_RIGHT, KC_F12, KC_TRNS, KC_NO, \
              KC_TRNS,KC_NO,  KC_1   ,  KC_2  ,   KC_3 ,   KC_NO,                                        KC_F7,   KC_F8,    KC_F9,   KC_F10, KC_F11,KC_TRNS,        \
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, MAC \
    ),


/*
 * MO Layer: Symbol layer
 *
 *        ,-------------------------------------------.                                                ,-------------------------------------------.
 *        |     !  |   @  |   #  |   $  |   %  |   ^  |                                                |   &  |   *  |   (  |   )  |   _  |   ~    |
 *,-------+--------+------+------+------+------+------|                                                |------+------+------+------+------+--------+-------.
 *|KC_TRNS|KC_TRNS_| XXXX | HOME | PGUP |  DEL |prscr |                                                |   -  |   =  |  {   |   }  |   |  |KC_TRNS_| XXXXX |
 *`-------+--------+------+------+------+------+------|                                                |------+------+------+------+------+--------+-------'
 *        |KC_TRNS_| XXXX |  END | PGDN | XXXX | XXXX |                                                |   _  |   +  |   [  |   ]  |   \  |KC_TRNS_|
 *        `----------------------+------+------+------+--|-----------------.      .-----------------|--+------+------+------+----------------------'
 *                               |______|______|______|______|______|______|      |______|______|______|______|______|QWERTY|
 *                               |      |      |      |      |      |      |      |      |      |      |      |      |      |
 *                               `-----------------------------------------'      `-----------------------------------------'
 */
    [_SYM] = LAYOUT(\
              KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,   KC_PERC, KC_CIRC,                                        KC_AMPR,  KC_ASTR, KC_LPRN,  KC_RPRN, KC_GRV, S(KC_GRV), \
     KC_TRNS, KC_TRNS,KC_NO,   KC_HOME, KC_PGUP, KC_DEL,   KC_PSCR,                                        KC_MINS, KC_EQL,   KC_LCBR, KC_RCBR,  KC_PIPE, KC_TILD, KC_NO, \
              KC_TRNS,KC_NO,   KC_END , KC_PGDN, KC_NO,  KC_NO,                                        KC_UNDS, KC_PLUS,  KC_LBRC, KC_RBRC,  KC_BSLS, KC_TRNS, \
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QWERTY \
    ),

/*
 * MO Layer: Gaming Layer
 *
 *        ,-------------------------------------------.                                               ,-------------------------------------------.          
 *        |    T   |  TAB |   Q  |   W  |   E  |   R  |                                               |   Y  |   U  |   I  |   O  |   P  |  LBRC  |          
 *,-------+--------+------+------+------+------+------|                                               |------+------+------+------+------+--------+-------.  
 *|   M   |    G   | LSHFT|   A  |   S  |   D  |   F  |                                               |   H  |   J  |   K  |   L  | ;  : |Ctrl/' "| RBRC  |  
 *`-------+--------+------+------+------+------+------|                                               |------+------+------+------+------+--------+-------'  
 *        |    B   | LCTL |   Z  |   X  |   C  |   V  |                                               |   N  |   M  | ,  < | . >  | /  ? |  Bksp  |          
 *        `----------------------+------+------+------+--|-----------------.     .-----------------|--+------+------+------+----------------------'  
 *                               |______| LALT |GAME_A|  SPC |GAME_ALT |___|     | Space| LGUI |QWERTY| ENTER|  SPC |______|                                 
*                                `-----------------------------------------'     `-----------------------------------------'                                 
*/ 
    [_GAMING] = LAYOUT(\
              KC_T,    KC_TAB,   KC_Q,    KC_W,    KC_E,     KC_R,                                        KC_Y,    KC_U,     KC_I,    KC_O,     KC_P,    KC_LBRC, \
        KC_M, KC_G,    KC_LSFT,  KC_A,    KC_S,    KC_D,     KC_F,                                        KC_H,    KC_J,     KC_K,    KC_L,     KC_SCLN, KC_QUOT, KC_RBRC, \
              KC_B,    KC_LCTL,  KC_Z,    KC_X,    KC_C,     KC_V,                                        KC_N,    KC_M,     KC_COMM, KC_DOT,   KC_SLSH, KC_BSPC, \
                                KC_TRNS, KC_LALT, GAME_ALT, KC_SPC, GAME_ALT_CTRL, KC_TRNS,         KC_TRNS, KC_LGUI, QWERTY,  KC_ENT,   KC_SPC, KC_TRNS \
    ),
/*
 * MO Layer: Gaming ALT Layer
 *
 *        ,-------------------------------------------.                                               ,-------------------------------------------.          
 *        |    T   |   1  |   2  |   W  |   3  |   4  |                                               |   Y  |   U  |   I  |   O  |   P  |  LBRC  |          
 *,-------+--------+------+------+------+------+------|                                               |------+------+------+------+------+--------+-------.  
 *|  ESC  |    5   |SHIFT |   A  |   S  |   D  |   6  |                                               |   H  |   J  |   K  |   L  | ;  : |Ctrl/' "| RBRC  |  
 *`-------+--------+------+------+------+------+------|                                               |------+------+------+------+------+--------+-------'  
 *        |    B   | LCTL |   7  |   8  |   9  |   0  |                                               |   N  |   M  | ,  < | . >  | /  ? |  Bksp  |          
 *        `----------------------+------+------+------+--|-----------------.     .-----------------|--+------+------+------+----------------------'  
 *                               |______|   L  |GAME_A|______|______|______|     |______|______|______|______|______|RESET |                           
 *                               |      |      |LT    |      |      |      |     |      |      |      |      |      |      |                                 
 *                               `-----------------------------------------'     `-----------------------------------------'                                 
*/ 
    [_GAMING_ALT] = LAYOUT( \
              KC_T,    KC_1,   KC_2, KC_TRNS ,  KC_3,  KC_4,                                              KC_F1  ,   KC_F2,  KC_F3,   KC_F4,  KC_F5,   KC_F6, \
        KC_ESC, KC_5,  KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,  KC_6,                                             KC_LEFT, KC_DOWN,  KC_UP,KC_RIGHT, KC_F12, KC_TRNS, KC_NO, \
              KC_J,    KC_TRNS,  KC_7, KC_8,  KC_9,  KC_0,                                                KC_F7,   KC_F8,    KC_F9,   KC_F10, KC_F11,KC_TRNS, \
                                KC_TRNS, KC_L , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, RESET  \
    ),



};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // switching windows
        if (clockwise) {
            if (!is_alt_tab_active) {
               is_alt_tab_active = true;
               if (biton32(default_layer_state) == _MAC_QWERTY) {
                   register_code(KC_RGUI);
               } else {
                   register_code(KC_LALT);
               }
            }
            alt_tab_timer = timer_read();
            tap_code16(KC_TAB);
        } else {
        if (!is_alt_tab_active) {
            is_alt_tab_active = true;
            if (biton32(default_layer_state) == _MAC_QWERTY) {
                register_code(KC_RGUI);
            } else {
                register_code(KC_LALT);
            }
        }
        alt_tab_timer = timer_read();
        tap_code16(S(KC_TAB));
        }
    } else if (index == 1) {
        // Page up/Page down
        if (!clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}



void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 750) {
        if (biton32(default_layer_state) == _MAC_QWERTY) {
            unregister_code(KC_RGUI);
        } else {
            unregister_code(KC_LALT);
        }
        is_alt_tab_active = false;
    }
  }
}
#endif