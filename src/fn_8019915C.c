// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019915C-0x801992A8 (332B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80305F9C;

s32 GetText(s32, s32, s32, s32);
s32 fn_8009CF2C(s32);
s32 fn_80125994(s32, s32);
CStruct *fn_801259C8(u32, s32);
void fn_80126FF4(CStruct *, s32);
void CStruct_dtor(CStruct *);
s32 fn_80128E34(s32, u32, s32 *, s32);
s32 fn_80129528(CStruct *, u32);
void fn_801980C4(s32);
void fn_80198190(s32);
void fn_80198D08(s32, s32);
s32 fn_80198D38(s32);

bool fn_8019915C(s32 arg0, s32 arg1) {
    CStruct *st;
    s32 handle;
    s32 width;
    s32 el;
    s32 checksum;
    s32 def;
    u32 i;

    handle = lbl_80305F9C;
    width = 8;
    if (handle != 0 && fn_8009CF2C(handle) != 0) {
        width = fn_80198D38(arg0);
    }
    CStruct_dtor((CStruct *)(arg0 + 4));
    st = fn_801259C8(QB_MODE_INFO, 1);
    for (i = 0; i < (u32)st->unk0x4; i++) {
        el = fn_80129528(st, i);
        fn_80128E34(el, QB_CHECKSUM, &checksum, 1);
        if (checksum == arg1) {
            GetText(el, QB_DEFINITION, &def, 1);
            fn_80126FF4((CStruct *)(arg0 + 4), fn_80125994(def, 1));
            fn_801980C4(arg0);
            fn_80198190(arg0);
            if (handle != 0 && fn_8009CF2C(handle) != 0) {
                fn_80198D08(arg0, width);
            }
            return true;
        }
    }
    return false;
}
