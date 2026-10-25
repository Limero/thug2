// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A26E0-0x801A275C (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 fn_801A269C(Unk_31DE137E *);
void *fn_801A26E0(Unk_31DE137E *arg0, s32 arg1) {
    register CStruct *w9 __asm__("r9");
    CStruct *temp_r31;
    s32 temp_r28;
    Unk_C7387A53 *var_r3;
    u32 var_r4;
    s32 f4;

    if (fn_801A269C(arg0) == 0) {
        return NULL;
    }
    temp_r31 = (CStruct *)arg0;
    temp_r28 = arg1;
    w9 = (CStruct *)temp_r31->unk0x64;
    var_r4 = temp_r28;
    while (1) {
        f4 = w9->unk0x4;
        var_r3 = (Unk_C7387A53 *)w9;
        if (f4 == -1) {
            var_r3 = NULL;
        }
        if (var_r3 == 0) {
            break;
        }
        if (var_r4-- == 0) {
            return var_r3;
        }
        w9 = (CStruct *)var_r3->unk0xC;
    }
    return NULL;
}
