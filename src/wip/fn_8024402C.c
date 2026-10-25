// PARKED 2026-09-18 — FRAME SIZE SHORT + SPURIOUS CRCLR (assessed).
// 11.7% (14/120 words). got 456B vs want 480B; the 24-byte delta
// is the FRAME: want stwu -0x40 with `stmw r25,0x24` (locals 8..0x24 = 0x1c B)
// vs got stwu -0x38 / stmw r25,0x1c (locals 8..0x1c = 0x14 B, 8 B short). Two
// concrete defects visible in the first 0x60 bytes:
//  1. got emits `crclr cr1eq` at +0x3c where want has `li r9,0`. The call
//     `fn_80240B0C(&sp8, 0, 0, 0, 0, 0)` is declared with a 5-arg prototype but
//     m2c's argument list is speculative (doc-52 phantom-arg class) — an
//     unprototyped/varargs call is what emits cr1eq. Re-derive fn_80240B0C's
//     real arity from a matched caller before touching the body.
//  2. The sp8 build block diverges immediately: want `li r9,0;
//     lwz r11,4(r31); cmpwi r11,0; lhz r0,4(r11); addi r9,r1,8` (i.e. the
//     16-bit field is COPIED while the base stays in r9), got stores the half
//     word immediately (`sth r0,0xc(r1)`) and loads `*r9` — the `Unk_2F6F6F9D
//     sp8` member access shape and the `*(s32 *)((char *)&sp8 + 0x5/+0x3)`
//     byte-offset puns both need re-typing from the want loads (doc-51-style
//     symbol/field work), not permuting.
//
// family=m2c range=0x8024402C-0x8024420C size=480B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// UPDATED 2026-09-15: phantom-arg drop (addr-literal + bare-0 classes); now 11.7%.
#include "structs.h"
s32 fn_80243EFC(s32, s32, s32);
static s32 unksp12;
void fn_8024402C(Unk_7044F700 *arg0, Unk_A5D07D11 *arg1, s32 arg2, s32 arg3, CStruct *arg4) {
    Unk_12E59EE9 sp1C;
    Unk_12E59EE9 sp18;
    u16 sp14;
    s32 sp10;
    Unk_2F6F6F9D sp8;
    s32 temp_r0;
    s32 temp_r0_2;
    u8 var_r0;
    u8 var_r11;
    Unk_F5317C5D *temp_r11;
    fn_80240B0C(&sp8, 0, 0, 0, 0, 0);
    temp_r11 = arg0->unk0x4;
    if (temp_r11 != NULL) {
        sp8.unk0x4 = (u16) temp_r11->unk0x4;
        *((s32 *)&sp8) = temp_r11->unk0x0;
    } else {
        *(s32 *)((char *)&sp8 + 0x5) = 1;
        *(s32 *)((char *)&sp8 + 0x3) = 1;
        sp8.unk0x4 = 1;
    }
    temp_r0 = (arg4->unk0x3C + arg0->unk0xC) & 3;
    switch (temp_r0) {                              
    case 2:                                         
    case 0:                                         
        var_r0 = *(s32 *)((char *)&sp8 + 0x5);
        var_r11 = *(s32 *)((char *)&sp8 + 0x3);
block_12:
        arg1->unk0x4 = 1;
        *(s32 *)((char *)arg1 + (s32)0x3) = var_r11;
        *(s32 *)((char *)arg1 + (s32)0x5) = var_r0;
        break;
    case 1:                                         
    case 3:                                         
        var_r0 = *(s32 *)((char *)&sp8 + 0x3);
        var_r11 = *(s32 *)((char *)&sp8 + 0x5);
        goto block_12;
    }
    *((s32 *)&sp18) = arg0->unk0x8 - arg2;
    *((s32 *)&sp1C) = ((Unk_2A99262E *)arg0)->unk0xA - arg3;
    fn_80243EFC(&sp18, &sp1C, arg4->unk0x3C);
    temp_r0_2 = arg4->unk0x3C;
    switch (temp_r0_2) {                            
    case 1:                                         
        *((s32 *)&sp1C) = (*((s32 *)&sp1C) + 1) - arg0->unk0x10;
        break;
    case 2:                                         
        *((s32 *)&sp18) = (*((s32 *)&sp18) + 1) - arg0->unk0x10;
        *((s32 *)&sp1C) = (*((s32 *)&sp1C) + 1) - *(s32 *)((char *)arg0 + (s32)0x11);
        break;
    case 3:                                         
        *((s32 *)&sp18) = (*((s32 *)&sp18) + 1) - *(s32 *)((char *)arg0 + (s32)0x11);
        break;
    }
    sp10 = arg4->unk0x4;
    *((s8 *)&arg1->unk0x2) = (s8) (unksp12 + sp1C.unk0x3);
    sp14 = arg4->unk0x8;
    arg1->unk0x0 = (s8) ((u8) sp10 + sp18.unk0x3);
    arg1->unk0x1 = (u8) ((Unk_2A99262E *)arg0)->unk0x9;
}
