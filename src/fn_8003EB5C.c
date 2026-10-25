// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003EB5C-0x8003EC7C (288B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -Os -fno-strength-reduce
#include "types.h"
void memcpy();
s32 strlen(const char *);
typedef struct Rec24 { s32 f0; s32 f1; s32 f2; s32 f3; s32 f4; s32 f5; } Rec24;
void *fn_8003EB5C(void *arg0, void *arg1) {
    Rec24 *dst1;
    Rec24 *src1;
    Rec24 *dst2;
    Rec24 *src2;
    char *name;
    char *name_dst;
    s32 cnt1;
    s32 cnt2;
    s32 len;
    s32 t;

    name = (char *)arg1;
    dst1 = (Rec24 *)((char *)arg0 + 0x40);
    src1 = (Rec24 *)name;
    cnt1 = 0x4410;
    do {
        cnt1 -= 0x18;
        dst1->f0 = src1->f0;
        dst1->f1 = src1->f1;
        dst1->f2 = src1->f2;
        dst1->f3 = src1->f3;
        dst1->f4 = src1->f4;
        t = src1->f5;
        src1++;
        dst1->f5 = t;
        dst1++;
    } while (cnt1 != 0);
    dst1->f0 = src1->f0;
    t = src1->f1;
    __asm__("li %0,0x30" : "=r"(cnt2) : "r"(t));
    dst1->f1 = t;
    dst1->f2 = src1->f2;
    dst1->f3 = src1->f3;

    dst2 = (Rec24 *)((char *)arg0 + 8);
    name += 0x4420;
    name_dst = (char *)arg0 + 0x4460;
    src2 = (Rec24 *)name;
    do {
        cnt2 -= 0x18;
        dst2->f0 = src2->f0;
        dst2->f1 = src2->f1;
        dst2->f2 = src2->f2;
        dst2->f3 = src2->f3;
        dst2->f4 = src2->f4;
        t = src2->f5;
        src2++;
        dst2->f5 = t;
        dst2++;
    } while (cnt2 != 0);
    dst2->f0 = src2->f0;
    dst2->f1 = src2->f1;

    name += 0x38;
    len = strlen(name) + 1;
    memcpy(name_dst, name, len);
    return name + len;
}
