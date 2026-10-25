// range 0x8000A510-0x8000A578 (0x68). Byte-identical.
// Identification: node-family state push/pop wrapper (adjacent to the
// A13C/A37C container constructors, right after fn_8000A3DC). The self+4
// counter is bumped +1, the object at self+0x3c is stashed to self+0x40 and
// handed (with the passthrough arg4 and self+0x8) to fn_80009D88, the counter
// is restored -1, fn_8000A0A8(self) runs, and self+0x44/0x48 are cleared.
// The +/-1 counter pair around the call looks like a re-entrancy/lock guard.
//
// Matching key (recipe 243): the two pre-call stores want order
// [self->0x40 = p; self->4 = n+1] and any `s32 n` temp makes ngccc emit the
// self->4 store FIRST regardless of source order (24/26). Inlining the
// increment at the store — `self->4 = self->4 + 1` — plus keeping the p-store
// first makes it 26/26 byte-identical. Likewise the trailing two zero-stores
// need source order [0x44, 0x48] (rotate-right emit).
#include "types.h"
#include "structs.h"
extern void fn_80009D88(void *, s32, void *);
extern void fn_8000A0A8(void *);
void fn_8000A510(Unk_C8FEE62D *self, s32 arg4) {
    void *p = *((void * *)&self->unk0x3C);
    *((void * *)&self->unk0x40) = p;
    self->unk0x4 = self->unk0x4 + 1;
    fn_80009D88(p, arg4, *((void * *)&self->unk0x8));
    self->unk0x4 = self->unk0x4 - 1;
    fn_8000A0A8(self);
    self->unk0x44 = 0;
    self->unk0x48 = 0;
}