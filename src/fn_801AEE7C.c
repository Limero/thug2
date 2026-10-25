// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AEE7C-0x801AEF14 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802ABCD8[];
extern char lbl_802ABCF0[];
extern void fn_80126A30(Unk_5AA7B5D7 *);
extern void fn_80128FB4(Unk_F8A5095F *, s32);

// PARKED 94.7%: single scheduler slot-fill — want emits [lwz r0][lwz r11][addi lbl@l] at the
// lbl_802ABCF0 store; GOT inserts the addi after the FIRST load. All sched flags resist
// (-fno-schedule-insns fixes order but flips reg assignment r9->r11 net-worse; insns2 hoists
// andi.; spec/interblock/strength no-ops). B-stmt base-first staging fixed its load pair.
void fn_801AEE7C(Unk_C8FEE62D *arg0, s32 arg1) {
    s32 temp_r3;
    s32 temp_r0;
    s32 temp_r11;
    s32 temp_r9;

    temp_r3 = arg0->unk0x68;
    arg0->unk0x14 = (s32)lbl_802ABCD8;
    if (temp_r3 != 0) {
        fn_80126A30(temp_r3);
        temp_r3 = arg0->unk0x68;
        if (temp_r3 != 0) {
            fn_80128FB4(temp_r3, 3);
        }
    }
    arg0->unk0x14 = (s32)lbl_802ABCF0;
    temp_r11 = arg0->unk0x10;
    temp_r0 = arg0->unk0xC;
    ((Unk_1D62F22E_2 *)temp_r11)->unk0xC = temp_r0;
    temp_r9 = arg0->unk0xC;
    ((Unk_1D62F22E_2 *)temp_r9)->unk0x10 = arg0->unk0x10;
    arg0->unk0xC = arg0;
    arg0->unk0x10 = arg0;
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
