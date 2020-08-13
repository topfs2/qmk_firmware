#pragma once
#include "topfs2.h"

/*
Since our quirky block definitions are basically a list of comma separated
arguments, we need a wrapper in order for these definitions to be
expanded before being used as arguments to the LAYOUT_xxx macro.
*/
#if (!defined(LAYOUT) && defined(KEYMAP))
#    define LAYOUT KEYMAP
#endif

// clang-format off
#define LAYOUT_ergodox_wrapper(...)          LAYOUT_ergodox(__VA_ARGS__)
#define LAYOUT_ergodox_pretty_wrapper(...)   LAYOUT_ergodox_pretty(__VA_ARGS__)
#define KEYMAP_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_ortho_4x12_wrapper(...)       LAYOUT_ortho_4x12(__VA_ARGS__)
#define LAYOUT_ortho_5x12_wrapper(...)       LAYOUT_ortho_5x12(__VA_ARGS__)
#define LAYOUT_gergo_wrapper(...)            LAYOUT_gergo(__VA_ARGS__)

/*
Blocks for each of the four major keyboard layouts
Organized so we can quickly adapt and modify all of them
at once, rather than for each keyboard, one at a time.
And this allows for much cleaner blocks in the keymaps.
For instance Tap/Hold for Control on all of the layouts	

NOTE: These are all the same length.  If you do a search/replace
  then you need to add/remove underscores to keep the
  lengths consistent.
*/

#define _________THUMB_L_________                                  KC_LGUI, LOWER,   KC_BSPC
#define _________THUMB_R_________                                  KC_SPC,  RAISE,   KC_RALT

#define _________________COLEMAK_L1_________________________       KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define _________________COLEMAK_L2_________________________       KC_LSFT, KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define _________________COLEMAK_L3_________________________       KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________COLEMAK_R1_________________________       KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL
#define _________________COLEMAK_R2_________________________       KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT
#define _________________COLEMAK_R3_________________________       KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH,KC_ENT

#define _________COLEMAK_LT_______                                 _________THUMB_L_________
#define _________COLEMAK_RT_______                                 _________THUMB_R_________

#define _________________QWERTY_L1__________________________       _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2__________________________       _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3__________________________       _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1__________________________       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______
#define _________________QWERTY_R2__________________________       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______
#define _________________QWERTY_R3__________________________       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH,_______

#define _________QWERTY_LT________                                 _________THUMB_L_________
#define _________QWERTY_RT________                                 _________THUMB_R_________

#define ___________________BLANK____________________________       _______, _______, _______, _______, _______, _______
#define ___________________BLANK___________________                _______, _______, _______, _______, _______
#define __________BLANK__________                                  _______, _______, _______

#define _________________LOWER_L1___________________________       _______, KC_CIRC, KC_LCBR, KC_RCBR, KC_PIPE, KC_GRV
#define _________________LOWER_L2___________________________       _______, KC_AT,   KC_AMPR, KC_EXLM, KC_TILD, KC_DLR
#define _________________LOWER_L3___________________________       _______, KC_LBRC, KC_LPRN, KC_RPRN, KC_RBRC, KC_BSLS

#define _________________LOWER_R1___________________________       _______, KC_PERC, KC_UNDS, _______, _______, _______
#define _________________LOWER_R2___________________________       KC_HASH, KC_PEQL, KC_PAST, KC_PPLS, KC_PMNS, _______
#define _________________LOWER_R3___________________________       _______, _______, KC_LT,   KC_GT,   KC_PSLS, _______


#define _________LOWER_LT________                                  __________BLANK__________
#define _________LOWER_RT________                                  KC_ENT,  _______, KC_RGUI

#define _________________RAISE_L1___________________________       _______, _______, _______, _______, KC_PERC, _______
#define _________________RAISE_L2___________________________       _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define _________________RAISE_L3___________________________       _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0

#define _________________RAISE_R1___________________________       KC_DOWN, KC_RGHT, _______, _______, _______, _______
#define _________________RAISE_R2___________________________       KC_LEFT, _______, _______, _______, _______, _______
#define _________________RAISE_R3___________________________       KC_UP,   _______, _______, _______, _______, _______

#define _________RAISE_LT________                                  __________BLANK__________
#define _________RAISE_RT________                                  __________BLANK__________

#define _________________ADJUST_L1__________________________       RESET,   QWERTY,  _______, _______, _______, _______
#define _________________ADJUST_L2__________________________       _______, _______, _______, _______, _______, _______
#define _________________ADJUST_L3__________________________       _______, _______, _______, COLEMAK, _______, _______

#define _________________ADJUST_R1__________________________       KC_PGDN, KC_END,  KC_VOLU, _______, _______, _______
#define _________________ADJUST_R2__________________________       KC_HOME, KC_MPRV, KC_VOLD, KC_MNXT, _______, SFT_QUOT
#define _________________ADJUST_R3__________________________       KC_PGUP, _______, _______, _______, _______, _______

// clang-format on
