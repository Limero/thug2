// fn_800575DC — table-dispatched helper call with a stack-copied arg (9th
// matched function). Same family as fn_8005C2F8: EngineX-style dispatch
// through a table pointer stored at object offset 0x284, with an s16
// `this`-offset at table slot 0x48 (index 0x24) and a member-fn pointer at
// 0x4C (index 0x13).
//
// Shape (16 words, exact match with ProDG 3.7 -O2 -G0): small GPR-only
// frame; the u32 arg is copied to a stack slot, the table at o+0x284 is
// loaded, `this` is derived via the s16 offset at table index 0x24, and the
// member fn pointer at index 0x13 is called indirectly with (this, &local).
#include "types.h"

typedef struct {
    char pad[0x284];
    void **table; /* offset 0x284 */
} Obj575DC;

void fn_800575DC(Obj575DC *o, u32 *arg) {
    u32 local = *arg;
    void **t = o->table;
    void (*fp)(void *, u32 *) = (void (*)(void *, u32 *))t[0x13]; /* 0x4C */
    fp((char *)o + (signed short)((s16 *)t)[0x24], &local);      /* 0x48 */
}
