// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004F6B8-0x8004F85C (420B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-thread-jumps
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8004FA00(s32, s32);
/* 3-word list cursor: value, prev-link, next-link (see CObject_AddRefLink/DFC0) */
typedef struct { void *v; void *prev; void *next; } Ck_t;

void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);
void fn_8004F85C(Unk_0055B719 *);
void CObject_RemoveRefLink(void *, void *);
void fn_800A3B44(Unk_C7387A53 *, s32, s32);
s32 fn_8004C858(s32, s32);
s32 fn_80042180(Unk_C7387A53 *);
s32 fn_8004C414(Unk_9E4B1D7B *, s32);
s32 fn_8004215C();
void fn_8004F6B8(Unk_AD9AE6AA *arg0, CStruct *arg1) {
    s32 *sp8;
    s32 *temp_r31_2;
    s32 *var_r3;
    s32 temp_r31;
    CScript *temp_r9;
    Unk_07FDFB02 *temp_r9_2;
    s32 padA, padB;

    
    temp_r31 = arg0->unk0x10;
    if (fn_8004215C() == 0) {
        goto block_4;
    }
    if (fn_8004C414(temp_r31, arg1->unk0x0) == 0) {
        goto block_4;
    }
    if (fn_80042180(arg0) == 0) {
        goto block_22;
    }
    if (fn_8004C858(temp_r31, arg0->unk0x18) == 0) {
        goto block_22;
    }
block_4:
    if ((s32) arg1->unk0x0 != QB_NOTIFY_CHILD_LOCK) {
        goto block_9;
    }
    temp_r9 = arg0->unk0x1AC;
    if (temp_r9 == NULL) {
        goto block_9;
    }
    if ((s32) arg1->unk0x8 != (s32) temp_r9->unk0x18) {
        goto block_8;
    }
    temp_r9_2 = arg0->unk0x8;
    arg0->unk0x1C0 = 1;
    ((s32 (*)(void *))temp_r9_2->unk0x5C)((char *)arg0 + temp_r9_2->unk0x58);
block_8:
    fn_800A3B44(arg1, arg0->unk0x18, 0);
block_9:
    if ((s32) arg1->unk0x0 != QB_FOCUS) {
        goto block_22;
    }
    if ( arg0->unk0x1AC != NULL) {
        goto block_12;
    }
    fn_8004F85C(arg0);
block_12:
    var_r3 = *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x1AC) + 0x64);
    ((Ck_t *)&sp8)->prev = 0;
    ((Ck_t *)&sp8)->next = 0;
    ((Ck_t *)&sp8)->v = var_r3;
    if (var_r3 == NULL) {
        goto loop_17;
    }
    goto block_16;
block_14:
    temp_r31_2 = ((Unk_C8FEE62D *)sp8)->unk0x70;
    CObject_RemoveRefLink(sp8, &sp8);
    sp8 = temp_r31_2;
    if (temp_r31_2 == NULL) {
        goto loop_17;
    }
    var_r3 = temp_r31_2;
block_16:
    CObject_AddRefLink(var_r3, &sp8);
loop_17:
    if (sp8 == NULL) {
        goto block_20;
    }
    if ((s32) ((Unk_C8FEE62D *)sp8)->unk0x18 != (s32) arg1->unk0x8) {
        goto block_14;
    }
    fn_8004FA00(arg0, &sp8);
    fn_800A3B44(arg1, arg0->unk0x18, 0);
block_20:
    if (sp8 == NULL) {
        goto block_22;
    }
    CObject_RemoveRefLink(sp8, &sp8);
    sp8 = NULL;
block_22:
    /* Two address-taken-but-never-written words keep the local area at 16
       bytes, so the link-cell puns are not folded into the CR/GPR save area
       (frame 0x28 with the save block at 0x18 instead of a 0x20 frame). */
    __asm__("" : : "m"(padA), "m"(padB));
    return;
}
