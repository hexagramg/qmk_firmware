// Copyright 2021 Konstantin (@Konstantin)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
        L01, L02, L03, L04, L05, L06,                R06, R05, R04, R03, R02, R01, \
   L10, L11, L12, L13, L14, L15, L16,                R16, R15, R14, R13, R12, R11, R10, \
        L21, L22, L23, L24, L25, L26,                R26, R25, R24, R23, R22, R21, \
             L31, L32, L33, L34, L35, L36, R36, R35, R34, R33, R32, R31 \
) \
{ \
    { KC_NO, L01, L02, L03, L04, L05, L06 }, \
    { L10,   L11, L12, L13, L14, L15, L16 }, \
    { KC_NO, L21, L22, L23, L24, L25, L26 }, \
    { KC_NO, L31, L32, L33, L34, L35, L36 }, \
    { KC_NO, R01, R02, R03, R04, R05, R06 }, \
    { R10,   R11, R12, R13, R14, R15, R16 }, \
    { KC_NO, R21, R22, R23, R24, R25, R26 }, \
    { KC_NO, R31, R32, R33, R34, R35, R36 } \
}
