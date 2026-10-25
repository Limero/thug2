// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AF434-0x801AF4A8 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 strcmp(char *, char *);
extern char *fn_801AED74(s32);
extern void fn_801AED44(Unk_C7387A53 *);
void fn_801AF434(CStruct *arg0, void *arg1) {
    register s32 var_r9 __asm__("r9");
    register s32 var_r3 __asm__("r3");
    Unk_C7387A53 *var_r31;
    s32 t;

    var_r9 = arg0->unk0x10;
    t = ((CStruct *)var_r9)->unk0x4;
    var_r3 = var_r9;
    if (t == -1) {
        var_r3 = NULL;
    }
    var_r31 = var_r3;
    for (;;) {
        if (var_r31 == 0) {
            break;
        }
        if (strcmp(fn_801AED74(var_r31), (char *)arg1) == 0) {
            fn_801AED44((void *)var_r31);
            break;
        }
        var_r9 = var_r31->unk0xC;
        t = ((CStruct *)var_r9)->unk0x4;
        var_r3 = var_r9;
        if (t == -1) {
            var_r3 = NULL;
        }
        var_r31 = var_r3;
    }
}
