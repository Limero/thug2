// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DB364-0x800DB398 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    char _p0[0x3C];
    f32 unk0x3C; f32 unk0x40; f32 unk0x44; f32 unk0x48;
} TDB364;
extern f32 lbl_80299D80, lbl_80299D84, lbl_80299D88, lbl_80299D8C;
void fn_800DB364(void *arg0) {
    TDB364 *p = (TDB364 *)arg0;
    p->unk0x3C = lbl_80299D80;
    p->unk0x40 = lbl_80299D84;
    p->unk0x44 = lbl_80299D88;
    p->unk0x48 = lbl_80299D8C;
}
