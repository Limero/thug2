// range 0x801A7DB4-0x801A7DDC (0x28). Byte-identical.
// Identification: running-sum table update — replaces the u16 entry
// arr[i] (arr = self+0x5ae, i = self->0x630) with val and adjusts the
// self->0x5da u16 running sum by (val - old). Likely a per-channel
// audio/event accumulator.
//
// Matching key (recipe 66): the scaled offset must be materialized as
// `s32 off = i * 2` and used via `*(u16 *)((char *)arr + off)` — the
// inline `arr[i]` form makes ngccc put the index term in rA of the
// lhzx/sthx (7-8/10); the temp puts the base in rA (10/10). All math is
// unsigned u16 (no sign casts, which produce a different sum chain).
#include "types.h"
#include "structs.h"
void fn_801A7DB4(Unk_5367668A *self, u16 val) {
    u16 *arr = (u16 *)((char *)self + 0x5ae);
    s32 i = self->unk0x630;
    s32 off = i * 2;
    u32 sum = self->unk0x5DA;
    sum += val - *(u16 *)((char *)arr + off);
    self->unk0x5DA = sum;
    *(u16 *)((char *)arr + off) = val;
}
