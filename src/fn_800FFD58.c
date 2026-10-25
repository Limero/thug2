// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FFD58-0x800FFDC8 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
bool fn_800FFD58(Unk_FFAD6788 *arg0, Unk_DB0E2BAB *arg1) {
    if ((*((f32 *)&arg1->unk0x0) > *((f32 *)&arg0->unk0xB0)) ||
        (*((f32 *)&arg0->unk0xA0) > *((f32 *)&arg1->unk0x10)) ||
        (*((f32 *)&arg1->unk0x8) > *((f32 *)&arg0->unk0xB8)) ||
        (*((f32 *)&arg0->unk0xA8) > *((f32 *)&arg1->unk0x18)) ||
        (*((f32 *)&arg1->unk0x4) > *((f32 *)&arg0->unk0xB4)) ||
        (*((f32 *)&arg0->unk0xA4) > *((f32 *)&arg1->unk0x14))) {
        return false;
    }
    return true;
}