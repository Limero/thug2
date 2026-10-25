// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80078864-0x800788FC (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

void fn_80078274(s32, s32, s32, u16, u16);

typedef struct {
    char pad0x0[0x6];
    u8 unk0x6;
    u8 unk0x7;
    u8 unk0x8;
    u8 unk0x9;
    u16 unk0xA;
    char pad0xC[0x4];
    s32 unk0x10;
    s32 unk0x14;
    s32 unk0x18;
} Snd;

typedef struct {
    char pad0x0[0x58];
    s16 unk0x58;
    char pad0x5A[0x2];
    s32 (*unk0x5C)(void *);
} Vt;

typedef struct {
    char pad0x0[0x8];
    Vt *unk0x8;
    Snd *unk0xC;
} Obj;

void fn_80078864(Obj *arg0) {
    Snd *s;
    Vt *v;

    s = arg0->unk0xC;
    fn_80078274(s->unk0x18, 0, s->unk0x10, (u16) (1 << s->unk0x6), (u16) (1 << s->unk0x7));
    arg0->unk0xC->unk0xA |= 0x201;
    arg0->unk0xC->unk0x14 = 0;
    arg0->unk0xC->unk0x9 = 6;
    v = arg0->unk0x8;
    v->unk0x5C((char *) arg0 + v->unk0x58);
}
