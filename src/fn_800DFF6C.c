// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DFF6C-0x800E0030 (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct { char pad0x0[0x114]; s32 unk0x114; } C_DFF6C;
typedef struct { char pad0x0[0xC]; C_DFF6C *unk0xC; char pad0x10[0x10]; s32 unk0x20; char pad0x24[0x500]; s32 unk0x524; s32 unk0x528; } S_DFF6C;
void fn_800E021C(S_DFF6C *, void *);
s32 fn_800DFDFC(S_DFF6C *);
void fn_800AAA34(void *);
void fn_800AA1F4(void *, void *);
void fn_800DFF6C(S_DFF6C *arg0, void *arg1) {
    s32 flag;
    s32 ret;
    s32 has;
    flag = 1;
    if ((arg0->unk0xC->unk0x114 & 1) == 0) {
        flag = 0;
    }
    if (flag != 0) {
        return;
    }
    fn_800E021C(arg0, arg1);
    ret = fn_800DFDFC(arg0);
    has = 0;
    if (arg0->unk0x524 != 0 || arg0->unk0x528 != 0) {
        has = 1;
    }
    if (has != 0) {
        goto doAAA;
    }
    if (ret == 0) {
        goto doAA;
    }
doAAA:
    fn_800AAA34((char *)arg0 + 0x24);
    if (ret != 0) {
        arg0->unk0x20 = 0;
    }
    goto end;
doAA:
    fn_800AA1F4((char *)arg0 + 0x24, arg1);
end:;
}
