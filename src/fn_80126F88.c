// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80126F88-0x80126FF4 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern void *fn_80126808(void *, void *, s32);
extern void fn_80127438(void *, void *);
extern s32 fn_801252BC(void);
extern void fn_8009F4C4(s32);
s32 fn_80126F88(Unk_80577C09 *arg0, CStruct *arg1) {
    Unk_C7387A53 *var_r31;
    s32 temp_r30;
    var_r31 = (Unk_C7387A53 *)arg1->unk0x4;
    if (var_r31 != NULL) {
        do {
            fn_8009F4C4(0x10);
            temp_r30 = fn_801252BC();
            fn_80126808(temp_r30, var_r31, 0);
            fn_80127438(arg0, temp_r30);
            var_r31 = var_r31->unk0xC;
        } while (var_r31 != NULL);
    }
    return (s32)arg0;
}
