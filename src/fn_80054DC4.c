// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80054DC4-0x80054E1C (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80364C28[];
void *fn_80054DC4(s32 arg0) {
    Unk_C7387A53 *temp_r3;
    CStruct *var_r9;
    register s32 cur __asm__("r11");

    cur = (s32)*(void * *)&lbl_80364C28;
    if (*(s32 *)((char *)cur + 4) == -1) {
        cur = 0;
    }
    while (cur != 0) {
        var_r9 = (CStruct *)(*(s32 *)((char *)cur + 0xC));
        if ((s32) var_r9->unk0x4 == -1) {
            var_r9 = NULL;
        }
        temp_r3 = (Unk_C7387A53 *)(*(s32 *)((char *)cur + 4));
        if ((s32) temp_r3->unk0x80 == arg0) {
            return temp_r3;
        }
        cur = (s32)var_r9;
    }
    return NULL;
}
