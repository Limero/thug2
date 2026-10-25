// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CC698-0x800CC770 (216B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetArray(CStruct *, s32, void *, s32);
s32 GetChecksum_2(void *, s32, s32 *, s32);
void *fn_80129528(void *, s32);
void *Mem_NewZero(s32);
void *fn_8007138C(void *);
void fn_8006AC08(void *, void *);

void fn_800CC698(s32 arg0, CStruct *arg1) {
    void *sp8;
    s32 spC;
    u32 ctr;
    s32 zero;
    Unk_C8FEE62D *base;
    void *elem;
    Unk_C8FEE62D *tmp;

    base = (Unk_C8FEE62D *)arg0;
    sp8 = NULL;
    GetArray(arg1, QB_TEXTURE_PROJECTIONS, &sp8, 1);
    ctr = 0;
    if (ctr >= ((CStruct *)sp8)->unk0x4) {
        goto end;
    }
    base = (Unk_C8FEE62D *)((char *)base + 0x1C);
    zero = 0;
    do {
        elem = fn_80129528(sp8, ctr);
        ctr += 1;
        spC = zero;
        GetChecksum_2(elem, QB_PROJ_ID, &spC, 1);
        tmp = fn_8007138C(Mem_NewZero(0xD0));
        tmp->unk0x18 = spC;
        fn_8006AC08(tmp, elem);
        tmp->unk0x10 = (s32)base;
        tmp->unk0xC = base->unk0xC;
        ((Unk_C8FEE62D *)base->unk0xC)->unk0x10 = (s32)tmp;
        base->unk0xC = (s32)tmp;
    } while (ctr < ((CStruct *)sp8)->unk0x4);
end:;
}
