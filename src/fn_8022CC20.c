// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022CC20-0x8022CD10 (240B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802B04C8[];
extern char lbl_802B04D0[];
extern char lbl_802B04D8[];
extern char lbl_802B04E8[];
void *fn_80011F94(Unk_78674569 *, s32, s32, void *);
/* sprintf deliberately UNPROTOTYPED: varargs callee, want keeps crclr cr1eq */
void fn_8022CC20(Unk_C8FEE62D *arg0, s32 arg1, s32 arg2, s32 arg3) {
    char sp8[0x40];
    char sp48[0x40];
    register char *pg __asm__("r9");
    register s32 wv __asm__("r10");
    register s32 bv __asm__("r8");
    s32 hv;
    char *temp_r9;
    register char *temp_r11 __asm__("r11");
    char *temp_r30;
    char *var_r31;

    if (arg3 != 0) {
        __asm__ volatile("lis %0,%1@ha" : "=r"(pg) : "s"(lbl_802B04C8));
        temp_r11 = (char *)arg0 + 0x18;
        __asm__ volatile("lwz %0,%1@l(%2)" : "=r"(wv) : "s"(lbl_802B04C8), "r"(pg));
        __asm__ volatile("mr %0,%1" : "=r"(var_r31) : "r"(temp_r11));
        __asm__ volatile("addi %0,%0,%1@l" : "+r"(pg) : "s"(lbl_802B04C8));
        hv = *((u16 *)&((Unk_90ACC040 *)pg)->unk0x4);
        bv = ((Unk_90ACC040 *)pg)->unk0x6;
        *(s32 *)temp_r11 = wv;
        ((Unk_90ACC040 *)temp_r11)->unk0x6 = bv;
        *((u16 *)&((Unk_90ACC040 *)temp_r11)->unk0x4) = hv;
    } else {
        __asm__ volatile("lis %0,%1@ha" : "=r"(pg) : "s"(lbl_802B04D0));
        temp_r11 = (char *)arg0 + 0x18;
        __asm__ volatile("lwz %0,%1@l(%2)" : "=r"(wv) : "s"(lbl_802B04D0), "r"(pg));
        __asm__ volatile("mr %0,%1" : "=r"(var_r31) : "r"(temp_r11));
        __asm__ volatile("addi %0,%0,%1@l" : "+r"(pg) : "s"(lbl_802B04D0));
        hv = *((s32 *)&((Unk_90ACC040 *)pg)->unk0x4);
        *(s32 *)temp_r11 = wv;
        *((s32 *)&((Unk_90ACC040 *)temp_r11)->unk0x4) = hv;
    }
    sprintf(sp8, (s32)lbl_802B04D8, var_r31);
    temp_r30 = sp48;
    sprintf(sp48, (s32)lbl_802B04E8, var_r31);
    arg0->unk0x10 = (s32)fn_80011F94((void *)Mem_Alloc2(0x5C), 0x38, arg1, sp8);
    arg0->unk0x14 = (s32)fn_80011F94((void *)Mem_Alloc2(0x5C), 0x24, arg2, temp_r30);
}
