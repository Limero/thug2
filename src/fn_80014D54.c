// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80014D54-0x80014E70 (284B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_80013410(s32, s32, s32, s32, s32);
void fn_80014D54(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    switch (arg1) {
    case 0:
        return;
    case 1:
        if ((arg3 >= 0) && (arg2 == 0)) {
            arg0->unk0x2C = arg4;
        }
        break;
    case 5:
        if ((arg3 >= 0) && (arg2 == 0)) {
            arg0->unk0x30 = arg3;
        }
        break;
    case 2:
    case 3:
        if ((arg2 == 0) && (arg0->unk0x88 != 0) && (arg3 > 0)) {
            memcpy(arg0->unk0x84, arg0->unk0x88, arg3);
        }
        /* fall through */
    case 4:
        if (arg3 >= 0) {
            if (arg2 == 0) {
                arg0->unk0x30 = arg0->unk0x30 + arg3;
            }
            if (arg0->unk0x88 != 0) {
                Mem_Free(arg0->unk0x88);
                arg0->unk0x84 = 0;
                arg0->unk0x88 = 0;
            }
        }
        break;
    }
    fn_80013410(arg0, arg1, arg2, arg3, arg4);
}
