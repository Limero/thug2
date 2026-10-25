// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000FF18-0x800100A4 (396B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 Mem_NewZero(s32);
s32 fn_8001094C(s32, s32);
s32 Mem_Alloc(s32);
void fn_800107A0(s32, s32, s32);
s32 fn_8000F95C(Unk_C6DE1362 *, s32, s32, s32);
s32 fn_80010400(s32, s32, s32);
s32 fn_80011CF4(s32, s32, s32);
void *memset(void *, s32, s32);

extern s32 lbl_802FFE98;
extern char lbl_802904C0[];
extern char lbl_802904D4[];

void fn_8000FF18(Unk_C6DE1362 *arg0, s32 arg1) {
    s32 temp_r30;
    s32 temp_r4;
    s32 temp_r5;

    if (arg0->unk0x14C == 0) {
        arg1 &= 0xFFFFFFF0;
        arg0->unk0x14C = fn_8001094C(Mem_NewZero(0x1C), 0);
        temp_r30 = Mem_Alloc(arg1);
        memset((void *)temp_r30, 0xFE, arg1);
        temp_r5 = temp_r30 - 0x400;
        fn_800107A0(arg0->unk0x14C, temp_r30, temp_r5 + arg1);
        arg0->unk0x154 = fn_8000F95C(arg0, arg0->unk0x14C, 1, (s32)lbl_802904C0);
        arg0->unk0x150 = fn_8000F95C(arg0, arg0->unk0x14C, -1, (s32)lbl_802904D4);
        if (fn_80010400(lbl_802FFE98, QB_TEAMMATEPRO, 0) != 0) {
            fn_80011CF4(arg0->unk0x154, fn_80010400(lbl_802FFE98, QB_TEAMMATEPRO, 0), 0);
            fn_80011CF4(arg0->unk0x124, fn_80010400(lbl_802FFE98, QB_TEAMMATEPRO, 0), 0);
            fn_80011CF4(arg0->unk0x134, fn_80010400(lbl_802FFE98, QB_TEAMMATEPRO, 0), 0);
        }
        fn_80011CF4(arg0->unk0x154, arg0->unk0x170, 0);
        fn_80011CF4(arg0->unk0x154, arg0->unk0x11C, 0x7800);
        fn_80011CF4(arg0->unk0x154, arg0->unk0x118, 0x7800);
        fn_80011CF4(arg0->unk0x154, arg0->unk0x1E4, 0);
    }
}
