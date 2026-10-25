// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80137B74-0x80137BA4 (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    s32 unk0x00; s32 unk0x04; s32 unk0x08; s32 unk0x0C; s32 unk0x10;
    s32 unk0x14; s32 unk0x18; s32 unk0x1C;
} T137B74;
extern char lbl_8029F1F0[];
void *fn_80137B74(void *arg0, s32 arg1) {
    T137B74 *p = (T137B74 *)arg0;
    p->unk0x04 = (s32)p;
    p->unk0x08 = 0;
    p->unk0x0C = (s32)p;
    p->unk0x10 = (s32)p;
    p->unk0x14 = (s32)lbl_8029F1F0;
    p->unk0x18 = arg1;
    p->unk0x1C = 0;
    return arg0;
}
