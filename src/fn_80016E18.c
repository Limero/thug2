// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80016E18-0x80016EAC (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// NOTE: this function must call the local 32-byte GX thunks (GX_SetTexCopySrc /
// GX_SetTexCopyDst / GX_CopyTex / GX_PixModeSync), NOT the GXSetTexCopySrc-style SDK
// names they wrap. Their `bl` targets are relocation-masked in the byte
// compare, so either spelling scores 100%, but calling the SDK names leaves
// the four thunks unreferenced and mwld dead-strips them — a 0x80 .text
// deficit that shifts every later section and trips patch_dol's init-r2
// assert. The thunks are declared `(void)` in src/, so the argument registers
// set up here simply pass through to the SDK.
#include "types.h"
#include "qb_constants.h"
typedef struct Ent16 {
    char pad0x0[0x2];
    u16 unk0x2;
    char pad0x4[0x2];
    u16 unk0x6;
    char pad0x8[0x2];
    u16 unk0xA;
    char pad0xC[0x2];
    u16 unk0xE;
} Ent16;
typedef struct Ent32 {
    char pad0x0[0x8];
    s32 unk0x8;
    s32 unk0xC;
} Ent32;
extern Ent16 lbl_802FFF80[];
void GX_SetTexCopySrc(u16, u16, u16, u16);
void GX_SetTexCopyDst(u16, u16, s32, u8);
void GX_CopyTex(void *, u8);
void GX_PixModeSync(void);
void fn_80016E18(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Ent16 *p;
    Ent32 *e;

    p = &lbl_802FFF80[arg1];
    e = (Ent32 *) p;
    GX_SetTexCopySrc(p->unk0x2, p->unk0x6, p->unk0xA, p->unk0xE);
    GX_SetTexCopyDst((u16) (e->unk0x8 >> arg4), (u16) (e->unk0xC >> arg4), arg2, arg4);
    GX_CopyTex((void *) arg0, 0);
    if (arg3 != 0)
        GX_PixModeSync();
}
