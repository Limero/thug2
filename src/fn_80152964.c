// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80152964-0x80152A4C (232B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8009F27C(CStruct *, Unk_15EF4A35 *, void *, void *, void *);
s32 GetStructure_3(CStruct *, void *, void *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
s32 GetChecksum_4(CStruct *, void *, void *, void *);
s32 ContainsFlag(CStruct *, void *);
s32 fn_8012EF68(Unk_FFAD6788 *, Unk_15EF4A35 *);
s32 fn_801319F8(Unk_FFAD6788 *);
extern char lbl_802A7D78[];
extern char lbl_802A7D7C[];
bool ScriptSpawnSound(CStruct *arg0, Unk_FFAD6788 *arg1) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r30;

    if ((s32) arg1->unk0xBC == 0) {
        return ScriptSpawnScript();
    }
    if (GetChecksum_2(arg0, 0, &sp8, 0) != 0) {
        spC = 0;
        spC = fn_801319F8(arg1);
        GetChecksum_4(arg0, (s32)lbl_802A7D78, &spC, 0);
        sp10 = 0;
        GetStructure_3(arg0, (s32)lbl_802A7D7C, &sp10, 0);
        temp_r30 = fn_8009F27C(arg1->unk0xBC, sp8, sp10, spC, 0);
        if (ContainsFlag(arg0, QB_NOQBID) == 0) {
            fn_8012EF68(temp_r30, arg1);
        }
    }
    return true;
}
