#include QMK_KEYBOARD_H

///////// Key Overrides ////////////
// const key_override_t shift_insert = ko_make_basic(MOD_MASK_CTRL, KC_V, LSFT(KC_INS));

// // This globally defines all key overrides to be used
// const key_override_t *key_overrides[] = {
// 	&shift_insert
// };
///////////////////////////////////
///////// Tape Dance for Pipe on ; ////////////
#define TAP_TAPPING_TERM 200
void install_tap_dance_entries(void) {
    vial_tap_dance_entry_t td0 = { KC_SCLN, 
                                   KC_NO,
                                   KC_PIPE,
                                   KC_NO,
                                   TAP_TAPPING_TERM };
    vial_tap_dance_entry_t td1 = { KC_V, 
                                   KC_NO,
                                   LSFT(KC_INS),
                                   KC_NO,
                                   TAP_TAPPING_TERM };
    dynamic_keymap_set_tap_dance(0, &td0); // the first value corresponds to the TD(i) slot
    dynamic_keymap_set_tap_dance(1, &td1);
}

#define TD_PIPE TD(0)
#define TD_Insert TD(1)

void keyboard_post_init_user(void) {
  install_tap_dance_entries();
};
////////////////////////////////////////////////
//// Macro ////
enum custom_keycodes {
    SS_PANE = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SS_PANE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("a") SS_LSFT(SS_TAP(X_QUOTE)));
            }
            return false;
    }

    return true;
}
////////////////////

// Layers //
enum layers {
    _COLEMAK = 0,
    _QWERTY,
    _FN,
};
////////////////////

// Keymaps //
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT_65_ansi_blocker(
        QK_GESC, KC_1,    KC_2,          KC_3,        KC_4,        KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,  KC_Q,    KC_W,          KC_F,        KC_P,        KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    TD_PIPE, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_CAPS, KC_A,    LT(_FN, KC_R), LCTL_T(KC_S),LSFT_T(KC_T),KC_D,    KC_H,    RSFT_T(KC_N), RCTL_T(KC_E), LT(_FN, KC_I), KC_O, KC_QUOT, KC_ENT, KC_PGDN,
        KC_LSFT, KC_Z,    KC_X,          KC_C,        TD_Insert,        KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                     KC_SPC,                     MO(_FN),            KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT
    ),

    [_QWERTY] = LAYOUT_65_ansi_blocker(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______, _______, _______, _______,
        _______, KC_A,    LT(_FN, KC_S),    LCTL_T(KC_D),    LSFT_T(KC_F),    KC_G,    KC_H,    RSFT_T(KC_J),    RCTL_T(KC_K),    LT(_FN, KC_L),    TD_PIPE, _______, _______,  _______,
        _______, KC_Z,    KC_X,    KC_C,    TD_Insert,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  _______, _______, _______,   _______,
        _______, _______, _______,                     _______,                     _______,            _______, _______, _______, _______
    ),

    [_FN] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11, KC_F12, KC_DEL,  KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______, KC_PSCR, KC_SCRL, KC_PAUS, QK_BOOT, SS_PANE,
        _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, EE_CLR, _______,
        _______, TO(_COLEMAK), TO(_QWERTY), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                     _______,                     _______,            _______, _______, _______, _______
    )
};