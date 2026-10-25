// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006FD50-0x8006FE28 (216B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
typedef struct {
    char pad0x0[0x4];
    s32 unk0x4;
    s16 unk0x8;
    char pad0xA[0x2];
    s32 unk0xC;
} Unk_6FD50_vt;
extern char lbl_80294CD8[];
void fn_8006FD50(CStruct *arg0, s32 arg1) {
    void *temp_r11;
    register CStruct *temp_r9 __asm__("r9");
    register Unk_6FD50_vt *temp_r9_2 __asm__("r9");
    Unk_6FD50_vt *temp_r9_3;
    Unk_6FD50_vt *temp_r9_4;
    void *var_r11;
    void *var_r31;

    arg0->unk0x60 = (s32)lbl_80294CD8;
    temp_r9 = *(CStruct **)(*(s32 *)((char *)arg0 + 0x3C) + 0xC);
    {
        s32 t = (s32) temp_r9->unk0x4;

        var_r11 = temp_r9;
        if (t == -1) {
            var_r11 = NULL;
        }
    }
    if (var_r11 != NULL) {
        do {
            temp_r9_2 = ((Unk_C8FEE62D *)var_r11)->unk0xC;
            {
                s32 t = (s32) temp_r9_2->unk0x4;

                var_r31 = temp_r9_2;
                if (t == -1) {
                    var_r31 = NULL;
                }
            }
            if (var_r11 != NULL) {
                temp_r9_3 = ((Unk_C8FEE62D *)var_r11)->unk0x14;
                ((s32 (*)(void *, s32))temp_r9_3->unk0xC)(var_r11 + temp_r9_3->unk0x8, 3);
            }
            var_r11 = var_r31;
        } while (var_r11 != NULL);
    }
    temp_r11 = arg0->unk0x3C;
    if (temp_r11 != NULL) {
        temp_r9_4 = ((Unk_C8FEE62D *)temp_r11)->unk0x14;
        ((s32 (*)(void *, s32))temp_r9_4->unk0xC)(temp_r11 + temp_r9_4->unk0x8, 3);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
