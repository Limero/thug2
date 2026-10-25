// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80181AC0-0x80181C00 (320B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void *fn_80182F98(CStruct *, s32);
s32 Script_GetInteger(s32, s32);
typedef struct { s32 u0; s32 u4; s32 u8; s32 uC; s32 u10; s32 u14; s32 u18; } EntAC0;
s32 fn_80181AC0(Unk_FFAD6788 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    CStruct *a0 = (CStruct *)arg0;
    s32 count = 0;
    s32 a1 = arg1;
    s32 a2 = arg2;
    s32 v = 1;
    s32 i = 0;
    s32 mul;
    CStruct *base;
    EntAC0 *e;
    if (count < arg0->unk0x68) {
        mul = a2 * 0xB4;
        base = (CStruct *)((char *)a0 + 0x54);
        do {
            e = (EntAC0 *)fn_80182F98(base, i);
            if (e->u18 & 2) {
                v = 1;
            } else if ((i == 0) || ((i > 0) && (((EntAC0 *)fn_80182F98(base, i - 1))->u18 & 2))) {
                v = ((EntAC0 *)fn_80182F98(base, i))->u8;
            }
            e = (EntAC0 *)fn_80182F98(base, i);
            if (e->u10 == a1) {
                if (a2 == 0) {
                    count += 1;
                } else if (a2 == v) {
                    if (arg3 == 0) {
                        count += 1;
                    } else {
                        EntAC0 *e5 = (EntAC0 *)fn_80182F98(base, i);
                        s32 q = e5->uC;
                        s32 ab = abs(q);
                        s32 d = ab - mul;
                        s32 ad = abs(d);
                        if (ad < Script_GetInteger(QB_PERFECT_LANDING_SLOP, 0)) {
                            count += 1;
                        }
                    }
                }
            }
            i += 1;
        } while (i < arg0->unk0x68);
    }
    return count;
}
