// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80125FF0-0x80126064 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Movie-player accessor block (docs/neversoft-audio-engine.md §8,
// fn_80124C20-fn_80126FF4 same-shaped 116B functions): registers a freshly
// created object into the 2-slot global table lbl_80303280[lbl_80303290]
// (allocation via Mem_Alloc2(0x5C) + typed constructor fn_80011F94(id 0xC,
// arg0, arg1)) and sets the matching in-use flag lbl_80303288[idx] = 1.
// Suggested rename: MoviePlayerRegister12
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_80303280[];
extern s32 lbl_80303288[];
extern s32 lbl_80303290;
void *fn_80011F94(Unk_78674569 *, s32, s32, s32);
void fn_80125FF0(s32 arg0, s32 arg1) {
    s32 *dst = &lbl_80303280[lbl_80303290];
    *dst = (s32)fn_80011F94(Mem_Alloc2(0x5C), 0xC, arg0, arg1);
    lbl_80303288[lbl_80303290] = 1;
}
