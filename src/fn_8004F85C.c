// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004F85C-0x8004FA00 (420B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80292C70[];
extern char lbl_80292C78[];
extern f32 lbl_80292C80;
extern f64 lbl_80292C88;
s32 Script_GenerateCRC(s32);
void CObject_AddRefLink(void *, void *);
void CObject_RemoveRefLink(void *, void *);
s32 fn_8004E710(void *, void *);

typedef struct {
    char pad0[0x64];
    void *unk64;
    char pad1[0x110];
    f32 unk178;
    f32 unk17C;
    char pad2[0x2C];
    void *unk1AC;
    char pad3[0x1C];
    s32 unk1CC;
    f32 unk1D0;
    f32 unk1D4;
    s32 unk1D8;
} Obj_t;

/* 3-word list cursor: value, prev-link, next-link. */
typedef struct { void *v; void *prev; void *next; } Ck_t;
typedef struct { char p0[0x1C]; s32 id; char p1[0x50]; void *next70; } Node_t;

void fn_8004F85C(Obj_t *arg0) {
    s32 z0;
    s32 z1;
    s32 z2;
    s32 *sp8;
    f32 sp18;
    s32 temp_r30_3;
    s32 temp_r3;
    f32 var_f0;
    s32 temp_r0;
    s32 temp_r30;
    s32 temp_r30_2;

    temp_r3 = arg0->unk64;
    ((Ck_t *)&sp8)->prev = 0;
    ((Ck_t *)&sp8)->next = 0;
    sp8 = temp_r3;
    if (temp_r3 != NULL) {
        CObject_AddRefLink(sp8, &sp8);
    }
    if (sp8 != NULL) {
        do {
            __asm__("" : : "m"(z0), "m"(z1), "m"(z2));
            temp_r30 = ((Node_t *)sp8)->id;
            if (((temp_r30 == Script_GenerateCRC((s32)lbl_80292C70)) && (arg0->unk1D8 != 0)) ||
                ((temp_r30_2 = ((Node_t *)sp8)->id,
                  temp_r30_2 == Script_GenerateCRC((s32)lbl_80292C78)) && (arg0->unk1D8 == 0))) {
                arg0->unk1AC = sp8;
            }
            temp_r30_3 = ((Node_t *)sp8)->next70;
            if (sp8 != NULL) {
                CObject_RemoveRefLink(sp8, &sp8);
                sp8 = NULL;
            }
            sp8 = temp_r30_3;
            if (temp_r30_3 != NULL) {
                CObject_AddRefLink(temp_r30_3, &sp8);
            }
        } while (sp8 != NULL);
    }
    sp18 = lbl_80292C80;
    if ((fn_8004E710(arg0->unk1AC, &sp18) != 0) && (temp_r0 = arg0->unk1CC, temp_r0 >= 0)) {
        arg0->unk1D4 = sp18;
        arg0->unk1D0 = sp18 * (f32)(f64)temp_r0;
    } else {
        arg0->unk1CC = -1;
        if (arg0->unk1D8 != 0) {
            var_f0 = arg0->unk17C;
        } else {
            var_f0 = arg0->unk178;
        }
        arg0->unk1D0 = var_f0;
    }
    if (sp8 != NULL) {
        CObject_RemoveRefLink(sp8, &sp8);
        sp8 = NULL;
    }
}
