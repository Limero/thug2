// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AF244-0x801AF278 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802ABD08[];
void fn_801AF244(void *arg0) {
    register void *obj __asm__("r10");
    register s32 walk_r9 __asm__("r9");
    register s32 zero_r8 __asm__("r8");
    register s32 lblv __asm__("r11");

    obj = arg0;
    __asm__("" : "+r"(obj));
    __asm__ volatile("lis %0, %1@ha" : "=r"(lblv) : "s"(lbl_802ABD08));
    walk_r9 = (s32)((char *)obj + 4);
    __asm__ volatile("li %0, 0" : "=r"(zero_r8));
    __asm__ volatile("addi %0, %0, %1@l" : "+r"(lblv) : "s"(lbl_802ABD08));
    ((Unk_C8FEE62D *)walk_r9)->unk0x14 = lblv;
    ((Unk_C8FEE62D *)walk_r9)->unk0x4 = -1;
    ((Unk_C8FEE62D *)walk_r9)->unk0xC = walk_r9;
    ((Unk_C8FEE62D *)walk_r9)->unk0x10 = walk_r9;
    ((Unk_C8FEE62D *)walk_r9)->unk0x8 = zero_r8;
    *(s32 *)obj = zero_r8;
}
