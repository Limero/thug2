// Promoted from src/wip (m2c draft hand-refined to exact match).
// range 0x800F1A3C-0x800F1AD8 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80129528(CStruct *, s32);
s32 fn_800F1A3C(Unk_A231C4C2 *arg0) {
    s32 temp_r9_2;
    s32 temp_r9_3;
    s32 temp_r3;
    s32 var_limit;
    CStruct *temp_r30;
    void *temp_r9;

    if (arg0->unk0x10004 == -1) {
        return 0;
    }
    temp_r9 = (char *)arg0 + 0x10010;
    temp_r30 = (CStruct *)*(s32 *)((char *)temp_r9 + arg0->unk0x10002 * 0xC);
    temp_r3 = fn_80129528(temp_r30, arg0->unk0x10004);
    var_limit = temp_r30->unk0x4;
    temp_r9_2 = (u16)arg0->unk0x10004 + 1;
    arg0->unk0x10004 = temp_r9_2;
    if ((s16)temp_r9_2 >= var_limit) {
        temp_r9_3 = (u16)arg0->unk0x10002 + 1;
        arg0->unk0x10004 = 0;
        arg0->unk0x10002 = temp_r9_3;
        if ((u16)temp_r9_3 >= (u32)arg0->unk0x10008) {
            arg0->unk0x10004 = -1;
        }
    }
    return temp_r3;
}
