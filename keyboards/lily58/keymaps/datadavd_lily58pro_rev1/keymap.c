#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern uint8_t is_master;

enum layer_number {
  _QWERTY = 0,
  _SUPER,
  _RAISE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+----- |
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | \|   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+----- |
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |  ;:  |  '"  |
 * |------+------+------+------+------+------|   `~  |    | Enter |------+------+------+------+------+------|
 * |LCTRL |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |  ,<  |  .>  |  ?/  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |  [   | LAlt | LGUI | /SUPER  /       \Space \  |RAISE | RGUI |   ]  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LCTRL, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,   KC_GRV, KC_ENT,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, \
                        KC_LBRC, KC_LALT, KC_LGUI, MO(_SUPER), KC_SPC, MO(_RAISE), KC_RGUI, KC_RBRC \
),
/* SUPER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |Trans | XXXX | XXXX | XXXX | XXXX | XXXX |                    |  \|  |  `~  |BackSP|  -_  |  =+  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Tab | Tab  | ESC  |Enter |LCTRL |  {   |                    |   }  |  Tab |  Up  |  {[  |  ]}  |  \|  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|LShift| LGUI | LAlt |   _  |  (   |-------.    ,-------|   )  | Left | Down |Right |   =  |Enter |
 * |------+------+------+------+------+------| CAPS  |    |BackSP |------+------+------+------+------+------|
 * |LCTRL |LCTRL | Home |Pg Up |Pg Dwn| End  |-------|    |-------|   B  |   V  |   C  |   X  |   Z  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |Trans | LAlt |LGUI  | /Trans  /       \Space \  |Del   | TGUI |Trans |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_SUPER] = LAYOUT( \
  KC_TRNS,   KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_NO,                         KC_BSLS,  KC_GRV,   KC_BSPC,  KC_MINS,  KC_EQL,  KC_BSPC,\
  KC_TAB,    KC_TAB,   KC_ESC,   KC_ENT,   KC_LCTRL,  KC_LCBR,                       KC_RCBR,  KC_TAB,   KC_UP,    KC_LBRC,  KC_RBRC, KC_TRNS, \
  KC_LSFT,   KC_LSFT,  KC_LGUI,  KC_LALT,  KC_UNDS,   KC_LPRN,                       KC_RPRN,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_EQL,  KC_ENT, \
  KC_LCTL,   KC_LCTL,  KC_HOME,  KC_PGUP,  KC_PGDN,   KC_END,   KC_CAPS, KC_BSPC,    KC_B,     KC_V,     KC_C,     KC_X,     KC_Z,    KC_RSFT, \
                                  KC_TRNS, KC_LALT, KC_LGUI, KC_TRNS, KC_SPC, KC_DEL, KC_RGUI, KC_TRNS\
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | Tab  |      |  [   |   ]  | CAPS |                    | MUTE | VOLU |  Up  |  {[  |  ]}  | CAPS |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|LShift| DEL  |  (   |   )  |  `~  |-------.    ,-------| VOLD | Left | Down |Right |RShift|Enter |
 * |------+------+------+------+------+------|  BRID |    | BRIU  |------+------+------+------+------+------|
 * |LCTRL |LCTRL | MRWD | MPLY | MFFD | MSTP |-------|    |-------| End  |Pg Dwn|Pg Up | Home |RShift|RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | XXXX | LAlt | LGUI | /BackSP /       \Trans \  |Trans |Trans | XXXX |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,    KC_F6,                       KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,   KC_F12, \
  KC_TAB,  KC_TAB,  KC_NO,   KC_LBRC,  KC_RBRC,  KC_CAPS,                     KC_MUTE,  KC_VOLU,  KC_UP,   KC_LBRC,  KC_RBRC,  KC_CAPS, \
  KC_LSFT, KC_LSFT, KC_DEL,  KC_LPRN,  KC_RPRN,  KC_GRV,                      KC_VOLD,  KC_LEFT,  KC_DOWN, KC_RGHT,  KC_RSFT,  KC_ENT, \
  KC_LCTL, KC_LCTL, KC_MRWD, KC_MPLY,  KC_MFFD,  KC_MSTP,   KC_BRID, KC_BRIU, KC_END,   KC_PGDN,  KC_PGUP, KC_HOME,  KC_RSFT,  KC_RSFT, \
                             KC_NO, KC_LALT, KC_LGUI, KC_BSPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO \
)
};

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
//const char *read_keylog(void);
//const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

static void render_logo(void) {
  static const char PROGMEM my_logo[] = {
    // Paste the code from the previous step below this line!
    // 'DataDavD Logo', 128x32px
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x01, 0x01, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0x19, 0xf9, 0xf9, 0xf9, 0xe1, 0xe7, 0x07, 0xff, 0xff,
    0xff, 0x01, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0x01, 0xff, 0xff,
    0xff, 0x01, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0x61, 0x61, 0x67, 0x67, 0x67, 0x67, 0x07, 0x07, 0xff,
    0xff, 0x01, 0x01, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0xf9, 0xf9, 0xf9, 0xf9, 0x01, 0x01, 0xff,
    0xff, 0x01, 0x01, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0x19, 0xf9, 0xf9, 0xf9, 0xe1, 0xe7, 0x07, 0xff,
    0xff, 0xff, 0x01, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0x01, 0xff,
    0xff, 0xff, 0x01, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0x01, 0x01, 0xf9, 0xf9, 0xf9, 0xf9, 0x01, 0x01,
    0xff, 0xff, 0x01, 0x01, 0xf9, 0xf9, 0xf9, 0xf9, 0x19, 0x19, 0xf9, 0xf9, 0xe1, 0xe1, 0x07, 0x07,
    0x80, 0x80, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x98, 0x9f, 0x9f, 0x9f, 0x87, 0xe7, 0xe0, 0xff, 0xff,
    0xff, 0x80, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x99, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x80, 0xff, 0xff,
    0xff, 0x80, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x98, 0x98, 0x9e, 0x9e, 0x9e, 0x9e, 0x80, 0x80, 0xff,
    0xff, 0x80, 0x80, 0x9f, 0x9f, 0x9f, 0x9f, 0x99, 0x99, 0x9f, 0x9f, 0x9f, 0x9f, 0x80, 0x80, 0xff,
    0xff, 0x80, 0x80, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x98, 0x9f, 0x9f, 0x9f, 0x87, 0xe7, 0xe0, 0xff,
    0xff, 0xff, 0x80, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x99, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x80, 0xff,
    0xff, 0xff, 0xe0, 0xe7, 0x87, 0x9f, 0x9f, 0x9f, 0x98, 0x98, 0x9f, 0x9f, 0x87, 0x87, 0xe0, 0xe0,
    0xff, 0xff, 0x80, 0x80, 0x9f, 0x9f, 0x9f, 0x9f, 0x98, 0x98, 0x9f, 0x9f, 0x87, 0x87, 0xe0, 0xe0,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff

  };

  oled_write_raw_P(my_logo, sizeof(my_logo));
}

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    render_logo();
//    oled_write_ln(read_layer_state(), false);
//    oled_write_ln(read_keylog(), false);
//    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    render_logo();
//    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
//    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
