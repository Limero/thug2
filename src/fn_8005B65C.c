// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005B65C-0x8005B68C (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct S5B65C {
    char pad0[4];
    f32 unk4;
    f32 unk8;
} S5B65C;
void fn_8005B68C(S5B65C *);
bool fn_8005B65C(S5B65C *arg0, f32 farg0) {
    arg0->unk8 = farg0;
    arg0->unk4 = farg0;
    fn_8005B68C(arg0);
    return true;
}
