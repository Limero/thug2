// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CDE04-0x801CDE30 (44B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305EAC[];
s32 fn_801CDE04(s32 arg0) {
    register s32 a0 __asm__("r7");
    register char *t __asm__("r8");
    register s32 idx __asm__("r9");
    register char *anchor __asm__("r10");
    register char *p __asm__("r11");
    register s32 ret __asm__("r3");
    s32 v;

    a0 = arg0;
    __asm__ volatile("lis %0,%1@ha" : "=r"(anchor) : "s"(lbl_80305EAC));
    t = *((char * *)&((Unk_C7387A53 *)a0)->unk0xC);
    __asm__("li %0,1" : "=r"(ret));
    __asm__ volatile("lwz %0,%1@l(%2)" : "=r"(p) : "s"(lbl_80305EAC), "r"(anchor));
    idx = ((Unk_5F9B5F15 *)t)->unk0x2E8;
    p += (s32)0x3A8;
    v = *(s32 *)(p + (idx << 4));
    ((Unk_C7387A53 *)a0)->unk0x320 = v;
    return ret;
}
