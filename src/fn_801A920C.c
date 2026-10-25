// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A920C-0x801A9270 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_801A91D8(void);
void fn_801A9C1C(s32, s32, void *);
void fn_801A8E5C(s32, s32, s32, void *, s32);
typedef struct { u8 buf[0x80]; s32 flag; } Fr;
void fn_801A920C(s32 arg0, s32 arg1) {
    Fr fr;
    fr.flag = 0;
    fn_801A9C1C(arg0 + 8, (s32)fn_801A91D8, fr.buf);
    if (fr.flag != 0) {
        fn_801A8E5C(arg1, 0x3E8, fr.flag, fr.buf, 1);
    }
}
