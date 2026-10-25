// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80123864-0x80123938 (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 fn_802499BC(Unk_31DE137E *, s32, s32, s32, s32, s32);
s32 fn_80123690(s32, void *, s32, s32);

typedef struct {
    s32 unk0x0;
    u16 unk0x4;
    char pad0x6[0x2];
} Chunk;

typedef struct {
    char pad0x0[0xA0];
    s32 unk0xA0;
    char pad0xA4[0x2F4];
    s32 unk0x398;
} Mgr;

extern Mgr lbl_8039BA58;
extern s32 lbl_8039BE80;
extern s32 (*lbl_8039BE8C)(s32);

bool fn_80123864(Chunk *arg0, s32 arg1) {
    s32 temp_r10;
    s32 var_r3;
    s32 temp_r4;
    s32 sp8;
    s32 *sp8p;

    temp_r10 = lbl_8039BA58.unk0xA0;
    if (temp_r10 != QB_STREAM_STATE_NONE) {
        if (temp_r10 == QB_FOURCC_VAUD) {
            temp_r4 = arg0->unk0x4;
            var_r3 = fn_802499BC((Unk_31DE137E *) lbl_8039BA58.unk0x398, (s32) ((char *) arg0 + temp_r4),
                                 arg1 - temp_r4, 3, fn_80123690, 0);
        } else {
            sp8p = &sp8;
            sp8 = (s32) ((char *) arg0 + 4);
            var_r3 = lbl_8039BE8C(arg0->unk0x0);
            var_r3 = fn_80123690(1, sp8p, var_r3, 0);
        }
        if (var_r3 == 0) {
            return false;
        }
        lbl_8039BE80 = 1;
    }
    return true;
}
