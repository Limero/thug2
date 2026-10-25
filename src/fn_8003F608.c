// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003F608-0x8003F6F0 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80292408[];
typedef struct A_3F608 {
    char pad0x0[0x8];
    s32 unk0x8;
    char pad0xC[0xC];
    s32 unk0x18;
    char pad0x1C[0x3C];
    s32 unk0x58;
    char pad0x5C[0x8];
    s32 unk0x64;
    char pad0x68[0x8];
    s32 unk0x70;
    char pad0x74[0x8];
    s32 unk0x7C;
} A_3F608;
void fn_80041564(A_3F608 *, void *, s32);
void CObject_RemoveRefLink(s32, void *);
void fn_8009E0B0(A_3F608 *, s32);
void fn_8003F608(A_3F608 *arg0, s32 arg1) {
    struct { s32 f0; s32 f4; s32 f8; } sp8;
    struct { s32 f0; s32 f4; s32 f8; } *p;
    void *l7c;
    void *l70;
    void *l64;
    void *l58;

    p = &sp8;
    p->f4 = 0;
    p->f8 = 0;
    arg0->unk0x8 = (s32)lbl_80292408;
    sp8.f0 = 0;
    fn_80041564(arg0, p, 0);
    if (sp8.f0 != 0) {
        CObject_RemoveRefLink(sp8.f0, p);
        sp8.f0 = 0;
    }
    l7c = (char *)arg0 + 0x7C;
    arg0->unk0x18 = 0xDEADBEEF;
    if (arg0->unk0x7C != 0) {
        CObject_RemoveRefLink(arg0->unk0x7C, l7c);
        arg0->unk0x7C = 0;
    }
    l70 = (char *)arg0 + 0x70;
    if (arg0->unk0x70 != 0) {
        CObject_RemoveRefLink(arg0->unk0x70, l70);
        arg0->unk0x70 = 0;
    }
    l64 = (char *)arg0 + 0x64;
    if (arg0->unk0x64 != 0) {
        CObject_RemoveRefLink(arg0->unk0x64, l64);
        arg0->unk0x64 = 0;
    }
    l58 = (char *)arg0 + 0x58;
    if (arg0->unk0x58 != 0) {
        CObject_RemoveRefLink(arg0->unk0x58, l58);
        arg0->unk0x58 = 0;
    }
    fn_8009E0B0(arg0, arg1);
}
