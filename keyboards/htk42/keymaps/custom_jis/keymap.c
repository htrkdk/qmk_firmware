#include QMK_KEYBOARD_H
#include "a2j/translate_ansi_to_jis.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE = 0,
    _FN,
    _LOWER,
    _RAISE
};

enum custom_keycodes {
    OUT_TOG
};

typedef union {
  uint32_t raw;
  struct {
    bool is_jis_mode: 1;
  };
} user_config_t;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,  KC_BSPC, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  MO(_FN), \
        KC_LALT, LGUI_T(KC_MHEN),  LT(_LOWER, KC_SPC),   KC_DEL,   LT(_RAISE, KC_SPC),   RGUI_T(KC_HENK),  KC_RSFT
    ),
    [_FN] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUSE,KC_UP,   XXXXXXX, KC_BSPC, \
        _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX, KC_HOME, KC_PGUP, KC_LEFT, KC_RIGHT,_______, _______, \
        _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, KC_END,  KC_PGDN, KC_DOWN, XXXXXXX, _______, \
        _______, _______,          _______,              _______,  _______,              _______,          _______
    ),
    [_LOWER] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,  \
        _______, KC_MINS, KC_EQL, KC_BSLS,  KC_GRV,  XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX, KC_SCLN, KC_QUOT, \
        _______, OUT_TOG, RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LABK, KC_RABK, KC_SLSH, \
        _______, _______,          _______,              _______,  _______,              _______,          _______
    ),
    [_RAISE] = LAYOUT(
        KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD, \
        _______, KC_UNDS, KC_PLUS, KC_PIPE, KC_TILD, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX, KC_COLN, KC_DQUO, \
        _______, KC_BSPC, KC_DEL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LABK, KC_RABK, KC_QUES, \
        _______, _______,          _______,              _______,  _______,              _______,          _______
    )
};

// Configure ANSI/JIS mode function
user_config_t user_config;

void init_user_config(void) {
    user_config.raw = eeconfig_read_user();
}

bool is_jis_mode(void) {
    return user_config.is_jis_mode;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (keycode == OUT_TOG) {
    if (record->event.pressed) {
      // set_jis_mode
      user_config.is_jis_mode = !is_jis_mode();
      eeconfig_update_user(user_config.raw);
    }
    return false;
  }

  if (!is_jis_mode()) {
    return true;
  }

  return process_record_user_a2j(keycode, record);
}
