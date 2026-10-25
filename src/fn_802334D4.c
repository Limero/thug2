// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802334D4-0x8023357C (168B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_8029FC18[];
s32 fn_8019CF2C(s32);
void fn_8019CF94(void);
void fn_8019D3E0(s32, s32);

// WINNER fn_802334D4 (168B) - doc 23. Two plain pads declared after the OOB
// anchors; ONE empty asm pins all four locals as "m" operands at function END:
// all escaped -> frame grows to 0x20; same-size pads tie -> declaration order
// puts them HIGH (0x10/0x14); bases stay addi rN,r1,8 / r1,0xc.
void fn_802334D4(Unk_C7387A53 *arg0) {
    s32 spC;
    s32 sp8;
    s32 padA;
    s32 padB;
    s32 var_r9;

    ((Unk_59AB5482 *)&sp8)->unk0xC = (s32)lbl_8029FC18;
    ((Unk_59AB5482 *)&spC)->unk0x4 = fn_8019CF2C(0);
    if (arg0->unk0x44 == QB_EDIT) {
        var_r9 = 1;
        if (!(arg0->unk0x4C & 2))
            var_r9 = 0;
        if (var_r9 == 0) {
            fn_8019D3E0(((Unk_59AB5482 *)&spC)->unk0x4, 0);
        } else {
            goto block_5;
        }
    } else {
block_5:
        fn_8019D3E0(((Unk_59AB5482 *)&spC)->unk0x4, 1);
    }
    ((Unk_59AB5482 *)&sp8)->unk0xC = (s32)lbl_8029FC18;
    fn_8019CF94();
    __asm__("" : : "m"(sp8), "m"(spC), "m"(padA), "m"(padB));
}
