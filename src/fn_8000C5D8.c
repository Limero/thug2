// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip matching)
// range 0x8000C5D8-0x8000C6A0 (0xC8 = 200B). Byte-identical (50/50).
// Link-level exactness verified against the full linked DOL.
//
// Identification: state-gated per-slot sign flag + motor/subsystem call —
// same family as fn_8000C938 / fn_8000C6A0 (doc-47). If self->0xc8 == 0,
// self->0xdc == 2, (self->0xcc & 2) set, and 0 <= idx < self->0xd4, writes
// buf[idx] = ((f32)(f64)(s32)value > 0.0f) into the byte buffer at self+0x60,
// then calls PADControlMotor (fn_80269394, the Dolphin SDK rumble API) with
// (self->0x10, (self->0x60 & 0xffff0000) ? 1 : 0).
//
// Matching notes (recipes 246-248):
//  - The flag must be materialized as `flag = 1; if (!(x & 2)) flag = 0;`
//    then `if (!flag) return;` (the C938 bool-materialization idiom), or
//    ngccc emits a direct andi./beq and diverges.
//  - The comparison is `> 0.0f` (rlwinm SH=0x1e); `< 0.0f` emits SH=0x1d.
//  - The u32->float path goes through the signed magic-constant conversion
//    (xoris + 0x4330000080000000) because the source casts (s32)value.
//  - The byte store needs an explicit `u8 *base = (u8*)self + 0x60;`
//    then `base[idx] = ...` to get the indexed `stbx r0,r7,r4` form
//    (a bare `*(u8*)(self+0x60+idx)` folds into `add r7,r4,r3; stb`).
//
// Suggested rename: Fn_8000C5D8_SetSlotSignFlagAndKick — marks slot idx of
// the self+0x60 byte array as "signed/positive" and nudges the subsystem.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void PADControlMotor(void *, void *);
void fn_8000C5D8(Unk_A0A7249E *self, s32 idx, u32 value) {
    s32 flag;
    u8 *base;
    if (self->unk0xC8 != 0)
        return;
    if (self->unk0xDC != 2)
        return;
    flag = 1;
    if (!(self->unk0xCC & 2))
        flag = 0;
    if (!flag)
        return;
    if (idx < 0)
        return;
    if (idx >= self->unk0xD4)
        return;
    base = (u8 *)((char *)self + 0x60);
    base[idx] = ((f32)(f64)(s32)value) > 0.0f;
    PADControlMotor(self->unk0x10,
                    (void *)((self->unk0x60 & QB_UNKNOWN_0xFFFF0000) ? 1 : 0));
}
