// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A24C8-0x800A25A4 (220B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Ident: script comparison command on a byte field. Resolves the skater
// object's byte at (arg1+0x128) via fn_800A2430 (obj+0x120) + fn_800A21C0
// (read +0x8), then applies the operator in arg0+4 against the literal byte
// at arg0+8: 2=`<`, 4=`>`, 8=`==`, 10/12=`>=` (polarity distinguishes them:
// want emits subfc r3,r9,r3 for case 10 but subfc r3,r3,r9 for case 12, so
// the two >= cases must stay distinct expressions in source or the compiler
// merges the bodies). The 0+M2C_CARRY m2c rendering was a lost comparison.
#include "types.h"
#include "structs.h"
extern void *fn_800A2430(void *);
u8 fn_800A21C0(Unk_6A78CE27 *);

s32 fn_800A24C8(Unk_A46CE310 *arg0, void *arg1) {
    u32 t0;
    u32 r9;

    r9 = fn_800A21C0(fn_800A2430(arg1));
    t0 = *((u32 *)&arg0->unk0x4);
    switch (t0) {
    case 2:
        return r9 < (u8) arg0->unk0x8;
    case 10:
        return (u8) arg0->unk0x8 >= r9;
    case 8:
        return (r9 ^ (u8) arg0->unk0x8) == 0;
    case 4:
        return (u8) arg0->unk0x8 < r9;
    case 12:
        return r9 >= (u8) arg0->unk0x8;
    default:
        return 0;
    }
}