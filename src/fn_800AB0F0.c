// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AB0F0-0x800AB15C (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
s32 Mem_NewZero(s32);
s32 fn_8002439C(s32);
extern char lbl_80298448[];
void *fn_800AB0F0(Unk_C8FEE62D *arg0) {
    arg0->unk0x4 = arg0;
    arg0->unk0xC = arg0;
    arg0->unk0x10 = arg0;
    arg0->unk0x14 = (s32)lbl_80298448;
    arg0->unk0x2C = 0;
    arg0->unk0x8 = 0;
    arg0->unk0x38 = 0;
    arg0->unk0x20 = 0;
    arg0->unk0x1C = 0;
    arg0->unk0x18 = fn_8002439C(Mem_NewZero(0xD0));
    return arg0;
}
