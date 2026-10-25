// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80057E2C-0x80057E7C (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct { char pad[0xB0]; s16 unk0xB0; char pad2[2]; s32 unk0xB4; } Disp57;
void fn_8005F258(s32);
void fn_80057E2C(Unk_C8FEE62D *arg0) {
    register Unk_C8FEE62D *temp_r9 __asm__("r9");
    register s32 var_r3 __asm__("r3");
    register s32 off __asm__("r0");
    register s32 (*temp_r9_2)(void *) __asm__("r9");

    temp_r9 = arg0;
    var_r3 = temp_r9->unk0x10;
    if (var_r3 == 0) {
        var_r3 = temp_r9->unk0x14;
        __asm__("" : "+r"(var_r3), "+r"(temp_r9));
        temp_r9 = (Unk_C7387A53 *)((Unk_C7387A53 *)var_r3)->unk0xC;
        __asm__("" : "+r"(temp_r9), "+r"(var_r3));
        off = (s16)(*(volatile s16 *)&((Disp57 *)temp_r9)->unk0xB0);
        temp_r9_2 = (s32 (*)(void *))((Disp57 *)temp_r9)->unk0xB4;
        __asm__("" : "+r"(temp_r9_2), "+r"(off), "+r"(var_r3));
        var_r3 = var_r3 + off;
        temp_r9_2(var_r3);
        return;
    }
    fn_8005F258(arg0->unk0x10);
}
