// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80152CD0-0x80152D84 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 fn_801746A4(Unk_C7387A53 *, s32);
void fn_8009F9AC(Unk_6A70655D *, void *);
bool ScriptUnPauseSkaters(void) {
    s32 var_r0;
    u32 var_r29;
    u32 var_r30;
    CStruct *temp_r11;
    Unk_C7387A53 *temp_r28;
    Unk_9994C3F5 *temp_r3;
    Unk_2C7D9FAD *temp_r9;
    register void *var_r9 __asm__("r9");

    var_r29 = 0U;
    temp_r28 = (void *)lbl_80305EAC;
    temp_r11 = *((void * *)&temp_r28->unk0x38);
    var_r0 = temp_r11->unk0x4;
    var_r9 = temp_r11;
    __asm__("" : "+r"(var_r9) : "r"(var_r0), "r"(temp_r11));
    while ((((var_r0 == -1) && (var_r9 = NULL)), var_r9 != NULL)) {
        var_r9 = *((void * *)&((CStruct *)var_r9)->unk0xC);
        var_r29 += 1;
        var_r0 = ((CStruct *)var_r9)->unk0x4;
    }
    __asm__("" :: "r"(var_r9));
    for (var_r30 = 0U; var_r30 < var_r29; var_r30++) {
        temp_r3 = (void *)fn_801746A4((s32)temp_r28, var_r30);
        if (temp_r3 != NULL) {
            temp_r9 = *((void * *)&temp_r3->unk0x8);
            ((s32 (*)(void *))temp_r9->unk0x6C)((void *)((char *)temp_r3 + temp_r9->unk0x68));
            fn_8009F9AC(temp_r3, 0);
        }
    }
    return true;
}
