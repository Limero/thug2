// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802053AC-0x802053E4 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// ID: QB script callback — forwards the object's unk0x30 flag with the
// global QB key at lbl_80302C34 to fn_8011A6A8 (flag-set notify); always
// returns 1.
#include "types.h"
#include "structs.h"
extern char lbl_80302C34[];

bool fn_802053AC(Unk_C7387A53 *arg0) {
    extern s32 fn_8011A6A8(s32, s32);
    s32 flag = arg0->unk0x30;
    if (flag != 0)
        fn_8011A6A8(*(s32 *)lbl_80302C34, flag);
    return true;
}