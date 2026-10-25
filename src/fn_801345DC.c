// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801345DC-0x8013465C (128B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
s32 fn_800113E4(Unk_C7387A53 *);
s32 fn_80134CB8(void);
void fn_80134584(CScript *, Unk_C8FEE62D *);
void fn_801345DC(Unk_C7387A53 *arg0, s32 arg1) {
    register void *anchor __asm__("r29");
    Unk_C7387A53 *temp_r9;
    s32 var_f20;

    __asm__ volatile("lis %0,%1@ha" : "=r"(anchor) : "s"(lbl_802FFE98));
top_1:
    __asm__ volatile("lwz %0,%1@l(%2)" : "=r"(temp_r9) : "s"(lbl_802FFE98), "r"(anchor));
    if (arg1 > (fn_800113E4(temp_r9->unk0x12C) - 0x80)) {
        goto big_2;
    }
    goto hdr_4;
call_5:
    fn_80134584(arg0, (void *)var_f20);
hdr_4:
    if (fn_80134CB8() <= 0x63) {
        return;
    }
    var_f20 = arg0->unk0x20;
    if (var_f20 != 0) {
        goto call_5;
    }
    return;
big_2:
    fn_80134584(arg0, arg0->unk0x20);
    goto top_1;
}
