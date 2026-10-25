// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013BE28-0x8013BEE0 (184B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"

extern void* lbl_802FFE98;
extern void fn_8000F2F8(Unk_9F352E7C *, s32);
extern s32 *fn_8013E870(Unk_A99C4F7E *, s32);
extern s32 fn_8013ADE8(void *);
extern s32 fn_800145AC(void);
extern void fn_8000F320(Unk_F12C5E01 *);

void *fn_8013BE28(Unk_CA1C78B1 *arg0, s32 arg1, s16 arg2, s32 arg3) {
    Unk_04010383 *obj;
    s32 temp_r3;
    s32 listhdr;
    s32 link;
    s32 temp_r0;

    fn_8000F2F8(lbl_802FFE98, ((Unk_FFAD6788 *)lbl_802FFE98)->unk0x134);
    obj = NULL;
    if (arg0->unk0x1844 < arg0->unk0x1848) {
        obj = fn_8013E870(Mem_Alloc2(0x493C), arg3);
        obj->unk0x4C = arg1;
        obj->unk0x50 = (u16)arg2;
        temp_r3 = fn_8013ADE8(arg0);
        obj->unk0x70 = (s32)arg0;
        obj->unk0x48 = temp_r3;
        obj->unk0x74 = fn_800145AC();
        listhdr = (s32)arg0 + 0x227C;
        link = (s32)obj + 0x4910;
        temp_r0 = ((Unk_1D62F22E_2 *)listhdr)->unk0x10;
        ((Unk_1D62F22E_2 *)link)->unk0xC = listhdr;
        ((Unk_1D62F22E_2 *)link)->unk0x10 = temp_r0;
        *(s32 *)(((Unk_1D62F22E_2 *)listhdr)->unk0x10 + 0xC) = link;
        ((Unk_1D62F22E_2 *)listhdr)->unk0x10 = link;
    }
    fn_8000F320(lbl_802FFE98);
    return obj;
}
