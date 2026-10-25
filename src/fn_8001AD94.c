// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001AD94-0x8001ADC8 (52B). Byte-identical.
#include "types.h"
// dvd_file_exist @ 0x8001AD94
s32 dvd_file_exist(void) {
    s32 var_r3;

    dvd_file_fix_name();
    
    return ( !(DVDConvertPathToEntrynum() == -1) );
}
