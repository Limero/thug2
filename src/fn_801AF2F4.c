// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AF2F4-0x801AF37C (136B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_801AED74(s32);
extern s32 strcmp(char *, char *);
s32 fn_801AF2F4(CStruct *arg0, char *arg1) {
    register void *walk_r9 __asm__("r9");
    Unk_C7387A53 *var_r31;
    s32 var_r30;

    walk_r9 = arg0->unk0x10;
    var_r30 = 0;
    if ((s32)((CStruct *)walk_r9)->unk0x4 == -1) {
        walk_r9 = NULL;
    }
    var_r31 = walk_r9;
    while (var_r31 != NULL) {
        if (strcmp((char *)fn_801AED74((s32)var_r31), arg1) == 0) {
            return var_r30;
        }
        walk_r9 = var_r31->unk0xC;
        if ((s32)((CStruct *)walk_r9)->unk0x4 == -1) {
            walk_r9 = NULL;
        }
        var_r30 += 1;
        var_r31 = walk_r9;
    }
    return -1;
}
