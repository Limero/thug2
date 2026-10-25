// fn_8005F28C — table-dispatch helper that forwards its first arg and
// returns it (10th matched function). GPR-only (saves r30), so it matches
// cleanly with ngccc (see AGENTS.md §4c — only FPR-saving frames have the
// +8 quirk).
//
// Shape (17 words): small frame saving one callee-saved reg; loads the
// table at other+0x14, derives the second arg via the s16 offset at table
// index 0x48, and calls the member fn pointer at index 0x25 indirectly with
// (o, other + off) — note the arg order — then returns o.
//
// The `mr r30,r3` + `mr r3,r30` around the call means the function returns
// its first argument `o` — it must survive the indirect call.
#include "types.h"

typedef struct {
    char pad[0x14];
    void **table; /* offset 0x14 */
} Obj5F28C;

void *fn_8005F28C(void *o, Obj5F28C *other) {
    void **t = other->table;
    void (*fp)(void *, void *) = (void (*)(void *, void *))t[0x25]; /* 0x94 */
    fp(o, (char *)other + (signed short)((s16 *)t)[0x48]);          /* 0x90 */
    return o;
}
