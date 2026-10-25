// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80221C00-0x80221CB4 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80219698(CStruct * arg0);
s32 fn_8021D454(s32 arg0, CStruct * arg1, s32 arg2);
s32 fn_8021D4E8(s32 arg0, CStruct * arg1, s32 arg2);
extern char lbl_802A83F8[];
extern s32 lbl_80305F9C;
bool ScriptAllPlayersAreReady(void) {
    s64 sp8;
    s32 temp_r31;
    Unk_31DE137E *var_r3;
    s32 lblv;
    s64 _pad;
    register CStruct *q4 __asm__("r4");

    temp_r31 = lbl_80305F9C;
    lblv = (s32)lbl_802A83F8;
    ((Unk_59AB5482 *)&sp8)->unk0x4 = 0;
    ((Unk_59AB5482 *)&sp8)->unk0x8 = lblv;
    if (fn_80219698(temp_r31) != 0) {
        var_r3 = fn_8021D454(temp_r31, &sp8, 1);
        while (var_r3 != 0) {
            __asm__("" : : "m"(_pad));
            if (!(*(s32 *)(var_r3->unk0x1C + 0x68) & 1)) {
                ((Unk_59AB5482 *)&sp8)->unk0x8 = lblv;
                return false;
            }
            q4 = (CStruct *)&sp8;
            var_r3 = fn_8021D4E8(temp_r31, q4, 1);
        }
    }
    ((Unk_59AB5482 *)&sp8)->unk0x8 = (s32)lbl_802A83F8;
    return true;
}
