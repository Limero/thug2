// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009666C-0x800966D8 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8037B614[];
void fn_8001D424(void *);
void PSMTX_MultVec(s32, void *, void *);
typedef struct { f32 f0, f4, f8; } AV;
f32 fn_8009666C(AV *arg0) {
    f32 sp8[3];
    f32 sp18[3];
    fn_8001D424(sp8);
    fn_8001D424(sp18);
    sp8[0] = arg0->f0;
    sp8[1] = arg0->f4;
    sp8[2] = arg0->f8;
    PSMTX_MultVec((s32)lbl_8037B614, sp8, sp18);
    return sp18[2];
}
