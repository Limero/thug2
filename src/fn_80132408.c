// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80132408-0x80132458 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029E778;  /* .rodata2:0x8029E778 (lis -0x7fd6 @l -0x1888); the
                            * masked sweep cannot see a wrong label address, so
                            * decode lis+addi by hand before promoting. */

typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
} Loc32408;

s32 fn_80132408(Loc32408 *arg0) {
    s32 t = arg0->unk0x0 & 0x7F0000;

    if (t == 0x10000) {
        return arg0->unk0x8;
    }
    if (t == 0x20000) {
        return *(f32 *)((char *)arg0 + 8) != lbl_8029E778;
    }
    return 0;
}
