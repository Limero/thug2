// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800607A0-0x800608E8 (328B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void *Mem_Alloc2(s32 size);
void *fn_8000F10C(void *, s32, s32, void *);
void fn_8005F51C(void *, void *);
void fn_8005F418(void *, s32);
#include "qb_constants.h"
#include "structs.h"
s32 fn_80060DEC(s32, s32);
extern void *lbl_802FFE98;
extern s32 lbl_8029036C;
// arg0 field map used here (note +0x4A OVERLAPS the u32 at +0x48, so the
// u16 counter is reached through an s16* view instead of a struct member):
//   +0x10 list-cell head        +0x14 live-cell count
//   +0x18 bitmask, |= 1<<cnt    +0x30 notify flag (guarded thunk call)
//   +0x34 mesh-name hash        +0x48 u32 flags (bit0 cleared, bit5 read)
//   +0x4A u16 counter
// 0x18-byte record (var_r31): +0 arg1, +4 zero, +8 arg2, +C/+10/+14 zero.
// 0xC-byte cell  (temp_r3):   +0 record, +4 list head, +8 next cell; the
// previous head's +8 cell gets its +4 owner back-pointed at temp_r3.
bool fn_800607A0(Unk_2FEA250A *arg0, s32 arg1, s32 arg2, s32 arg3) {
    volatile s32 sp8; /* write-only: retail spills the list head here and
                         never reloads it, but the slot must exist (frame
                         0x20) — see fix 5 in the header */
    CStruct *temp_r29;
    Unk_9994C3F5 *temp_r30;
    CStruct *temp_r3;
    Unk_DB0E2BAB *var_r31;
    arg0->unk0x48 = (u32) (arg0->unk0x48 & 0x7FFFFFFFu);
    if (arg3 == 0) {
        s32 temp_size;
        temp_size = lbl_8029036C;
        var_r31 = fn_8000F10C(lbl_802FFE98, 0x18, temp_size, 0);
        if (var_r31 == NULL) {
            return false;
        }
        goto block_4;
    }
    var_r31 = Mem_Alloc2(0x18);
block_4:
    var_r31->unk0x0 = arg1;
    fn_8005F51C(arg1, ((u32) arg0->unk0x48 >> 0x1BU) & 1);
    var_r31->unk0x8 = arg2;
    arg0->unk0x18 = (s32) (arg0->unk0x18 | (1 << *(s16 *)((char *)arg0 + (s32)0x4A)));
    var_r31->unk0x4 = 0;
    if ((s32) arg0->unk0x30 != 0) {
        fn_8005F418(var_r31->unk0x0, arg0->unk0x30);
    }
    var_r31->unk0x14 = 0;
    temp_r29 = (char *)arg0 + 0x10;
    var_r31->unk0xC = 0;
    var_r31->unk0x10 = 0;
    temp_r30 = arg0->unk0x10;
    sp8 = (s32)temp_r30;
    temp_r3 = Mem_Alloc2(0xC);
    temp_r3->unk0x8 = temp_r30->unk0x8;
    temp_r3->unk0x0 = var_r31;
    temp_r3->unk0x4 = temp_r30;
    temp_r29->unk0x4 = (s32) (temp_r29->unk0x4 + 1);
    temp_r30->unk0x8 = temp_r3;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r3) + 0x8) + 0x4) = temp_r3;
    *(s16 *)((char *)arg0 + (s32)0x4A) = (s16) ((u16) *(s16 *)((char *)arg0 + (s32)0x4A) + 1);
    fn_80060DEC(arg0, 0);
    if (*(s16 *)((char *)arg0 + (s32)0x4A) == 1) {
        arg0->unk0x34 = QB_TEMPMESHNAME;
    }
    return true;
}
