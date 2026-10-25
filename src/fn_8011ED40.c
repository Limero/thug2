// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011ED40-0x8011ED64 (36B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// fn_8011ED40: voice-entry active test — lbl_8038EBB8[idx*2] != 0
// (8-byte voice entries). Suggested rename: fn_VoiceIsActive.
// 2026-09-04: REWRITTEN from the asm-pinned form to plain C.
// The old note claimed both regs must be `register asm` pinned or GCC swaps
// the lwzx rA/rB operands (doc-02 class) — FALSIFIED: declaring the table
// `extern s32 lbl_8038EBB8[]` and indexing `lbl_8038EBB8[idx * 2]` makes GCC
// emit lwzx with the BASE as rA exactly as retail; the char* + idx*8 spelling
// is the one that puts the scaled index in rA (88.9% ceiling).
#include "types.h"
extern s32 lbl_8038EBB8[];
bool fn_8011ED40(s32 idx) {
    if (lbl_8038EBB8[idx * 2] != 0) {
        return true;
    }
    return false;
}
