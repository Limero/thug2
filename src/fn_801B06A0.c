// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B06A0-0x801B07D4 (308B). Byte-identical.
// extra_cflags: -fno-strength-reduce -fno-schedule-insns2
#include "types.h"
#include "structs.h"

extern char lbl_802ABD94[];
extern void fn_801B0238(CStruct *, s32);
extern s32 fn_801B0318(Unk_9994C3F5 *);
extern void fn_801B028C(CStruct *, CStruct *);
extern void fn_801B0228(Unk_9994C3F5 *, s32);
extern void fn_801B0230(Unk_C7387A53 *, s32);
// WANT sets r4 at this call site though the callee body reads only r3
// (dead-arg proto, recipe 119).
extern void fn_801B0204(void *, s32);

s32 fn_801B06A0(CStruct *arg0, s32 arg1, s32 arg2) {
    register char *anch __asm__("r24");
    register s32 lastv __asm__("r30");
    register s32 dstv __asm__("r29");
    register s32 t9 __asm__("r9");
    s32 a1;
    s32 i;
    s32 off;
    s32 off2;
    s32 ret;
    s32 src_off;

    a1 = arg1;
    i = 0;
    if (i < arg0->unk0x4) {
        off = 0;
        do {
            fn_801B0238(arg0->unk0x8 + off, 0);
            off += 0x14;
            i += 1;
        } while (i < arg0->unk0x4);
    }
    i = 0;
    if (i < arg0->unk0x4) {
        off2 = 0;
        do {
            ret = fn_801B0318(arg0->unk0x8 + off2);
            if (a1 > ret) {
                register s32 c9 __asm__("r9");
                c9 = arg0->unk0x4;
                __asm__ volatile("lis %0,%1@ha"
                                 : "=r"(anch)
                                 : "s"(lbl_802ABD94));
                lastv = c9 - 1;
                if (lastv > i) {
                    t9 = lastv * 0x14;
                    dstv = t9;
                    __asm__ volatile("" : "+r"(t9));
                    src_off = t9 - 0x14;
                    do {
                        void *dsta =
                            (void *)(arg0->unk0x8 +
                                     dstv);
                        void *srca =
                            (void *)(arg0->unk0x8 +
                                     src_off);
                        src_off -= 0x14;
                        fn_801B028C(dsta, srca);
                        dstv -= 0x14;
                        lastv -= 1;
                    } while (lastv > i);
                }
                fn_801B0228(arg0->unk0x8 + off2, a1);
                fn_801B0230(arg0->unk0x8 + off2, arg2);
                fn_801B0204(arg0->unk0x8 + off2,
                            anch - 0x426C);
                fn_801B0238(arg0->unk0x8 + off2, 1);
                return i;
            }
            i += 1;
            off2 += 0x14;
        } while (i < arg0->unk0x4);
    }
    return -1;
}
