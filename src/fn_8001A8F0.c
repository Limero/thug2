// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001A8F0-0x8001A914 (36B). Byte-identical.
#include "types.h"
#include "structs.h"
// dvd_file_size @ 0x8001A8F0
s32 dvd_file_size(CStruct *arg0) {
    if ((s32) arg0->unk0x68 == 0) {
        arg0->unk0x68 = 1;
        arg0->unk0x6C = (s32) arg0->unk0x5C;
    }
    return arg0->unk0x6C;
}
