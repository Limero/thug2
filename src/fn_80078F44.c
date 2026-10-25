// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80078F44-0x80078FFC (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct Vt { char pad0[0x158]; s16 off; char pad2[2]; s32 (*fn)(void *); } Vt;
typedef struct Obj { char pad0[8]; Vt *vt; u8 *bytes; } Obj;
s32 fn_8007899C(s32, s32, s32, s32, s32, s32, s32);
bool fn_80078F44(Obj *arg0, Obj *arg1) {
    s32 a, b;
    u16 s6, s7, t6, t7;
    a = arg1->vt->fn((char *)arg1 + arg1->vt->off);
    s6 = 1 << arg1->bytes[6];
    s7 = 1 << arg1->bytes[7];
    b = arg0->vt->fn((char *)arg0 + arg0->vt->off);
    t6 = 1 << arg0->bytes[6];
    t7 = 1 << arg0->bytes[7];
    fn_8007899C(a, s6, s7, b, t6, t7, 0x20);
    return true;
}
