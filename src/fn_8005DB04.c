// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005DB04-0x8005DB30 (44B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    s32 unk0x00; s32 unk0x04; s32 unk0x08; s32 unk0x0C;
    s32 unk0x10; s32 unk0x14;
} T5DB04;
extern char lbl_80293940[];
void *fn_8005DB04(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    T5DB04 *p = (T5DB04 *)arg0;
    p->unk0x14 = (s32)lbl_80293940;
    p->unk0x00 = arg1;
    p->unk0x04 = arg2;
    p->unk0x08 = arg3;
    p->unk0x0C = arg4;
    p->unk0x10 = 0;
    return arg0;
}
