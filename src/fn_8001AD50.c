// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001AD50-0x8001AD94 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
// dvd_file_close @ 0x8001AD50
s32 dvd_file_close(CStruct *);
s32 DVDClose(void *);
bool dvd_file_close(CStruct *arg0) {
    DVDClose((char *)arg0 + 0x28);
    arg0->unk0x64 = 0;
    arg0->unk0x68 = 0;
    arg0->unk0x70 = 0;
    return false;
}
