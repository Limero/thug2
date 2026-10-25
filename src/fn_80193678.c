// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80193678-0x80193770 (248B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 AddInteger(CStruct * arg0, s32 arg1, s32 arg2);
extern s32 fn_8019519C(Unk_C7387A53 * arg0);
void fn_80193678(Unk_72E9CBBF *arg0) {
    s32 sp8;
    s32 *p84;
    s32 *p74;
    s32 *p78;
    s32 *p7C;
    s32 *p90;
    s32 *p94;
    s32 *p88;
    s32 *q;
    s32 i;

    arg0->unk0x4AC = 0;
    arg0->unk0x4B0 = 0;
    GetInteger(arg0->unk0x20, QB_TRICK_TIME, &sp8, 1);
    AddInteger(arg0->unk0x20, QB_ADJUSTED_TRICK_TIME, sp8);
    AddInteger(arg0->unk0x20, QB_TRICKS_COMPLETED, 0);
    if (fn_8019519C(arg0) != 0) {
        arg0->unk0x4B0 = 0;
    } else {
        arg0->unk0x4B0 = sp8 - 0xC8;
    }
    p84 = (s32 *)((char *)arg0 + 0x84);
    p74 = (s32 *)((char *)arg0 + 0x74);
    p78 = (s32 *)((char *)arg0 + 0x78);
    p7C = (s32 *)((char *)arg0 + 0x7C);
    p90 = (s32 *)((char *)arg0 + 0x90);
    p94 = (s32 *)((char *)arg0 + 0x94);
    p88 = (s32 *)((char *)arg0 + 0x88);
    q = (s32 *)((char *)arg0 + 0x4B4);
    for (i = 0; i < 0x1E; i++) {
        p84[i * 9] = 1;
        p74[i * 9] = 0;
        p78[i * 9] = 0;
        p7C[i * 9] = 0;
        p90[i * 9] = 0;
        p94[i * 9] = 1;
        p88[i * 9] = 0;
        q[0] = 0;
        q += 1;
    }
}
