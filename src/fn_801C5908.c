// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C5908-0x801C597C (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct S1C5908 {
    char pad0x0[0x4];
    s32 unk0x4;
    char pad0x8[0x10];
    s32 unk0x18;
    s32 unk0x1C;
    s8 unk0x20;
    char pad0x21[0xF];
    s32 unk0x30;
    s32 unk0x34;
    s8 unk0x38;
    s8 unk0x39;
    char pad0x3A[0x2];
    s32 unk0x3C;
    s32 unk0x40;
    s32 unk0x44;
} S1C5908;
extern char lbl_802ACCB8[];
void fn_8009F53C(void);
S1C5908 *fn_801C5908(S1C5908 *arg0) {
    fn_8009F53C();
    arg0->unk0x18 = (s32)lbl_802ACCB8;
    arg0->unk0x4 = QB_SKATERLOCALNETLOGIC;
    arg0->unk0x34 = 0;
    arg0->unk0x40 = 0;
    arg0->unk0x44 = 0;
    arg0->unk0x1C = 0;
    arg0->unk0x20 = -1;
    arg0->unk0x30 = 0;
    arg0->unk0x39 = -1;
    arg0->unk0x38 = 0;
    arg0->unk0x3C = 0;
    return arg0;
}
