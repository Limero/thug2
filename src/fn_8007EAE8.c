// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007EAE8-0x8007EC14 (300B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
#include "mem.h"
typedef struct {
    char pad0x0[0x4];
    s32 unk0x4;
    s16 unk0x8;
    char pad0xA[0x2];
    s32 unk0xC;
} Unk_EAE8_vt;
void fn_8007EAE8(CScript *arg0) {
    s32 var_r0;
    s32 temp_r0;
    s32 var_r29;
    s32 var_r3;
    register CStruct *temp_r11 __asm__("r11");
    void *temp_r11_2;
    Unk_EAE8_vt *temp_r9;
    Unk_EAE8_vt *temp_r9_2;
    Unk_EAE8_vt *temp_r9_3;
    void *var_r11;
    void *var_r31;
    register CStruct *var_r9 __asm__("r9");

    if ((s32) arg0->unk0x20 == 0) {
        var_r3 = 0;
        var_r9 = arg0->unk0x1C;
        temp_r11 = *(CStruct **)((char *)var_r9 + 0xC);
        {
            s32 t = temp_r11->unk0x4;

            var_r9 = temp_r11;
            if (t == -1) {
                var_r9 = NULL;
            }
        }
        while (var_r9 != NULL) {
            var_r9 = var_r9->unk0xC;
            var_r3 += 1;
            {
                s32 t = var_r9->unk0x4;

                if (t == -1) {
                    var_r9 = NULL;
                }
            }
        }
        arg0->unk0x24 = var_r3;
        if (var_r3 != 0) {
            arg0->unk0x20 = Mem_Alloc(var_r3 * 4);
            var_r11 = *(CStruct **)((char *)arg0->unk0x1C + 0xC);
            if ((s32) ((Unk_C8FEE62D *)var_r11)->unk0x4 == -1) {
                var_r11 = NULL;
            }
            if (var_r11 != NULL) {
                var_r29 = 0;
                do {
                    temp_r9 = ((Unk_C8FEE62D *)var_r11)->unk0xC;
                    {
                        s32 t = (s32) temp_r9->unk0x4;

                        var_r31 = temp_r9;
                        if (t == -1) {
                            var_r31 = NULL;
                        }
                    }
                    temp_r0 = ((Unk_C8FEE62D *)var_r11)->unk0x4;
                    *(s32 *)(var_r29 + arg0->unk0x20) = temp_r0;
                    if (var_r11 != NULL) {
                        temp_r9_2 = ((Unk_C8FEE62D *)var_r11)->unk0x14;
                        ((s32 (*)(void *, s32))temp_r9_2->unk0xC)(var_r11 + temp_r9_2->unk0x8, 3);
                    }
                    var_r29 += 4;
                    var_r11 = var_r31;
                } while (var_r11 != NULL);
            }
        }
        temp_r11_2 = arg0->unk0x1C;
        if (temp_r11_2 != NULL) {
            temp_r9_3 = ((Unk_C8FEE62D *)temp_r11_2)->unk0x14;
            ((s32 (*)(void *, s32))temp_r9_3->unk0xC)(temp_r11_2 + temp_r9_3->unk0x8, 3);
        }
        arg0->unk0x1C = NULL;
    }
}
