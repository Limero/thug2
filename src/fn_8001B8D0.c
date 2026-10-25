// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001B8D0-0x8001B9C8 (248B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    s32 state;
    s32 mode;
} SettingsRecord;

extern SettingsRecord lbl_80300180;
void SetTevSwapModeTable(s32, s32, s32, s32, s32);
void fn_8001E248(s32, s32, s32, s32, s32, s32, s32);
void fn_8001EEE0(s32, s32, s32, s32, s32);
void GX_SetClipMode(s32);
void fn_8001DD28(void *, void (*)());
void fn_8001B8D0(void) {
    s32 z = 0;
    s32 t = 2;
    fn_8001DD28(0, 0);
    if (lbl_80300180.state == 0) {
        fn_8001EEE0(0, t, 1, z, z);
        GX_SetClipMode(0);
        fn_8001E248(4, z, 1, 1, z, z, t);
        fn_8001E248(5, z, 1, 1, z, z, t);
        SetTevSwapModeTable(0, 0, 1, 2, 3);
        SetTevSwapModeTable(1, 2, 2, 0, 1);
        SetTevSwapModeTable(2, 2, 2, 2, 2);
        SetTevSwapModeTable(3, 0, 0, 0, 0);
    }
}
