// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A4540-0x801A46F8 (440B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802FFE98[];
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void CStruct_dtor(s32);
void fn_8000F2F8(Unk_B0F19D72 *, s32);
void fn_8000F320(Unk_B0F19D72 *);
void fn_8003AE60(s32);
void fn_8003A8D0(s32);
void fn_8003AE28(s32);
void fn_8003A99C(s32, s32, s32);
void fn_80127E70(s32, s32, s32, s32);
void fn_80126FF4(s32, s32);
s32 fn_80128E34(s32, s32, s32 *, s32);
s32 GetChecksum_2(s32, s32, s32 *, s32);
s32 GetStructure_2(s32, s32, s32 *, s32);
void GetString(s32, s32, s32 *, s32);
s32 GetStructure(s32, s32);
s32 fn_801A572C(s32);

bool fn_801A4540(s32 arg0, CStruct *arg1) {
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r30;
    s32 temp_r31;

    temp_r30 = arg0 + 4;
    temp_r31 = arg0 + 0x6C;
    fn_8000F2F8(*(Unk_B0F19D72 **)&lbl_802FFE98, (*(Unk_B0F19D72 **)&lbl_802FFE98)->unk0x5F8);
    fn_8003AE60(temp_r30);
    fn_8003A8D0(temp_r30);
    CStruct_dtor(temp_r31);
    fn_80127E70(temp_r31, QB_TRICK_MAPPING, 0xB, CStruct_ctor(CStruct_new(8)));
    fn_80127E70(temp_r31, QB_SPECIALS, 0xB, CStruct_ctor(CStruct_new(8)));
    fn_8000F320(*(Unk_B0F19D72 **)&lbl_802FFE98);
    if (arg1 != 0) {
        fn_80128E34(arg1, QB_DEFAULT_APPEARANCE, &sp8, 1);
        fn_8003A99C(temp_r30, sp8, 1);
        CStruct_dtor(temp_r31);
        fn_80126FF4(temp_r31, arg1);
        if (fn_801A572C(arg0) == 0) {
            fn_8000F2F8(*(Unk_B0F19D72 **)&lbl_802FFE98, (*(Unk_B0F19D72 **)&lbl_802FFE98)->unk0x5F8);
            fn_8003AE28(temp_r30);
            fn_8000F320(*(Unk_B0F19D72 **)&lbl_802FFE98);
        }
        GetChecksum_2(arg1, QB_DEFAULT_TRICK_MAPPING, &spC, 1);
        temp_r30 = GetStructure(spC, 1);
        GetStructure_2(temp_r31, QB_TRICK_MAPPING, &sp10, 1);
        CStruct_dtor(sp10);
        fn_80126FF4(sp10, temp_r30);
        GetChecksum_2(temp_r31, QB_NAME, &sp14, 1);
        if (sp14 != QB_CUSTOM) {
            GetString(temp_r31, QB_LAST_NAME, &sp18, 1);
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// REUSABLE ngccc GOT/REG-ALLOCATION RULE (w75/0x801A4540, 100.0%):
//
// A C LOCAL bound to a multi-use global pointer is the WRONG shape when retail
// re-loads the global every time. Compare:
//
//   mgr = *(T **)&lbl_802FFE98;   /* 4 uses */        -> 6.3%
//   fn_8000F2F8(mgr, mgr->unk0x5F8); ...            (one value kept in a
//                                                       callee-saved reg)
//   ... fn_8000F320(mgr); ...                       (address const remat in
//                                                       a CALLER-saved reg)
//
// vs the 100% shape: the global's ADDRESS constant held in a callee-saved
// reg, with the VALUE re-loaded from it at each of the 4 use sites, dead
// after each use:
//
//   fn_8000F2F8(*(T **)&lbl_802FFE98, (*(T **)&lbl_802FFE98)->unk0x5F8);  -> 100%
//   ... the same deref spelled out at each of the 4 use sites ...
//
// i.e. ngccc/GCC-2.95 allocates hard regs for C LOCAL VARIABLES first, so a
// local steals the last callee-saved register away from the symbol-address
// pseudo and the reload pass then keeps the (rematerialisable) constant in a
// volatile reg and the value in a callee-saved one — the exact OPPOSITE of
// retail. Spelled out as a repeated expression the loaded value is a plain
// CSE pseudo (not a local var), loses the hard-reg competition to the
// address constant, and ends up re-materialised per use. Same instruction
// count, same callee-saved set, byte-identical.
//
// Generalises: whenever the want shows the address constant of a global held
// in a callee-saved reg plus repeated reloads of the SAME global's value,
// DELETE the C local that cached it. If instead the want shows the address
// re-materialised in a volatile reg, the C local is correct.
//
// (The 4 value-load displacements and the address-constant immediate are
// ADDR16_LO / ADDR16_HA relocs against the same symbol and are masked by the
// scorer, so the hand check is: one HA reloc + N LO relocs, all named
// lbl_XXXXXXXX, all REL24s pointing at the wanted callees. Verified for this
// function.)
// ---------------------------------------------------------------------------
