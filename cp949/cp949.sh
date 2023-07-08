#!/usr/bin/env python

lines: list[str]
with open("cp949.txt", "r") as fp:
    lines = fp.readlines()

res = ['0xFFFFFFFF' for _ in range(65536)]

dat: list[list[str]] = [line.split('\t') for line in lines]
dat: list[tuple[int, int, str]] = [(int(cp949, 16), int(utf16, 16) if ' ' not in utf16 else 0xFFFFFFFF, comment) for cp949, utf16, comment in dat]
dat: list[tuple[int, int, str]] = [(p, 0xFFFFFFFE if "#DBCS LEAD BYTE" in c else u, c) for p, u, c in dat]

for p, u, c in dat:
    res[p] = f'0x{u:04X}'

with open("../cp949.g.h", "w") as fp:
    fp.write("""
/*
 * ========================================================================
 * https://www.unicode.org/Public/MAPPINGS/VENDORS/MICSFT/WINDOWS/CP949.TXT
 *
 * Name:            CP949-to-Unicode-table
 * Unicode version: 2.0
 * Table version:   2.01
 * Date:            1/7/2000
 * Contact:         Shawn.Steele@microsoft.com
 * ========================================================================
 */

#ifndef BOB_DECRYPTOR_CP949_G_H
#define BOB_DECRYPTOR_CP949_G_H

#include <stdint.h>
#include <limits.h>

extern uint32_t __cp949[UINT16_MAX + 1];

#endif // BOB_DECRYPTOR_CP949_H
    """)

with open("../cp949.g.c", "w") as fp:
    fp.write(f"""
/*
 * ========================================================================
 * https://www.unicode.org/Public/MAPPINGS/VENDORS/MICSFT/WINDOWS/CP949.TXT
 *
 * Name:            CP949-to-Unicode-table
 * Unicode version: 2.0
 * Table version:   2.01
 * Date:            1/7/2000
 * Contact:         Shawn.Steele@microsoft.com
 * ========================================================================
 */

#include "cp949.g.h"

uint32_t __cp949[UINT16_MAX + 1] = {{{','.join(res)}}};

    """)
