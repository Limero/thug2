// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A5E38-0x801A5F28 (240B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801A65EC(Unk_C8FEE62D *, s32 *, s32 *);
s32 fn_801A572C(s32);
s32 fn_801A4FF0(CStruct *, s32);
s32 fn_801A56F4(s32);
void fn_80127E70(s32, s32, s32, s32);
s32 fn_801A5848(s32);
void fn_80009218(void *, s32);
s32 fn_800093A4(Unk_9994C3F5 *);
void AddComponent(CStruct *, s32, s32, void *);
void fn_800092B0(Unk_9994C3F5 *, s32);
void fn_801A5E38(Unk_DB0E2BAB *arg0, CStruct *arg1) {
    struct {
        s32 sp8;
        s32 pad;
        long long blk[2];
        s32 spC;
    } fr;
    u32 count;
    u32 i;
    s32 entry;
    s32 *base;
    long long *pblk;

    count = *((u32 *)&arg0->unk0x8);
    pblk = fr.blk;
    for (i = 0; i < count; i++) {
        fr.sp8 = i;
        if (fn_801A572C(entry = fn_801A65EC((char *)arg0 + 4, &fr.sp8, &fr.spC)) != 0) {
            fn_801A4FF0(entry, arg1);
        }
    }
    base = (s32 *)((char *)arg0 + 0x1C);
    fn_80127E70(arg1, QB_CURRENTSKATER, 0xD, fn_801A56F4(base[arg0->unk0x24]));
    fn_80009218(pblk, fn_801A5848(base[arg0->unk0x24]));
    AddComponent(arg1, QB_DISPLAYNAME, 3, fn_800093A4(pblk));
    fn_800092B0(pblk, 2);
}
