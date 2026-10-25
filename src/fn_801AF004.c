// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AF004-0x801AF164 (352B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 strcmp(char *, char *);
extern s32 Compare(char *, char *);
extern void *lbl_802FFE98;
extern void fn_8000F2F8(Unk_9F352E7C *, s32);
extern void fn_8000F320(Unk_F12C5E01 *);
extern void *Mem_NewZero(s32);
extern void *fn_801AECBC(Unk_C8FEE62D *);
extern void fn_801AED68(Unk_C7387A53 *);
extern void fn_801AED98(void *, s32);
extern void fn_801AEDE0(Unk_C7387A53 *, s32);
extern void fn_801AEDE8(Unk_C7387A53 *, s32);
extern char *fn_801AED74(s32);
void fn_801AF004(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    CStruct *a0;
    register s32 a1 __asm__("r29");
    register s32 a2 __asm__("r26");
    register s32 a3 __asm__("r28");
    register s32 prev_r30 __asm__("r30");
    register s32 walk_r9 __asm__("r9");
    Unk_C8FEE62D *temp_r31;
    Unk_C7387A53 *var_r31;

    a0 = arg0;
    a0->unk0x0 = 1;
    a1 = arg1;
    walk_r9 = a0->unk0x10;
    a2 = arg2;
    a3 = arg3;
    if (((CStruct *)walk_r9)->unk0x4 == -1) {
        walk_r9 = NULL;
    }
    prev_r30 = NULL;
    var_r31 = walk_r9;
    while (var_r31 != NULL) {
        if (strcmp(fn_801AED74(var_r31), a1) == 0) {
            if (var_r31->unk0x40 == a3) {
                goto found;
            }
        }
        if ((var_r31->unk0x40 < a3) ||
            ((var_r31->unk0x40 == a3) &&
             (Compare(fn_801AED74(var_r31), a1) < 0))) {
            prev_r30 = var_r31;
        }
        walk_r9 = var_r31->unk0xC;
        if (((CStruct *)walk_r9)->unk0x4 == -1) {
            walk_r9 = NULL;
        }
        var_r31 = walk_r9;
    }
    fn_8000F2F8(lbl_802FFE98, ((Unk_C7387A53 *)lbl_802FFE98)->unk0x12C);
    temp_r31 = fn_801AECBC(Mem_NewZero(0x58));
    fn_801AED68(temp_r31);
    fn_801AED98(temp_r31, a1);
    fn_801AEDE0(temp_r31, a2);
    temp_r31->unk0x40 = a3;
    if (prev_r30 != NULL) {
        temp_r31->unk0x10 = prev_r30;
        temp_r31->unk0xC = ((Unk_C7387A53 *)prev_r30)->unk0xC;
        *(s32 *)(((Unk_C7387A53 *)prev_r30)->unk0xC + (s32)0x10) = temp_r31;
        ((Unk_C7387A53 *)prev_r30)->unk0xC = temp_r31;
        goto do_pop;
    }
    goto head_ins;
found:
    fn_801AEDE8((void *)var_r31, 1);
    return;
head_ins:
    walk_r9 = (s32)((char *)a0 + 4);
    temp_r31->unk0x10 = walk_r9;
    temp_r31->unk0xC = ((CStruct *)walk_r9)->unk0xC;
    *(s32 *)(((CStruct *)walk_r9)->unk0xC + (s32)0x10) = temp_r31;
    ((CStruct *)walk_r9)->unk0xC = temp_r31;
do_pop:
    fn_8000F320(lbl_802FFE98);
}
