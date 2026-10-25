// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A2584-0x801A25E4 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

void fn_801A1998(void *, void *);
void fn_801A1A9C(void *);
s32 fn_800AB404(void *, s32, void *);

s32 fn_801A2584(void *arg0, s32 arg1, void *arg2) {
    switch (arg1) {
    case (s32)QB_SETTARGETOBJECT:
        fn_801A1998(arg0, arg2);
        return 1;
    case (s32)QB_CLEARTARGETOBJECT:
        fn_801A1A9C(arg0);
        return 1;
    }
    return fn_800AB404(arg0, arg1, arg2);
}
