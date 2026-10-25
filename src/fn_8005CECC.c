// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005CECC-0x8005CF34 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
s32 fn_8005D380(s32, s32 *, s32 *);
s32 *fn_8005CECC(CStruct *arg0, s32 arg1) {
    s32 sp8;
    s32 *temp_r3;
    Unk_EFE13F4E *temp_r9;

    temp_r9 = *((Unk_EFE13F4E * *)&arg0->unk0x10);
    sp8 = arg1;
    temp_r3 = ((s32 *(*)(void *))temp_r9->unk0x4C)((char *)arg0 + temp_r9->unk0x48);
    if (temp_r3 != NULL) {
        *temp_r3 = sp8;
        fn_8005D380(arg0->unk0x8, &sp8, temp_r3);
    }
    return temp_r3;
}
