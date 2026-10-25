// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024DC14-0x8024DD84 (368B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8024DD84(Unk_C7387A53 * a, CStruct * b, s32 c, s32 d, s32 e);
void fn_8024E1F0(CStruct * a, CStruct * b, CStruct * c);

void fn_8024DC14(CStruct *arg0, Unk_12004030 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp8[2];
    s32 v;
    s32 avg;
    s32 x;
    s32 y;
    register s32 xp __asm__("r9");
    register s32 yp __asm__("r10");

    fn_8024DD84(arg0, (s32)&sp8[0], arg2, arg3, 0);
    if (arg4 == 0) {
        if (arg1->unk0xDC & 8) {
            v = sp8[1];
            sp8[1] = arg4;
            avg = v / 2;
            fn_8024E1F0(arg0, (char *)arg1 + 8, &sp8[0]);
            fn_8024E1F0(arg0, (char *)arg1 + 0x10, &sp8[0]);
            arg1->unk0xC = (arg1->unk0xC + avg) << 1;
            arg1->unk0x14 = (arg1->unk0x14 + avg) << 1;
            return;
        }
        fn_8024E1F0(arg0, (char *)arg1 + 8, &sp8[0]);
        xp = arg1->unk0x8;
        yp = arg1->unk0xC;
        arg1->unk0x10 = xp;
        arg1->unk0x14 = yp;
        arg1->unk0x18 = xp;
        arg1->unk0x1C = yp;
        arg1->unk0x20 = xp;
        arg1->unk0x24 = yp;
        return;
    }
    fn_8024E1F0(arg0, (char *)arg1 + 8, &sp8[0]);
    fn_8024DD84(arg0, (s32)&sp8[0], arg2, arg3, 1);
    fn_8024E1F0(arg0, (char *)arg1 + 0x10, &sp8[0]);
    fn_8024DD84(arg0, (s32)&sp8[0], arg2, arg3, 2);
    fn_8024E1F0(arg0, (char *)arg1 + 0x18, &sp8[0]);
    fn_8024DD84(arg0, (s32)&sp8[0], arg2, arg3, 3);
    fn_8024E1F0(arg0, (char *)arg1 + 0x20, &sp8[0]);
}
