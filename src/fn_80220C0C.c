// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80220C0C-0x80220CC8 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80128294(CStruct * arg0, void * arg1, void *arg2, s32 arg3);
CScript *fn_8021D454(s32 arg0, CStruct * arg1, s32 arg2);
CScript *fn_8021D4E8(s32 arg0, CStruct * arg1, s32 arg2);
s32 fn_80229BAC(CScript * arg0);
extern char lbl_802AFE9C[];
extern char lbl_802A83F8[];
extern s32 lbl_80305F9C;
bool ScriptTeamFlagTaken(CStruct *arg0) {
    struct { s32 o0; s32 o4; s32 o8; s32 pad; s32 sp18; } fr;
    register s32 *q __asm__("r30");
    register CStruct *q4 __asm__("r4");
    s32 *wp;
    s32 temp_r31;
    CScript *entry;
    q = &fr.o0;
    q[1] = 0;
    q[2] = (s32)lbl_802A83F8;
    temp_r31 = lbl_80305F9C;
    fn_80128294(arg0, (s32)lbl_802AFE9C, &fr.sp18, 0);
    entry = fn_8021D454(temp_r31, (CStruct *)&fr, 0);
    wp = q;
    while (entry != 0) {
        if (fn_80229BAC(entry) == fr.sp18) {
            wp[2] = (s32)lbl_802A83F8;
            return true;
        }
        q4 = (CStruct*)&fr.o0;
        entry = fn_8021D4E8(temp_r31, q4, 0);
    }
    wp[2] = (s32)lbl_802A83F8;
    return false;
}
