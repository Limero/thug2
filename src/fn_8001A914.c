// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001A914-0x8001A994 (128B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 dvd_file_size(CStruct *);
s32 DVDFastOpen(s32, s32);
s32 dvd_file_fix_name(s32);
// dvd_file_open @ 0x8001A914
bool dvd_file_open(CStruct *arg0, s32 arg1) {
    s32 temp_r3;

    dvd_file_fix_name(arg1);
    temp_r3 = DVDConvertPathToEntrynum();
    if (temp_r3 == -1) {
        return false;
    }
    do {

    } while (DVDFastOpen(temp_r3, (char *)arg0 + 0x28) == 0);
    arg0->unk0x64 = 1;
    arg0->unk0x70 = 0;
    arg0->unk0x74 = 0;
    dvd_file_size(arg0);
    return true;
}
