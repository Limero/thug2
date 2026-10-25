// range 0x800099AC-0x80009A04 (88B). Byte-identical.
// Identification: allocator wrapper, sibling of Mem_NewZero. Calls
// fn_8000F10C(obj, size, <uninit>, flag) — the uninitialized 3rd register arg
// produces want's `mr r6,r4` (flag in r6) with r5 untouched; then memset().
// The `s32 gap` pass-through is required to reproduce the arg-to-r6 layout.
#include "types.h"
#include "structs.h"
void *fn_8000F10C(Unk_4897C6F8 *, s32, s32, Unk_E15B2970 *);
void *memset(void *, s32, s32);
extern char lbl_802FFE98[];
void *fn_800099AC(s32 size, Unk_E15B2970 *arg, s32 arg0) {
    void *obj;
    s32 gap;
    obj = fn_8000F10C(*(void **)lbl_802FFE98, size, gap, arg);
    if (obj != 0) {
        memset(obj, 0, size);
    }
    return obj;
}