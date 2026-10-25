// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80070CAC-0x80070D20 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    u32 f29 : 3;
    u32 f24 : 5;
    u32 f22 : 2;
    u32 lo : 22;
} Flags_15E4;
extern Flags_15E4 lbl_803015E4;
void fn_8009C778(void);
void fn_80070CAC(s32 arg0, s32 arg1) {
    switch (arg0) {
    case 1:
        lbl_803015E4.f29 = arg1;
        break;
    case 2:
        lbl_803015E4.f24 = arg1;
        break;
    case 4:
        lbl_803015E4.f22 = arg1;
        break;
    }
    fn_8009C778();
}
