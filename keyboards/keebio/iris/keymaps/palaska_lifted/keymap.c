#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define KC_CTLBACKTICK CTL_T(KC_GRV)

//Tap Dance Declarations
enum {
  TD_PARENS_OPEN = 0,
  TD_PARENS_CLOSE,
};

void dance_parens_open_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_LSFT);
    register_code (KC_9);
  } else if (state->count == 2) {
    register_code (KC_LBRC);
  } else {
    register_code (KC_LSFT);
    register_code (KC_LBRC);
  }
}

void dance_parens_open_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LSFT);
    unregister_code (KC_9);
  } else if (state->count == 2) {
    unregister_code (KC_LBRC);
  } else {
    unregister_code (KC_LSFT);
    unregister_code (KC_LBRC);
  }
}

void dance_parens_close_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_LSFT);
    register_code (KC_0);
  } else if (state->count == 2) {
    register_code (KC_RBRC);
  } else {
    register_code (KC_LSFT);
    register_code (KC_RBRC);
  }
}

void dance_parens_close_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LSFT);
    unregister_code (KC_0);
  } else if (state->count == 2) {
    unregister_code (KC_RBRC);
  } else {
    unregister_code (KC_LSFT);
    unregister_code (KC_RBRC);
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_PARENS_OPEN]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_parens_open_finished, dance_parens_open_reset),
  [TD_PARENS_CLOSE]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_parens_close_finished, dance_parens_close_reset)
// Other declarations would go here, separated by commas, if you have them
};


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────────────┬────────┬────────┬────────┬────────┬──────────────────┐                           ┌────────────────────┬──────────────────┬────────┬────────┬────────┬────────┐
     KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                          KC_Y,                KC_U,              KC_I,    KC_O,    KC_P,    KC_MINS,
  //├────────────────┼────────┼────────┼────────┼────────┼──────────────────┤                           ├────────────────────┼──────────────────┼────────┼────────┼────────┼────────┤
     KC_ESC,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                          KC_H,                KC_J,              KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────────────┼────────┼────────┼────────┼────────┼──────────────────┤                           ├────────────────────┼──────────────────┼────────┼────────┼────────┼────────┤
     KC_LSFT,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                          KC_N,                KC_M,              KC_COMM, KC_DOT,  KC_UP,   KC_BSLS,
  //├────────────────┼────────┼────────┼────────┼────────┼──────────────────┼─────────┐        ┌────────┼────────────────────┼──────────────────┼────────┼────────┼────────┼────────┤
     KC_CTLBACKTICK,  KC_1,    KC_2,    KC_3,    KC_4,    TD(TD_PARENS_OPEN), KC_SPC,           KC_DEL,  TD(TD_PARENS_CLOSE), KC_EQL,            KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT,
  //└────────────────┴────────┴────────┴────────┴─────┬──┴─────┬────────┬───┴────┬────┘        └───┬────┴───┬───────┬────────┴──────────────────┴────────┴────────┴────────┴────────┘
                                               KC_LALT, KC_LGUI, KC_SPC,                    KC_ENT,  LOWER,  KC_BSPC
                                           // └────────┴────────┴────────┘                 └────────┴───────┴────────┘
  ),

  [_LOWER] = LAYOUT(
  //┌────────────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TILD,         KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PGUP,
  //├────────────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC,          KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PGDN,
  //├────────────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT,         _______, _______, _______, _______, _______,                            _______, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, KC_HOME,
  //├────────────────┼────────┼────────┼────────┼────────┼────────┼────────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_CTLBACKTICK,  _______, _______, _______, _______, _______, LGUI(KC_SPC),         KC_DEL,  _______, KC_P1,   KC_P2,   KC_P3,   KC_MINS, KC_END,
  //└────────────────┴────────┴────────┴───┬────┴───┬────┴────────┼────────────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LALT, KC_LGUI, LGUI(KC_SPC),                          KC_ENT,  _______, KC_P0
                                // └───────┴────────┴─────────────┘                         └────────┴────────┴────────┘
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        // update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        // update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}
