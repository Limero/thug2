// range 0x8012ED7C-0x8012ED98 (0x1C). Byte-identical.
// Identification: guarded getter — returns self->4 if self is non-null,
// otherwise the global lbl_803032DC.
//
// Matching key: the two-return form must be written as an if/else with a
// result variable (or ternary); the early-return form makes ngccc lay out
// the global path first (2/7). if/else materialization gives want's
// self-path-first layout (7/7).
#include "types.h"
#include "structs.h"
extern char lbl_803032DC[];
s32 fn_8012ED7C(CStruct *self) {
    s32 r;
    if (self != 0)
        r = self->unk0x4;
    else
        r = *(s32 *)lbl_803032DC;
    return r;
}
