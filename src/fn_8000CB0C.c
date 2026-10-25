// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000CB0C-0x8000CC48 (316B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s16 unk0x8;
    s16 pad0xA;
} Rec_t;

typedef struct {
    void *unk0x0;
    void *unk0x4;
    s32 unk0x8;
    void *unk0xC;
    void *unk0x10;
    void *unk0x14;
    s32 unk0x18;
} Head_t;

typedef struct {
    void *unk0x0;
    void *unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    s32 unk0x10;
} Node_t;

extern s32 *lbl_802FFE98;

s32 fn_8000E68C(void *, void *, void *);
s32 fn_8000E774(void *, void *, void *);
s32 fn_8000F10C(void *, s32, s32, s32);
s32 fn_8000E608(void *, s32);
void *Mem_Alloc2(s32);
void Mem_Free(void *);

void *fn_8000CB0C(Head_t *arg0, Unk_9994C3F5 *arg1, s32 arg2) {
    s32 var_r21;
    char *var_r28;
    s32 temp_r0;
    Rec_t *rec;
    s32 temp_r27;
    s32 temp_r25;
    s32 var_r24;
    s32 temp_r22;
    char *temp_r23;
    char *temp_r26;
    Node_t *temp_r30;
    s32 temp_r3;
    s32 temp_r31;
    s32 temp_r16;

    arg0->unk0x18 = arg2;
    arg0->unk0xC = fn_8000E608(Mem_Alloc2(0x18), 4);
    arg0->unk0x4 = arg1;
    var_r21 = 0;
    var_r28 = (char *)arg1 + 0xC;
    temp_r0 = arg1->unk0x8;
    arg0->unk0x8 = temp_r0;
    if (var_r21 < (s32)temp_r0) {
        do {
            rec = (Rec_t *)var_r28;
            temp_r27 = rec->unk0x4;
            temp_r25 = rec->unk0x0;
            temp_r16 = rec->unk0x8;
            var_r24 = temp_r27;
            if (var_r24 == 0) {
                var_r24 = temp_r25;
            }
            temp_r23 = var_r28 + (temp_r16 + 0x10);
            __asm__("mr %0,%1" : "=&r"(temp_r22) : "r"(temp_r16 + 0x10));
            temp_r26 = var_r28 + 0x10;
            if ((s32)arg0->unk0x18 != 0) {
                temp_r30 = (Node_t *)fn_8000F10C(lbl_802FFE98, 0x14, 1, *(s32 *)((char *)lbl_802FFE98 + 0x11C));
            } else {
                temp_r30 = (Node_t *)fn_8000F10C(lbl_802FFE98, 0x14, 1, *(s32 *)((char *)lbl_802FFE98 + 0x118));
            }
            temp_r3 = fn_8000E68C(arg0->unk0xC, temp_r26, (void *)1);
            temp_r31 = temp_r3;
            if (temp_r3 == 0) {
                fn_8000E774(arg0->unk0xC, temp_r26, temp_r30);
                temp_r30->unk0x0 = temp_r27;
                temp_r30->unk0x4 = temp_r23;
                temp_r30->unk0x8 = temp_r31;
                temp_r30->unk0xC = temp_r31;
                temp_r30->unk0x10 = temp_r25;
            } else {
                Mem_Free(temp_r30);
            }
            var_r21 += 1;
            var_r28 = var_r28 + (temp_r22 + ((var_r24 + 3) & QB_UNKNOWN_0xFFFFFFFC));
        } while (var_r21 < (s32)arg0->unk0x8);
    }
    arg0->unk0x10 = 0;
    arg0->unk0x14 = 0;
    return arg0;
}
