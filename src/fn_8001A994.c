// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001A994-0x8001A9D4 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

s32 dvd_file_size(void *arg0);

// dvd_file_eof @ 0x8001A994
s32 dvd_file_eof(void *arg0) {
    void *obj = arg0;
    return *(s32 *)((char *)obj + 0x74) >= dvd_file_size(obj);
}
