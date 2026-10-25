// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C211C-0x801C218C (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "qb_constants.h"
#include "types.h"
extern f32 lbl_802AC904;
s32 fn_8010BB24(s32);
void fn_8010CC40(s32, void *, s32, s32, f32, f32, f32);
typedef struct { u8 _0[0xC]; s32 unkC; u8 _10[0x1C]; f32 unk2C; } A;
void fn_801C211C(A *arg0, void *arg1, f32 farg0) {
    volatile double _dummy;
    f32 t;

    t = farg0 * lbl_802AC904;
    fn_8010CC40(fn_8010BB24(QB_TABLE_CESS), arg1, arg0->unkC + 0x58, 1, t * arg0->unk2C, t, t);
}
