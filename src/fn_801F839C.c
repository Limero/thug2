// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F839C-0x801F83E8 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AE508[];
extern char lbl_802AE50C[];

void fn_801F839C(void *arg0) {
    register void *s __asm__("r9");
    register char *a1 __asm__("r11");
    register char *a2 __asm__("r10");
    register s32 z __asm__("r0");
    Unk_5EF41E38 *p;
    f32 temp_f0;
    f32 temp_f13;

    __asm__ volatile("lis %0,%1@ha" : "=r"(a1) : "s"(lbl_802AE508));
    __asm__ volatile("lis %0,%1@ha" : "=r"(a2) : "s"(lbl_802AE50C));
    __asm__ volatile("lfs %0,%1@l(%2)" : "=f"(temp_f0) : "s"(lbl_802AE508), "r"(a1));
    __asm__ volatile("mr %0,%1" : "=r"(s) : "r"(arg0));
    __asm__ volatile("lfs %0,%1@l(%2)" : "=f"(temp_f13) : "s"(lbl_802AE50C), "r"(a2));
    p = (char *)s + 8;
    *((f32 *)&((Unk_DB0E2BAB *)s)->unk0x8) = temp_f0;
    __asm__ volatile("li %0,0" : "=r"(z));
    ((Unk_4C649A8C *)p)->unk0xC = temp_f13;
    p->unk0x8 = temp_f0;
    p->unk0x4 = temp_f0;
    ((Unk_DB0E2BAB *)s)->unk0x18 = z;
    ((Unk_DB0E2BAB *)s)->unk0x1C = z;
    ((Unk_DB0E2BAB *)s)->unk0x24 = z;
    ((Unk_DB0E2BAB *)s)->unk0x28 = z;
    ((Unk_DB0E2BAB *)s)->unk0x2C = z;
    ((Unk_DB0E2BAB *)s)->unk0x30 = z;
    *((f32 *)&((Unk_DB0E2BAB *)s)->unk0x20) = temp_f0;
}