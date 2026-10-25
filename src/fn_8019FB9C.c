// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019FB9C-0x8019FC70 (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

extern s32 lbl_80301B48;

s32 GetChecksum_3(s32, s32);
s32 Script_GenerateCRC(s32);
s32 fn_800CBDE0(void);
s32 fn_800F2A48(s32, s32, s32);
void fn_800F28E4(s32, s32);
s32 fn_800F2EDC(s32, s32, s32, s32, s32, s32);
void fn_8019EFD4(s32, s32);

void fn_8019FB9C(s32 arg0, s32 arg1, s32 arg2) {
    s32 list;
    s32 node;
    s32 crc;

    if (GetChecksum_3(arg0, QB_ANIMBLENDER) != 0) {
        list = lbl_80301B48;
        crc = Script_GenerateCRC(arg1);
        if (arg2 != 0) {
            GetChecksum_3(arg0, QB_ANIMBLENDER);
            crc = arg2 + fn_800CBDE0();
        }
        node = fn_800F2A48(list, crc, 0);
        if (node != 0) {
            fn_800F28E4(list, node);
        }
        GetChecksum_3(arg0, QB_ANIMBLENDER);
        fn_800F2EDC(list, arg1, arg2, fn_800CBDE0(), 0, 0);
        fn_8019EFD4(arg0, arg2);
    }
}
