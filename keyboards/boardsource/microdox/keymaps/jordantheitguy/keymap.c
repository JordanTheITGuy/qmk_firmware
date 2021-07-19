/*
Copyright 2020 Cole Smith <cole@boadsource.xyz>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "split_util.h"

enum layers {
    _QWERTY,
    _RAISE,
    _LOWER,
    _NUMPAD,
    _GAMING,
    _FFXIV
};

bool is_alt_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.

enum custom_keycodes {          // Make sure have the awesome keycode ready
  ALT_TAB = SAFE_RANGE,
};

enum {
    TD_LBRAC_LPAREN,
    TD_RBRAC_RPAREN,
};




#define KC_CTSC LT(_NUMPAD,KC_SCLN)
#define RAISE_SPC LT(_RAISE, KC_SPC)
#define RASE_BACK LT(_RAISE, KC_BSPC)
#define ALT_S MT(MOD_LALT, KC_S)
#define ALT_L MT(MOD_RALT,KC_L)
#define CTRL_D MT(MOD_LCTL, KC_D)
#define CTRL_K MT(MOD_RCTL,KC_K)
#define LOWER_ENT LT(_LOWER, KC_ENT)
#define NUM_A LT(_NUMPAD,KC_A)
#define SHFT_F MT(MOD_LSFT, KC_F)
#define SHFT_J MT(MOD_RSFT, KC_J)
#define TAB_LOWER LT(_LOWER, KC_TAB)
#define KC_COPY LCTL(KC_C)
#define KC_PASTE LCTL(KC_V)
#define KC_HOMER LSFT(KC_HOME)
#define KC_ENDER LSFT(KC_END)
#define KC_GAMER TG(_GAMING)
#define KC_FFXIV TG(_FFXIV)


// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_LBRAC_LPAREN] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_LBRC),
    [TD_RBRAC_RPAREN] = ACTION_TAP_DANCE_DOUBLE(KC_RCBR, KC_RBRC),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x5_3(
        KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,
        NUM_A,  ALT_S,    CTRL_D,    SHFT_F,    KC_G,       KC_H,    SHFT_J,   CTRL_K, ALT_L,   KC_CTSC,
        KC_Z,    KC_X,    KC_C,    KC_V, KC_B,              KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLASH,
                KC_FFXIV, TAB_LOWER, RAISE_SPC,              RASE_BACK, LOWER_ENT, ALT_TAB
                ),
  [_RAISE] = LAYOUT_split_3x5_3(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,        KC_HOMER, KC_HOME, KC_UP, KC_END, KC_ENDER,
        XXXXXXX, XXXXXXX, KC_COPY, KC_PASTE, KC_DEL,        KC_DEL, KC_LEFT, KC_DOWN, KC_RGHT, KC_QUOT,
        KC_LSFT, KC_GRV, XXXXXXX, XXXXXXX, XXXXXXX,         KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
                            _______, _______, _______,          KC_GAMER,  KC_FFXIV, _______
                         ),
  [_LOWER] = LAYOUT_split_3x5_3(
        KC_F2, KC_F3, KC_F5, KC_F8, KC_F12,                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        _______,   _______, KC_LPRN, TD(TD_LBRAC_LPAREN), _______,           _______,TD(TD_RBRAC_RPAREN) , KC_RPRN, _______, KC_DQT,
        XXXXXXX, KC_TILD, XXXXXXX, XXXXXXX, XXXXXXX,             KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                            _______,  _______,  _______,             _______,  _______, _______
                         ),
    [_NUMPAD] = LAYOUT_split_3x5_3(
          KC_ESC, XXXXXXX, KC_MS_UP, KC_PSCR, XXXXXXX,             XXXXXXX, KC_7, KC_8, KC_9, XXXXXXX,
          XXXXXXX, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, XXXXXXX,            XXXXXXX, KC_4, KC_5, KC_6, XXXXXXX,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            XXXXXXX, KC_1, KC_2, KC_3, XXXXXXX,
                            _______,_______ , KC_MS_BTN1,               KC_0, _______, _______
    ),
    [_GAMING] = LAYOUT_split_3x5_3(
          KC_LALT, KC_Q, KC_W, KC_E, XXXXXXX,             XXXXXXX, KC_7, KC_8, KC_9, XXXXXXX,
          KC_LSFT, KC_A, KC_S, KC_D, KC_G,                   XXXXXXX, KC_4, KC_5, KC_6, XXXXXXX,
          XXXXXXX, XXXXXXX, XXXXXXX, KC_V, XXXXXXX,            XXXXXXX, KC_1, KC_2, KC_3, XXXXXXX,
                            _______, KC_TAB, KC_SPC,               KC_0, KC_GAMER, _______
    ),
    [_FFXIV] = LAYOUT_split_3x5_3(
          KC_ESC, KC_Q, KC_W, KC_E, XXXXXXX,             XXXXXXX, KC_7, KC_8, KC_9, XXXXXXX,
          KC_LCTRL, KC_A, KC_S, KC_D, KC_G,                   XXXXXXX, KC_4, KC_5, KC_6, XXXXXXX,
          KC_LALT, XXXXXXX, KC_C, XXXXXXX, XXXXXXX,            XXXXXXX, KC_1, KC_2, KC_3, XXXXXXX,
                            _______, KC_TAB, KC_SPC,               KC_0, KC_FFXIV, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master())
    return OLED_ROTATION_180;
  return rotation;
}

static void render_logo(void) {
  static const char PROGMEM qmk_logo[] = {
     0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0
  };
  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
   switch (get_highest_layer(layer_state)) {
    case _QWERTY:
      oled_write_P(PSTR("B R L N G O\n"), false);
      oled_write_P(PSTR("^\n"), false);
      oled_write_P(PSTR("Layer: Base\n"), false);
      break;
    case _RAISE:
      oled_write_P(PSTR("B R L N G O\n"), false);
      oled_write_P(PSTR("  ^\n"), false);
      oled_write_P(PSTR("Layer: Raise\n"), false);
      break;
    case _LOWER:
      oled_write_P(PSTR("B R L N G O\n"), false);
      oled_write_P(PSTR("    ^\n"), false);
      oled_write_P(PSTR("Layer: Lower\n"), false);
      break;
    case _NUMPAD:
      oled_write_P(PSTR("B R L N G O\n"), false);
      oled_write_P(PSTR("      ^\n"), false);
      oled_write_P(PSTR("Layer: Numpad\n"), false);
      break;
    case _GAMING:
      oled_write_P(PSTR("B R L N G O\n"), false);
      oled_write_P(PSTR("        ^\n"), false);
      oled_write_P(PSTR("Layer: GAMING\n"), false);
      break;
    case _FFXIV:
      oled_write_P(PSTR("FFXIV\n"), false);
      oled_write_P(PSTR("Welcome to Eorzea\n"), false);
      oled_write_P(PSTR("Layer: FFXIV\n"), false);
      break;
    default:
      oled_write_P(PSTR("B R L N G O"), false);
      oled_write_P(PSTR("          ^\n"), false);
      oled_write_P(PSTR("Layer: Other\n"), false);
  }
}

void oled_task_user(void) {
  if (is_keyboard_master()) {
    render_status();
  } else {
    render_logo();
    oled_scroll_left();
  }
}

#endif
