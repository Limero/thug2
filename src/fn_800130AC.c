// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800130AC-0x80013118 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_8031349C[];
extern char lbl_8031362C[];
void fn_800130AC(s32 arg0, s32 arg1) {
    s32 *var_r9;
    s32 var_ctr;
    s32 var_ctr_2;
    char *var_r9_2;

    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        var_ctr = 0x64;
        var_r9 = lbl_8031349C;
        var_r9 += 0x63;
        do {
            *var_r9 = 0;
            var_r9 -= 1;
            var_ctr -= 1;
        } while (var_ctr != 0);
        var_ctr_2 = 0xC8;
        var_r9_2 = lbl_8031362C;
        do {
            ((CStruct *)var_r9_2)->unk0x0 = 0;
            ((CStruct *)var_r9_2)->unk0x4 = 0;
            ((CStruct *)var_r9_2)->unk0x8 = 0;
            ((CStruct *)var_r9_2)->unk0xC = 0;
            var_r9_2 += 0x10;
            var_ctr_2 -= 1;
        } while (var_ctr_2 != 0);
    }
}