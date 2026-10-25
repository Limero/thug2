// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F559C-0x801F56BC (288B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -O1 -fschedule-insns -fschedule-insns2
#include "types.h"
void CStruct_delete(void *, s32);
void fn_801F56F0(void *);
s32 Script_RunScript(s32, void *, s32, s32, s32);
s32 AddString(void *, s32, s32);
void AddChecksum(void *, s32, s32);
#include "qb_constants.h"
#include "structs.h"
s32 fn_801F46B0(s32);
void CStruct_ctor(void *);
extern char lbl_802AE2F8[];
extern char lbl_802AE338[];
s32 fn_801F1714(s32, s32);
s32 fn_801F4820(Unk_13D0EFB0 *);
void fn_801F559C(Unk_F0C166E4 *arg0) {
    s32 sp8[2];
    s32 var_r30;
    s32 t;
    Unk_31DE137E *temp_r9;
    char *base;

    base = (char *)arg0 + 0x10000;
    switch (fn_801F46B0(*(s32 *)(base - 0x5400))) {
    case 2:
        var_r30 = (s32)lbl_802AE2F8;
        break;
    case 3:
        temp_r9 = (Unk_31DE137E *)*(s32 *)(base - 0x5400);
        t = temp_r9->unk0x114;
        var_r30 = fn_801F1714(t, fn_801F4820((Unk_13D0EFB0 *)temp_r9));
        break;
    default:
        var_r30 = (s32)lbl_802AE338;
        break;
    }
    CStruct_ctor(sp8);
    switch (fn_801F46B0(arg0->unk0xAC00)) {
    case 1:
        AddChecksum(sp8, QB_TYPE, QB_PED);
        break;
    case 4:
        AddChecksum(sp8, QB_TYPE, QB_CHECKPOINT);
        break;
    }
    AddString(sp8, QB_MODEL, var_r30);
    Script_RunScript(QB_GOAL_EDITOR_CREATE_CURSOR, sp8, arg0->unk0xC, 0, 0);
    fn_801F56F0(arg0);
    CStruct_delete(sp8, 2);
}
