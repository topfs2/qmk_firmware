#include QMK_KEYBOARD_H

#include "topfs2.h"

#ifdef OLED_DRIVER_ENABLE
static uint32_t oled_timer                       = 0;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT_wrapper(
    _________________COLEMAK_L1_________________________,                    _________________COLEMAK_R1_________________________,
    _________________COLEMAK_L2_________________________,                    _________________COLEMAK_R2_________________________,
    _________________COLEMAK_L3_________________________,                    _________________COLEMAK_R3_________________________,
                                     _________THUMB_L_________,        _________THUMB_R_________
  ),

  [_QWERTY] = LAYOUT_wrapper(
    _________________QWERTY_L1__________________________,                    _________________QWERTY_R1__________________________,
    _________________QWERTY_L2__________________________,                    _________________QWERTY_R2__________________________,
    _________________QWERTY_L3__________________________,                    _________________QWERTY_R3__________________________,
                                     _________THUMB_L_________,        _________THUMB_R_________
  ),

  [_LOWER] = LAYOUT_wrapper(
    _________________LOWER_L1___________________________,                    _________________LOWER_R1___________________________,
    _________________LOWER_L2___________________________,                    _________________LOWER_R2___________________________,
    _________________LOWER_L3___________________________,                    _________________LOWER_R3___________________________,
                                     __________BLANK__________,        _________LOWER_RT________
  ),

  [_RAISE] = LAYOUT_wrapper( \
    _________________RAISE_L1___________________________,                    _________________RAISE_R1___________________________,
    _________________RAISE_L2___________________________,                    _________________RAISE_R2___________________________,
    _________________RAISE_L3___________________________,                    _________________RAISE_R3___________________________,
                                     __________BLANK__________,        __________BLANK__________
  ),

  [_MODL] = LAYOUT_wrapper(
    _________________MODL_L1____________________________,                    _________________MODL_R1____________________________,
    _________________MODL_L2____________________________,                    _________________MODL_R2____________________________,
    _________________MODL_L3____________________________,                    _________________MODL_R3____________________________,
                                     __________BLANK__________,        __________BLANK__________
  ),

  [_MODR] = LAYOUT_wrapper( \
    _________________MODR_L1____________________________,                    _________________MODR_R1____________________________,
    _________________MODR_L2____________________________,                    _________________MODR_R2____________________________,
    _________________MODR_L3____________________________,                    _________________MODR_R3____________________________,
                                     __________BLANK__________,        __________BLANK__________
  ),

  [_ADJUST] = LAYOUT_wrapper( \
    _________________ADJUST_L1__________________________,                    _________________ADJUST_R1__________________________,
    _________________ADJUST_L2__________________________,                    _________________ADJUST_R2__________________________,
    _________________ADJUST_L3__________________________,                    _________________ADJUST_R3__________________________,
                                     __________BLANK__________,        __________BLANK__________
  )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_default_layer_state(void) {
    oled_write_P(PSTR("Lyout"), false);
    switch (get_highest_layer(default_layer_state)) {
        case _COLEMAK:
            oled_write_P(PSTR(" COLE"), false);
            break;
        case _QWERTY:
            oled_write_P(PSTR(" QRTY"), false);
            break;
    }
}

void render_layer_state(void) {
    oled_write_P(PSTR("LAYER"), false);
    oled_write_P(PSTR("Lower"), layer_state_is(_LOWER));
    oled_write_P(PSTR("Raise"), layer_state_is(_RAISE));
    oled_write_P(PSTR("ModL "), layer_state_is(_MODL));
    oled_write_P(PSTR("ModR "), layer_state_is(_MODR));
    oled_write_P(PSTR("Adjst"), layer_state_is(_ADJUST));
}

void render_keylock_status(uint8_t led_usb_state) {
    oled_write_P(PSTR("Lock:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR("C"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write_ln_P(PSTR("S"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}


void render_status_main(void) {
    /* Show Keyboard Layout  */
    render_default_layer_state();
    render_keylock_status(host_keyboard_leds());
    render_layer_state();
}

void render_status_secondary(void) {
    /* Show Keyboard Layout  */
    render_default_layer_state();
    render_layer_state();
    render_mod_status(get_mods() | get_oneshot_mods());
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 30000) {
        oled_off();
        return;
    }
#    ifndef SPLIT_KEYBOARD
    else {
        oled_on();
    }
#    endif

    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
#endif
#ifndef SPLIT_KEYBOARD
        if (keycode == RESET && !is_master) {
            return false;
        }
#endif
    }
 

  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case MODL:
      if (record->event.pressed) {
        layer_on(_MODL);
      } else {
        layer_off(_MODL);
      }
      return false;
      break;
    case MODR:
      if (record->event.pressed) {
        layer_on(_MODR);
      } else {
        layer_off(_MODR);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
