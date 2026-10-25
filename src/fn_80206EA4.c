// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80206EA4-0x80206F7C (216B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void CStruct_dtor(s32);
void fn_80127E70(s32, s32, s32, s32);
void fn_80126FF4(s32, s32);
s32 fn_801A568C(void *, s32);
void *s_find_trick_in_mapping(void *, void *, s32);
s32 fn_801A7EC0(void *);
#include "qb_constants.h"
#include "structs.h"

// 16-byte scratch filled by s_find_trick_in_mapping(&sp8, arg1, i):
// f0 unused here, f1 -> 4th arg of fn_80127E70, f2 -> 2nd arg,
// f3 != 0 selects the arg2=1 branch, else arg2=0xD.
typedef struct {
    s32 f0;
    s32 f1;
    s32 f2;
    s32 f3;
} Unk_80206EA4_16;

void fn_80206EA4(Unk_59E38960 *arg0, void *arg1) {
    Unk_80206EA4_16 sp8;
    s32 i;
    if (arg0->unk0xA6C == 0) {
        arg0->unk0xA6C = CStruct_ctor(CStruct_new(8));
    }
    i = 0;
    CStruct_dtor(arg0->unk0xA6C);
    for (; i <= 0xB; i++) {
        s_find_trick_in_mapping(&sp8, arg1, i);
        if (fn_801A7EC0(&sp8) == 0) {
            if (sp8.f3 != 0) {
                fn_80127E70(arg0->unk0xA6C, sp8.f2, 1, sp8.f1);
            } else {
                fn_80127E70(arg0->unk0xA6C, sp8.f2, 0xD, sp8.f1);
            }
        }
    }
    fn_80126FF4(arg0->unk0xA6C, fn_801A568C(arg1, QB_TRICK_MAPPING));
}
