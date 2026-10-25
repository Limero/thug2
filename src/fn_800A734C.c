// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A734C-0x800A738C (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    char _p0[0x408];
    s32 unk0x408; s32 unk0x40C; s32 unk0x410;
    f32 unk0x414;
    f32 unk0x418; f32 unk0x41C; f32 unk0x420; f32 unk0x424;
    f32 unk0x428; s32 unk0x42C;
} TA734C;
typedef struct {
    f32 unk0x00; f32 unk0x04; f32 unk0x08; f32 unk0x0C;
} TQA734C;
extern f32 lbl_80298150;
extern f32 lbl_80298154;
void fn_800A734C(void *arg0) {
    TA734C *p = (TA734C *)arg0;
    TQA734C *q = (TQA734C *)((char *)arg0 + 0x418);
    p->unk0x408 = 0;
    p->unk0x40C = 0;
    p->unk0x410 = 0;
    p->unk0x418 = lbl_80298150;
    q->unk0x0C = lbl_80298154;
    q->unk0x08 = lbl_80298150;
    q->unk0x04 = lbl_80298150;
    p->unk0x428 = lbl_80298150;
    p->unk0x42C = 0;
}
