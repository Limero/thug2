// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801039D8-0x80103A50 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_80302BC8;
extern s32 fn_80103470(void *arg0, s32 arg1, s32 arg2, s32 arg3);

// field 0x8 is loaded with lhz in retail (u16), field 0x34 with lwz (s32).
typedef struct S_801039D8 {
    char pad0x0[0x8];
    u16 unk0x8;
    char pad0xA[0x2A];
    s32 unk0x34;
} S_801039D8;

s32 fn_801039D8(S_801039D8 *arg0, s32 arg1, s32 arg2) {
    s32 temp_r3;
    s32 temp_r4;

    temp_r4 = arg0->unk0x34;
    if (temp_r4 == 0) {
        return 0;
    }
    lbl_80302BC8 = 0;
    temp_r3 = fn_80103470(arg0, temp_r4, arg1, arg2);
    if (temp_r3 != 0) {
        temp_r3 = lbl_80302BC8 ^ (s32)arg0->unk0x8;
        return (temp_r3 == 0) ? 1 : 0;
    }
    return 0;
}
