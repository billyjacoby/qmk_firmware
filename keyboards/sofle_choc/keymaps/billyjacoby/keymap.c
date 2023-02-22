/* Copyright 2022 Brian Low
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum sofle_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes { KC_LOWER = SAFE_RANGE, KC_RAISE, KC_ADJUST, KC_PRVWD, KC_NXTWD, KC_LSTRT, KC_LEND, KC_DLINE, 
RAYCAST_SHORTCUT, 
EMOJI_KEY,
CMD_Z, CMD_SHIFT_Z,ARROW_FUNC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_ESC,    KC_1,     KC_2,     KC_3,     KC_4, KC_5,                                KC_6,   KC_7,     KC_8,     KC_9,   KC_0,       KC_BSPC, 
        KC_TAB,    KC_Q,     KC_W,     KC_E,     KC_R, KC_T,                                KC_Y,   KC_U,     KC_I,     KC_O,   KC_P,       KC_MINS, 
        KC_LSFT,   KC_A,     KC_S,     KC_D,     KC_F, KC_G,                                KC_H,   KC_J,     KC_K,     KC_L,   KC_SCLN,    KC_QUOT, 
        KC_LCTL,   KC_Z,     KC_X,     KC_C,     KC_V, KC_B, RAYCAST_SHORTCUT,    RAYCAST_SHORTCUT,     KC_N,   KC_M,     KC_COMM,  KC_DOT, KC_SLSH,    KC_BSLS, 
        KC_LBRC,   KC_LGUI,  KC_LALT,  MO(1),    LGUI_T(KC_SPC),            LT(1, KC_ENT),  MO(2),  KC_GRAVE, KC_RALT,  KC_RBRC
        ),


    [1] = LAYOUT(
        KC_EQL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                          EMOJI_KEY, KC_NO, KC_F12, KC_NO, KC_NO, KC_NO, 
    KC_PLUS, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,  LCTL(KC_LEFT),                                  LCTL(KC_RIGHT), KC_NO, KC_UP, KC_NO, KC_NO, KC_EQL,
    KC_TRNS, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_LBRC,                                  KC_RBRC, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_GRV, 
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_TRNS,            KC_TRNS, KC_NO, KC_NO, KC_NO, ARROW_FUNC, KC_NO, KC_NO,
        KC_TRNS,  KC_TRNS, KC_TRNS, MO(3), KC_TRNS,                                         KC_TRNS, MO(3), KC_TRNS, KC_TRNS, KC_TRNS
        ),

    [2] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                      EMOJI_KEY, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_PLUS, KC_NO, KC_NO, KC_NO, KC_NO, LCTL(KC_LEFT),                                      LCTL(KC_RIGHT), KC_NO, KC_UP, KC_NO, KC_NO, KC_NO, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LBRC,                                       KC_RBRC, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, 
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,                KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
                  KC_TRNS, KC_TRNS, KC_TRNS, MO(3), KC_TRNS,                  KC_TRNS, MO(3), KC_TRNS, KC_TRNS, KC_TRNS
        ),

    [3] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                      EMOJI_KEY, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_PLUS, KC_NO, KC_NO, KC_NO, KC_NO, LCTL(KC_LEFT),                                      LCTL(KC_RIGHT), KC_NO, KC_UP, KC_NO, KC_NO, KC_NO, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LSFT(KC_LBRC),                                       LSFT(KC_RBRC), KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, 
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,                KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
        )};

// Sets default effect and color
#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom(); // Enables RGB, without saving settings
    rgblight_sethsv_noeeprom(HSV_GREEN);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT);
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case RAYCAST_SHORTCUT:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(" "));
                return false;
            }
        case EMOJI_KEY:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCTL) SS_LGUI(" ") SS_UP(X_LCTL));
                return false;
            }
        case ARROW_FUNC:
            if (record->event.pressed) {
                SEND_STRING("=>");
                return false;
            }
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case KC_PRVWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            return false;
        case KC_NXTWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            return false;
        case KC_LSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    // CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            return false;
        case KC_LEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    // CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            return false;
        case KC_DLINE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_BSPC);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_BSPC);
            }
            return false;
        case KC_COPY:
            if (record->event.pressed) {
                // CMD-c on Mac, but we have CTL and GUI swapped
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_C);
            }
            return false;
        case KC_PASTE:
            if (record->event.pressed) {
                // CMD-v on Mac, but we have CTL and GUI swapped
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_V);
            }
            return false;
        case KC_CUT:
            if (record->event.pressed) {
                // CMD-x on Mac, but we have CTL and GUI swapped
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_X);
            }
            return false;
            return false;
        case KC_UNDO:
            if (record->event.pressed) {
                // CMD-z on Mac, but we have CTL and GUI swapped
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;
        default:
            return true;
    }
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN ), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = {ENCODER_CCW_CW(RGB_HUI, RGB_HUD ), ENCODER_CCW_CW(LGUI(KC_Z), LGUI(LSFT(KC_Z)))},
    [2] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(RGB_SPD, RGB_SPI)},
    [3] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(RGB_SPD, RGB_SPI)},
};
#endif

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00};

    oled_write_P(qmk_logo, false);
}

void write_int_ln(const char* prefix, uint8_t value) {
    oled_write_P(prefix, false);
    oled_write(get_u8_str(value, ' '), false);
}

static void print_status_narrow(void) {
    oled_write_ln_P(PSTR("soflechoc _____"), false);

    if (get_highest_layer(layer_state) == _ADJUST) {
        uint8_t mode  = rgb_matrix_get_mode();
        HSV     hsv   = rgb_matrix_get_hsv();
        uint8_t speed = rgb_matrix_get_speed();

        if (keymap_config.swap_lctl_lgui) {
            oled_write_ln_P(PSTR("MAC\n"), false);
        } else {
            oled_write_ln_P(PSTR("WIN\n"), false);
        }

        oled_write_ln("RGB", false);
        write_int_ln(PSTR("Mo"), mode);
        write_int_ln(PSTR("H "), hsv.h);
        write_int_ln(PSTR("S "), hsv.s);
        write_int_ln(PSTR("V "), hsv.v);
        write_int_ln(PSTR("Sp"), speed);
        oled_write_P(PSTR("\n\n\n"), false);
    } else {
        oled_write_P(PSTR("\n\n\n\n\n\n\n\n\n"), false);
        led_t led_usb_state = host_keyboard_led_state();
        if (led_usb_state.caps_lock) {
            oled_write_ln_P(PSTR(" CAP "), true);
        } else {
            oled_write_ln_P(PSTR("     "), false);
        }
    }

    // Print current layer
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("main"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("lower  "), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("raise  "), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adj  "), false);
            break;
        default:
            oled_write_P(PSTR("???  "), false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }

    return false;
}

#endif
