// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020D2E4-0x8020D530 (588B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct { f32 x; f32 y; f32 z; f32 w; } F32Vec4;
extern f32 lbl_802AF4C8;
extern f32 lbl_802AF4CC;
extern f32 lbl_802AF4D0;
extern f32 lbl_802AF4D4;
extern char lbl_802AF4D8[];
extern s32 lbl_80303150;

s32 Tmr_GetTime();
s32 fn_800145AC();
s32 GetStructure(s32 arg0, s32 arg1);
s32 GetFloat(CStruct * arg0, s32 arg1, f32 * arg2, s32 arg3);

void fn_8020D2E4(Unk_6553C923 *arg0, s32 arg1) {
    f32 out[4];
    s32 old;
    s32 conv;
    register f32 pf __asm__("fr31");
    f32 *fp;
    f32 prod;
    Unk_CFB386B2 *t;

    old = arg0->unk0x1C;
    if (arg1 != old) {
        arg0->unk0x24 = old;
        arg0->unk0x1C = arg1;
        arg0->unk0x20 = lbl_80303150 + Tmr_GetTime();
        if ((u32)arg0->unk0x24 <= 1U) {
            arg0->unk0x1874 = 0;
            arg0->unk0x1870 = 0;
        }
        if (arg0->unk0x24 == 1) {
            f32 c8 = lbl_802AF4C8;
            f32 cc;
            F32Vec4 *v = (F32Vec4 *)&arg0->unk0x1980;
            cc = lbl_802AF4CC;
            arg0->unk0x1978 = c8;
            v->x = c8;
            v->y = c8;
            v->z = c8;
            v->w = cc;
            arg0->unk0xB0 = 0;
        }
        if (arg0->unk0x1C == 0) {
            f32 d0 = lbl_802AF4D0;
            arg0->unk0x1950 = 1;
            arg0->unk0x194C = d0;
        }
        if (arg0->unk0x1C == 4) {
            f32 c8 = lbl_802AF4C8;
            f32 cc;
            F32Vec4 *v = (F32Vec4 *)&arg0->unk0x1A20;
            cc = lbl_802AF4CC;
            v->x = c8;
            v->y = c8;
            v->z = c8;
            v->w = cc;
        }
        if (arg0->unk0x1C != 1) {
            arg0->unk0x1998 = 0;
        }
        if ((arg0->unk0x1C == 0) || (arg0->unk0x24 != 1)) {
            arg0->unk0x1948 = 0;
        }
        if (arg0->unk0x1C == 2) {
            arg0->unk0x19C8 = lbl_802AF4C8;
            if (arg0->unk0x24 == 1) {
                t = (char *)arg0->unk0x183C + 0x24;
                GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_HANG_CONTROL_DEBOUNCE_TIME, &out[0], 1);
                pf = out[0];
                t->unk0x274 = fn_800145AC() + (s32)(u32)(pf * lbl_802AF4D4);
                GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_HANG_CONTROL_DEBOUNCE_TIME, &out[1], 1);
                pf = out[1];
                t->unk0x278 = fn_800145AC() + (s32)(u32)(pf * lbl_802AF4D4);
            }
        }
    }
}
