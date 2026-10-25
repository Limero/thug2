// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80072230-0x800722A8 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8036B3A0[];
extern char lbl_80295358[];
extern char lbl_80295370[];
void fn_80072230(s32 arg0, s32 arg1) {
    s32 var_ctr;
    s32 var_r7;
    void *var_r9;

    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        var_r9 = (void *)lbl_8036B3A0;
        var_ctr = 0;
        var_r7 = 0;
        do {
            ((Unk_C8FEE62D *)var_r9)->unk0x4 = var_r9;
            ((Unk_C8FEE62D *)var_r9)->unk0x8 = 0;
            ((Unk_C8FEE62D *)var_r9)->unk0xC = var_r9;
            ((Unk_C8FEE62D *)var_r9)->unk0x10 = var_r9;
            ((Unk_C8FEE62D *)var_r9)->unk0x14 = (s32)lbl_80295370;
            var_r7 = 0x600;
            do {
                var_r7 -= 1;
            } while (var_r7 != 0);
            ((Unk_C8FEE62D *)var_r9)->unk0x14 = (s32)lbl_80295358;
            var_ctr -= 1;
            var_r9 += 0xC028;
        } while (var_ctr != -1);
    }
}
