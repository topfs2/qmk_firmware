/*
Copyright 2017 Tobias Arrskog <tobias.arrskog@gmail.com> @topfs2

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


#pragma once
#include QMK_KEYBOARD_H

#include "wrappers.h"

#define _COLEMAK 0
#define _QWERTY 1
#define _LOWER 2
#define _RAISE 3
#define _MODL 4
#define _MODR 5
#define _ADJUST 6

enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  QWERTY,
  LOWER,
  RAISE,
  MODL,
  MODR,
  ADJUST,

  RGBRST
};
