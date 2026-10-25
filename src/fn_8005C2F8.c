// fn_8005C2F8 — table-dispatched helper call with a stack-copied arg (8th
// matched function).
//
// Shape (16 words, exact match with ProDG 3.7 -O2 -G0): small GPR-only
// frame; the u32 arg is copied to a stack slot, the table at o+8 is loaded,
// `this` is derived via the s16 offset at table index 0x50, and the member
// fn pointer at index 0x29 is called indirectly with (this, &local).
//
// This is an EngineX-style message dispatch: the callee is a member fn
// pointer in a vtable-like table at o+8, and the s16 at t[0x50] is an
// offset into the object used to derive `this`.
//
// Note: sibling helpers fn_8005C174 (off 0x68/0x6C), fn_8005C2B8
// (0x98/0x9C) and fn_8005C3A0 (0xB8/0xBC) are parked: their originals load
// the arg temp into r0 and store it before the lha, while every ngccc build
// uses r11 and defers the store (same unreproducible-allocation class as the
// FPR frame quirk, AGENTS.md §4c).
#include "types.h"

typedef struct {
    char pad[8];
    void **table; /* offset 8 */
} Obj5C2F8;

void fn_8005C2F8(Obj5C2F8 *o, u32 *arg) {
    u32 local = *arg;
    void **t = o->table;
    void (*fp)(void *, u32 *) = (void (*)(void *, u32 *))t[0x29]; /* 0xA4 */
    fp((char *)o + (signed short)((s16 *)t)[0x50], &local);      /* 0xA0 */
}
