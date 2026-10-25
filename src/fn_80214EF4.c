// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80214EF4-0x80214FF0 (252B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetStructure(s32, s32);
extern void GetFloat(CStruct *, s32, f32 *, s32);
extern s32 fn_80107B20(Unk_E9DCA07D *, s32, void *);
s32 fn_80214EF4(s32 arg0, Unk_EA529D06 *arg1, Unk_EA529D06 *arg2, Unk_73778A2B *arg3) {
    f32 spC;
    f32 sp8;
    s32 sp14;

    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_FEELER_HEIGHT, &sp8, 1);
    arg3->unk0x0 = arg1->unk0x0;
    arg3->unk0x8 = arg1->unk0x8;
    ((Unk_F6393DBC *)arg3)->unk0x4 = (f32) (((Unk_F6393DBC *)arg3)->unk0x4 + (sp8 + sp8));
    arg3->unk0x10 = arg1->unk0x0;
    arg3->unk0x18 = arg1->unk0x8;
    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_STAND_POS_SEARCH_DEPTH, &spC, 1);
    ((Unk_F6393DBC *)arg3)->unk0x14 = (f32) (((Unk_F6393DBC *)arg3)->unk0x14 - spC);
    if (fn_80107B20(arg3, 1, 0) == 0) {
        arg2->unk0x0 = arg1->unk0x0;
        ((__ps_t *)((char *)arg2))[1] = ((__ps_t *)((char *)arg1))[1];
        sp14 = 0;
    } else {
        arg2->unk0x0 = arg3->unk0x88;
        ((__ps_t *)((char *)arg2))[1] = ((__ps_t *)((char *)arg3 + (s32)0x88))[1];
        sp14 = 1;
    }
    return sp14;
}
