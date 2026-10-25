// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800BE568-0x800BE604 (156B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8037D008[];
extern char lbl_8037E778[];
void fn_80105BF4(Unk_5CB48605 *);
void fn_800BE568(s32 arg0, s32 arg1) {
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32 var_ctr_4;
    u32 var_r9;
    void *var_r9_2;

    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        fn_80105BF4((s32)lbl_8037D008);
        var_ctr = 0x18;
        do {
            var_ctr -= 1;
        } while (var_ctr != 0);
        var_ctr_2 = 0x18;
        do {
            var_ctr_2 -= 1;
        } while (var_ctr_2 != 0);
        var_ctr_3 = 0x18;
        do {
            var_ctr_3 -= 1;
        } while (var_ctr_3 != 0);
        var_r9 = 1;
        do {
        } while (var_r9-- != 0u);
        var_ctr_4 = 8;
        var_r9_2 = (void *)lbl_8037E778;
        do {
            ((CStruct *)var_r9_2)->unk0x4 = 0;
            ((CStruct *)var_r9_2)->unk0x8 = 0;
            ((CStruct *)var_r9_2)->unk0x0 = 0;
            var_r9_2 += 0xC;
            var_ctr_4 -= 1;
        } while (var_ctr_4 != 0);
    }
}
