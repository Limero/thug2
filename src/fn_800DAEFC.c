// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DAEFC-0x800DAF84 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
typedef struct Unk_800DAEFC {
    char pad0x0[0x4];
    s32 unk0x4;
    char pad0x8[0x10];
    char *unk0x18;
    s32 unk0x1C;
    f32 unk0x20;
    f32 unk0x24;
    char pad0x28[4];
    s32 unk0x2C;
    char pad0x30[0x1C];
    s32 unk0x4C;
} Unk_800DAEFC;
extern f32 lbl_80299D64;
extern char lbl_80299DA0[];
void fn_8009F53C(Unk_800DAEFC *);
f32 fn_8012570C(s32, s32);
void *fn_800DAEFC(Unk_800DAEFC *arg0) {
    fn_8009F53C(arg0);
    arg0->unk0x18 = lbl_80299DA0;
    arg0->unk0x4 = QB_SUSPEND;
    arg0->unk0x20 = fn_8012570C(QB_DEFAULTMOVINGOBJECTSUSPENDDISTANCE, 0) * lbl_80299D64;
    arg0->unk0x1C = 1;
    arg0->unk0x2C = 0xA;
    arg0->unk0x4C = 3;
    arg0->unk0x24 = arg0->unk0x20 * arg0->unk0x20;
    return arg0;
}
