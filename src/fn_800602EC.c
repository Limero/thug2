// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800602EC-0x80060490 (420B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "qb_constants.h"
#include "mem.h"

extern void *lbl_802FFE98;
extern s32 lbl_8029036C;
extern s32 lbl_80301B48;

s32 fn_800F2AD8(s32, s32, s32);
void *fn_8000F10C(void *, s32, s32, void *);
s32 fn_80055208(s32);
void fn_8005F058(void *, void *, void *, void *);
void fn_8005F51C(void *, s32);
void fn_8005F418(void *, s32);
s32 fn_80060DEC(s32, s32);

bool fn_800602EC(Unk_2FEA250A *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    volatile s32 sp8;
    CStruct *temp_r27;
    Unk_DB0E2BAB *var_r28;
    CStruct *temp_r30;
    CStruct *temp_r3_2;
    CStruct *temp_r29;
    s32 temp_r3;

    arg0->unk0x48 = (u32) (arg0->unk0x48 & 0x7FFFFFFFu);
    temp_r27 = (CStruct *)fn_800F2AD8(lbl_80301B48, arg1, 0);
    if (arg4 == 0) {
        s32 temp_size;
        temp_size = lbl_8029036C;
        var_r28 = (Unk_DB0E2BAB *)fn_8000F10C(lbl_802FFE98, 0x18, temp_size, 0);
        if (var_r28 == NULL) {
            return false;
        }
        goto block_4;
    }
    var_r28 = (Unk_DB0E2BAB *)Mem_Alloc2(0x18);
block_4:
    var_r28->unk0x10 = arg1;
    arg0->unk0x4E = (u16) (arg0->unk0x4E + 1);
    var_r28->unk0xC = 0;
    temp_r3 = fn_80055208(arg4);
    var_r28->unk0x0 = temp_r3;
    if (arg4 == 0) {
        if (temp_r3 == 0) {
            return false;
        }
    }
    fn_8005F058(var_r28->unk0x0, temp_r27, arg0, arg3);
    var_r28->unk0x4 = temp_r27->unk0x4;
    fn_8005F51C(var_r28->unk0x0, ((u32)arg0->unk0x48 >> 0x1BU) & 1);
    var_r28->unk0x8 = arg2;
    arg0->unk0x18 = (s32) (arg0->unk0x18 | (1 << *(s16 *)((char *)arg0 + (s32)0x4A)));
    if ((s32)arg0->unk0x30 != 0) {
        fn_8005F418(var_r28->unk0x0, arg0->unk0x30);
    }
    temp_r29 = (CStruct *)((char *)arg0 + 0x10);
    *(s16 *)((char *)arg0 + (s32)0x4A) = (s16) ((u16) *(s16 *)((char *)arg0 + (s32)0x4A) + 1);
    fn_80060DEC(arg0, 0);
    var_r28->unk0x14 = 0;
    temp_r30 = (CStruct *)arg0->unk0x10;
    sp8 = (s32)temp_r30;
    temp_r3_2 = (CStruct *)Mem_Alloc2(0xC);
    temp_r3_2->unk0x8 = temp_r30->unk0x8;
    temp_r3_2->unk0x0 = var_r28;
    temp_r3_2->unk0x4 = temp_r30;
    temp_r29->unk0x4 = (s32) (temp_r29->unk0x4 + 1);
    temp_r30->unk0x8 = temp_r3_2;
    *(s32 *) (*(s32 *) ((char *)temp_r3_2 + 0x8) + 0x4) = temp_r3_2;
    if (*(s16 *)((char *)arg0 + (s32)0x4A) == 1) {
        arg0->unk0x34 = QB_DATA_FROM_STREAM;
    }
    return true;
}
