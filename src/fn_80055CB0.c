// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80055CB0-0x80055E74 (452B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"

void fn_80012A10(void *);

typedef struct {
    char pad0x0[0x38];
    s16 unk0x38;
    char pad0x3A[0x2];
    s32 unk0x3C;
} Unk_55CB0_disp;
typedef struct {
    char pad0x0[0x8];
    s16 unk0x8;
    char pad0xA[0x2];
    s32 unk0xC;
} Unk_55CB0_vt;

void fn_800561B4(Unk_CFB386B2 *, CScript *);

bool fn_80055CB0(Unk_CFB386B2 *arg0) {
    Unk_55CB0_disp *temp_r9;
    CStruct *temp_r9_10;
    Unk_55CB0_vt *temp_r9_11;
    void *temp_r9_2;
    Unk_55CB0_vt *temp_r9_3;
    Unk_C7387A53 *temp_r9_4;
    CStruct *temp_r9_5;
    CStruct *temp_r9_6;
    Unk_55CB0_vt *temp_r9_7;
    Unk_C7387A53 *temp_r9_8;
    CStruct *temp_r9_9;
    void *var_r11;
    void *var_r30;
    void *var_r31;
    void *var_r31_2;
    void *var_r31_3;

    if ((s32) arg0->unk0x278 != 0) {
        fn_80055EEC();
    }
    temp_r9 = (Unk_55CB0_disp *)arg0->unk0x284;
    if (((s32 (*)(void *))temp_r9->unk0x3C)((char *)arg0 + temp_r9->unk0x38) == 0) {
        return false;
    }
    temp_r9_2 = arg0->unk0x26C;
    if (temp_r9_2 != NULL) {
        var_r31 = temp_r9_2 + (*(s32 *)((char *)temp_r9_2 - 0x8) * 0x10);
        if (temp_r9_2 != var_r31) {
            do {
                var_r31 -= 0x10;
                temp_r9_3 = (Unk_55CB0_vt *)((Unk_C7387A53 *)var_r31)->unk0xC;
                ((s32 (*)(void *, s32))temp_r9_3->unk0xC)(var_r31 + temp_r9_3->unk0x8, 0);
            } while ( arg0->unk0x26C != var_r31);
        }
        Mem_Free2((void *)(arg0->unk0x26C - 8));
    }
    if ((s32) arg0->unk0x270 != 0) {
        fn_80012A10((char *)arg0 + 0x1E8);
    }
    temp_r9_4 = arg0->unk0x27C;
    if (temp_r9_4 != NULL) {
        temp_r9_5 = temp_r9_4->unk0xC;
        {
            s32 t8 = temp_r9_5->unk0x4;
            var_r11 = temp_r9_5;
            if (t8 == -1) {
                var_r11 = NULL;
            }
        }
        if (var_r11 != NULL) {
            do {
                temp_r9_6 = ((Unk_C8FEE62D *)var_r11)->unk0xC;
                {
                    s32 t9b = temp_r9_6->unk0x4;
                    var_r31_2 = temp_r9_6;
                    if (t9b == -1) {
                        var_r31_2 = NULL;
                    }
                }
                if (var_r11 != NULL) {
                    temp_r9_7 = (Unk_55CB0_vt *)((Unk_C8FEE62D *)var_r11)->unk0x14;
                    ((s32 (*)(void *, s32))temp_r9_7->unk0xC)(var_r11 + temp_r9_7->unk0x8, 3);
                }
                var_r11 = var_r31_2;
            } while (var_r11 != NULL);
        }
    }
    temp_r9_8 = arg0->unk0x280;
    if (temp_r9_8 != NULL) {
        temp_r9_9 = temp_r9_8->unk0xC;
        {
            s32 t9 = temp_r9_9->unk0x4;
            var_r31_3 = temp_r9_9;
            if (t9 == -1) {
                var_r31_3 = NULL;
            }
        }
        if (var_r31_3 != NULL) {
            do {
                temp_r9_10 = ((Unk_C8FEE62D *)var_r31_3)->unk0xC;
                {
                    s32 t10 = temp_r9_10->unk0x4;
                    var_r30 = temp_r9_10;
                    if (t10 == -1) {
                        var_r30 = NULL;
                    }
                }
                fn_800561B4(arg0, ((Unk_C8FEE62D *)var_r31_3)->unk0x4);
                if (var_r31_3 != NULL) {
                    temp_r9_11 = (Unk_55CB0_vt *)((Unk_C8FEE62D *)var_r31_3)->unk0x14;
                    ((s32 (*)(void *, s32))temp_r9_11->unk0xC)(var_r31_3 + temp_r9_11->unk0x8, 3);
                }
                var_r31_3 = var_r30;
            } while (var_r31_3 != NULL);
        }
    }
    arg0->unk0x278 = 0;
    return true;
}
