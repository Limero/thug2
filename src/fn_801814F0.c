// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801814F0-0x801815EC (252B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_80305F9C;
extern char lbl_802A93DC[];

void fn_80137CB4(Unk_9F066EC1 *);
s32 fn_8021D358(s32, u16);
s32 fn_8021B55C(s32, s32);
s32 fn_8021F6CC(Unk_2EC243AC *);
void *fn_8017471C(s32, s16);
void *GetChecksum_3(Unk_6A70655D *, s32);
s32 fn_8020C604(Unk_03123917 *, void *, s32);
void fn_8013DDE4(s32, s32, s32, void *, void *, s32, s32, s32);

struct sc_s {
    u8 f00;
    u8 f01;
    u16 f02;
    void *f04;
    u8 pad08[4];
    s32 f0C;
    u8 f10;
    u8 pad11[0x17];
};
struct hd_s {
    u8 b1;
    u8 b2;
    u8 pad02[2];
    s32 w1;
    s32 w2;
    s32 w3;
};

void fn_801814F0(Unk_667BA59C *arg0, s32 arg1) {
    struct hd_s hd;
    char buf[0x800];
    struct sc_s sc;
    s32 temp_r27;
    s32 temp_r30;
    u32 temp_r3;
    s32 temp_r8;

    temp_r30 = lbl_80305F9C;
    fn_80137CB4(&sc);
    temp_r27 = fn_8021B55C(temp_r30,
        *(s32 *)((char *)*(s32 *)((char *)fn_8021D358(temp_r30, *((u16 *)&arg0->unk0xC)) + (s32)0x18) + (s32)0x2E8));
    hd.b1 = 1;
    hd.w1 = arg0->unk0xC;
    hd.w2 = arg1;
    hd.b2 = fn_8021F6CC(temp_r30);
    temp_r3 = fn_8020C604(GetChecksum_3(fn_8017471C(lbl_80305EAC, arg0->unk0xC), QB_TRICK), buf, 0x800);
    hd.w3 = temp_r3 >> 2U;
    temp_r8 = temp_r3 + 0x10U;
    sc.f00 = 0x3B;
    sc.f04 = &hd;
    sc.f02 = temp_r8;
    sc.f0C = 2;
    sc.f10 = 8;
    fn_8013DDE4(temp_r27, 0x3B, (u16)temp_r8, &hd, (s32)lbl_802A93DC, 8, 1, 0);
}
