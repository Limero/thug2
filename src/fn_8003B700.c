// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003B700-0x8003B984 (644B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 *lbl_803003F0;
extern s32 lbl_803003E8;
extern s32 lbl_803018F8;
void fn_80060490(s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 ContainsFlag(CStruct *, s32);
s32 GetString(CStruct *, s32 *, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
CStruct *fn_8003AB44(CStruct *, s32);
bool fn_8003B700(Unk_C7387A53 *arg0, s32 arg1) {
    s32 sp10;
    s32 sp14;
    CStruct *temp_r3;
    temp_r3 = fn_8003AB44(lbl_803003F0, arg1);
    if (temp_r3 != 0) {
        if (ContainsFlag(temp_r3, QB_SUPPORTS_LOGO) != 0) {
            lbl_803018F8 = 1;
        }
        sp10 = 0;
        GetInteger(temp_r3, QB_MULTICOLOR, &sp10, 0);
        if (GetString(temp_r3, QB_MESH, &sp14, 0) != 0) {
            fn_80060490(lbl_803003E8, sp14, arg1, arg0->unk0x58, arg0->unk0x5C, 0, (sp10 != 0), 1, 0);
        }
        if (GetString(temp_r3, QB_MESH1, &sp14, 0) != 0) {
            fn_80060490(lbl_803003E8, sp14, arg1, arg0->unk0x58, arg0->unk0x5C, 0, (sp10 != 0), 1, 0);
        }
        if (GetString(temp_r3, QB_MESH2, &sp14, 0) != 0) {
            fn_80060490(lbl_803003E8, sp14, arg1, arg0->unk0x58, arg0->unk0x5C, 0, (sp10 != 0), 1, 0);
        }
        if (GetString(temp_r3, QB_MESH3, &sp14, 0) != 0) {
            fn_80060490(lbl_803003E8, sp14, arg1, arg0->unk0x58, arg0->unk0x5C, 0, (sp10 != 0), 1, 0);
        }
        if (GetString(temp_r3, QB_MESH4, &sp14, 0) != 0) {
            fn_80060490(lbl_803003E8, sp14, arg1, arg0->unk0x58, arg0->unk0x5C, 0, (sp10 != 0), 1, 0);
        }
    }
    if (lbl_803018F8 != 0) {
        lbl_803018F8 = 0;
    }
    return true;
}
