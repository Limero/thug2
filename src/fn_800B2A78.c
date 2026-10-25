// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B2A78-0x800B2B3C (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80298864[];
extern char lbl_80298868[];
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802988F8[];

// Base-class ctor: writes a vtable at +0x18 and 0 at +0x8, 1 arg, void.
void fn_8009F53C(void *obj);
// Resource alloc thunk (j fn_800770F8): 1 arg, result in r3.
s32 fn_800551B4(s32 kind);
// 0x94-byte sub-object init loop: 1 arg, void.
void fn_800B62A4(void *sub);

// FILE-LOCAL layout. The shared Unk_9D191493 class types 0x30/0x34/0x38,
// 0x200/0x204/0x208 and 0x234 as s32 (corpus-wide majority vote), so the
// f32 stores became fctiwz+stfd+stw round-trips through a phantom 8-byte
// stack temp — which is what bloated the frame to 0x40 and forced a saved
// r27 base. Retail's 0x30 frame + scratch r9 base needs the true f32 view.
typedef struct { char _p[0x94]; } Sub_94;

typedef struct {
    char pad0x0[0x4];
    s32 unk0x4;              /* QB_MODEL */
    char pad0x8[0x10];
    void *vtable0x18;
    char pad0x1C[0x14];
    f32 f0x30;
    f32 f0x34;
    f32 f0x38;
    f32 f0x3C;
    Sub_94 sub0x40;          /* 0x40 */
    Sub_94 sub0xD4;          /* 0xD4 */
    Sub_94 sub0x168;         /* 0x168 */
    char pad0x1FC[0x4];
    f32 f0x200;
    f32 f0x204;
    f32 f0x208;
    f32 f0x20C;
    s32 handle0x210;
    char pad0x214[0x1C];
    s32 unk0x230;
    f32 f0x234;
    char pad0x238[0x8];
    s32 unk0x240;
} S_800B2A78;

void *fn_800B2A78(S_800B2A78 *arg0) {
    volatile double _dummy1;   /* §4c issue-01: 2 dummies land the 0x30 frame */
    volatile double _dummy2;
    f32 temp_f30;
    f32 temp_f31;
    s32 temp_h;
    char *temp_r9;
    char *temp_r9_2;

    fn_8009F53C(arg0);
    arg0->vtable0x18 = (void *)lbl_802988F8;
    arg0->unk0x4 = QB_MODEL;
    temp_h = fn_800551B4(1);
    temp_f31 = *(f32 *)&lbl_80298864;
    temp_f30 = *(f32 *)&lbl_80298868;
    temp_r9 = (char *)arg0 + 0x30;
    arg0->handle0x210 = temp_h;
    *(f32 *)((char *)arg0 + 0x30) = temp_f31;
    *(f32 *)(temp_r9 + 4) = temp_f31;
    *(f32 *)(temp_r9 + 8) = temp_f31;
    *(f32 *)(temp_r9 + 0xC) = temp_f30;
    fn_800B62A4(arg0->sub0x40._p);
    fn_800B62A4(arg0->sub0xD4._p);
    fn_800B62A4(arg0->sub0x168._p);
    temp_r9_2 = (char *)arg0 + 0x200;
    arg0->unk0x230 = 0;
    arg0->unk0x240 = 0;
    *(f32 *)((char *)arg0 + 0x200) = temp_f31;
    *(f32 *)(temp_r9_2 + 0xC) = temp_f30;
    *(f32 *)(temp_r9_2 + 4) = temp_f31;
    *(f32 *)(temp_r9_2 + 8) = temp_f31;
    arg0->f0x234 = temp_f30;
    return arg0;
}
