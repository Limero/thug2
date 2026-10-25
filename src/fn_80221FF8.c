// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80221FF8-0x8022208C (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8021D454(s32 arg0, CStruct * arg1, s32 arg2);
s32 fn_8021D4E8(s32 arg0, CStruct * arg1, s32 arg2);
extern char lbl_802A83F8[];
extern s32 lbl_80305F9C;
bool ScriptCancelRemovePlayer(CStruct *pParams, CScript *pScript) {
    s64 sp8;
    s32 temp_r31;
    CScript *var_r9;
    register s32 var_r4 __asm__("r4");
    s64 _pad;
    register s32 msk __asm__("r30");
    temp_r31 = lbl_80305F9C;
    ((Unk_59AB5482 *)&sp8)->unk0x8 = (s32)lbl_802A83F8;
    ((Unk_59AB5482 *)&sp8)->unk0x4 = 0;
    var_r9 = fn_8021D454(temp_r31, &sp8, 0);
    if (var_r9 != 0) {
        msk = ~0x400;
        do {
            __asm__("" : : "m"(_pad));
            var_r9->unk0x1D8 &= msk;
            var_r4 = (s32)((char *)&sp8);
            var_r9 = fn_8021D4E8(temp_r31, (void *)var_r4, 0);
        } while (var_r9 != 0);
    }
    ((Unk_59AB5482 *)&sp8)->unk0x8 = (s32)lbl_802A83F8;
    return true;
}
