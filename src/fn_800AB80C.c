// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AB80C-0x800AB930 (292B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(s32, s32);
s32 fn_8009F498(s32);
s32 fn_800B6570(void);
s32 fn_800602E4(s32);
void fn_80060264(s32, s32);
void fn_80060E4C(s32, s32);
void fn_80062584(s32, s32);
void fn_80062774(s32, void *);
typedef struct {
    char pad0x0[0x24];
    char pad0x24[0x4];
    char pad0x28[0x10];
    s32 unk0x38;
    s32 unk0x3C;
    s32 unk0x40;
    s32 unk0x44;
    s32 unk0x48;
    char pad0x4C[0x8];
    char pad0x54[0x2000];
    s32 unk0x2054;
} AB80C_t;
void fn_800AB80C(AB80C_t *arg0) {
    s32 var_r25;
    s32 var_r24;
    void *var_r26;
    s32 temp_r27;
    s32 temp_r28;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r11;
    s32 *temp_r9;
    var_r25 = 0;
    if (var_r25 < (s32) arg0->unk0x2054) {
        var_r24 = 0;
        var_r26 = (char *)arg0 + 0x54;
        do {
            if (((Unk_C8FEE62D *)var_r26)->unk0xC != 0) {
                temp_r27 = GetChecksum_3(((Unk_C8FEE62D *)var_r26)->unk0x14, QB_MODEL);
                temp_r28 = fn_8009F498(fn_800B6570());
                temp_r30 = *(s32 *)((char *)GetChecksum_3(temp_r28, QB_MODEL) + 0x210);
                fn_80062774(temp_r30, (char *)arg0 + 0x28);
                fn_80060E4C(temp_r30, arg0->unk0x38);
                fn_80062584(temp_r30, arg0->unk0x3C);
                temp_r29 = fn_800602E4(temp_r30);
                fn_80060264(temp_r30, fn_800602E4(*(s32 *)((char *)temp_r27 + 0x210)));
                fn_80060264(*(s32 *)((char *)temp_r27 + 0x210), temp_r29);
                *(__ps_t *)((char *)temp_r28 + 0x58) = *(__ps_t *)((char *)arg0 + 0x40);
                *(__ps_t *)((char *)temp_r28 + 0x60) = *(__ps_t *)((char *)arg0 + 0x48);
            }
            temp_r11 = ((Unk_C8FEE62D *)var_r26)->unk0x14;
            if (temp_r11 != NULL) {
                temp_r9 = (s32 *)((Unk_9994C3F5 *)temp_r11)->unk0x8;
                ((void (*)(void *, s32))*(s32 *)((char *)temp_r9 + 0xC))((char *)temp_r11 + *(s16 *)((char *)temp_r9 + 8), 3);
            }
            ((Unk_C8FEE62D *)var_r26)->unk0x14 = var_r24;
            var_r25 += 1;
            var_r26 += 0x20;
        } while (var_r25 < (s32) arg0->unk0x2054);
    }
    arg0->unk0x2054 = 0;
}
