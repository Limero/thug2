// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80143B7C-0x80143C94 (280B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// NOTE (2026-10-04): this object carries a PRIVATE .rodata pool (1 site),
// retargeted by tools/fix_fp_pool.py to lbl_8029F820 in .rodata2 and then
// emptied. It previously mis-linked (2 bytes, 0x10000 page skew) because the
// pool site is referenced by more than one ADDR16 reloc and the old
// proximity-based HA/LO pairing handed the extra LO to the next site
// (recipes §6gu). Any change to the literals here will re-expose that.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_801C51A4(Unk_C8FEE62D *, s32);
void fn_801F0F48(Unk_C7387A53 *);
void fn_80206E24(Unk_90685748 *);
void fn_80206E7C(Unk_76553646 *);
void fn_8020A35C(Unk_13928190 *);
void fn_80206E48(void *);
void fn_80209268(Unk_CF8B1206 *);
void fn_8020C5BC(Unk_90685748 *);
void fn_801F1250(Unk_C7387A53 *);
void fn_801812B8(s32, s32, f32);
void fn_801812DC(s32, s32, f32);
void fn_800DE9A4(CScript *);
void fn_800DDD98(s32, void *);
void fn_800DDDAC(s32, void *);
void fn_80143B7C(Unk_9D99273B *arg0) {
    Unk_31DE137E *temp_r3;

    temp_r3 = GetChecksum_3((s32)arg0, QB_SKATERPHYSICSCONTROL);
    if (temp_r3->unk0x1C != 0) {
        fn_801C51A4(temp_r3, 0);
    }
    fn_801F0F48(GetChecksum_3((s32)arg0, QB_SKATERFLIPANDROTATE));
    fn_80206E24(arg0->unk0x284);
    fn_80206E7C(arg0->unk0x284);
    fn_8020A35C(arg0->unk0x284);
    fn_80206E48(arg0->unk0x284);
    fn_80209268(arg0->unk0x284);
    fn_8020C5BC(arg0->unk0x284);
    fn_801F1250(GetChecksum_3((s32)arg0, QB_SKATERSTATE));
    *(s32 *)(arg0->unk0x27C + (s32)0x1FC) = 0;
    fn_801812B8(*(s32 *)(arg0->unk0x2A4 + (s32)0x1C), 0, 0.0f);
    fn_801812DC(*(s32 *)(arg0->unk0x2A4 + (s32)0x1C), 0, 0.0f);
    if ((s32) arg0->unk0x288 != 0) {
        fn_800DE9A4(arg0->unk0x288);
    }
    fn_800DDD98(arg0->unk0x280, (char *)arg0 + 0x58);
    fn_800DDDAC(arg0->unk0x280, (char *)arg0 + 0x88);
    *(s32 *)((char *)GetChecksum_3((s32)arg0, QB_SKATERSTANCEPANEL) + (s32)0x1C) = -1;
}
