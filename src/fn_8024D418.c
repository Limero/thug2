// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024D418-0x8024D480 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802B1A14[];
extern s32 fn_80250E24(CStruct *, s32);
extern void fn_80250E6C(CStruct *, unsigned);
s32 fn_8024D418(void *arg0, s32 arg1) {
    register s32 a0 __asm__("r29");
    register s32 a1 __asm__("r28");
    register u32 v __asm__("r30");
    s32 var_r3;
    u32 off;
    s32 i;
    u32 f2;
    register s32 base __asm__("r9");

    a0 = (s32)arg0;
    a1 = arg1;
    i = fn_80250E24(((Unk_C7387A53 *)a0)->unk0x44, 6);
    __asm__ volatile("lis %0,%1@ha" : "=r"(base) : "s"(lbl_802B1A14));
    off = (u32)i << 2;
    __asm__("" :: "r"(i));
    __asm__ volatile("addi %0,%0,%1@l" : "+r"(base) : "s"(lbl_802B1A14));
    f2 = *((u32 *)&((Unk_C7387A53 *)a0)->unk0x44);
    __asm__ volatile("" ::: "memory");
    fn_80250E6C(f2, (v = *(s32 *)((char *)base + off), (u32)v >> 0x11U));
    v &= 0x1FFFF;
    var_r3 = 0xF - v;
    if (a1 != 0) {
        var_r3 = v;
    }
    return var_r3;
}
