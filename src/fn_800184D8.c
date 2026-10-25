// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800184D8-0x80018570 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void VIFlush(void);
void VISetNextFrameBuffer(void *);
void VIDSimpleAudioStartPlayback(s32, s32);
s32 GX_ReadDrawSync(void);
extern char lbl_80290D20[];
extern s32 lbl_8031E7C8;
extern s32 lbl_8031E7CC;
extern s32 lbl_8031E7D4;
extern u8 lbl_8031E7DA;
extern u16 lbl_8031E7DC;

// VIPreCallback @ 0x800184D8
void VIPreCallback(void) {
    s32 temp_r3;
    s32 temp_r11;
    s32 var_r0;
    s32 *p;

    temp_r3 = GX_ReadDrawSync();
    if (temp_r3 == (s32) (u16) (lbl_8031E7DC + 1)) {
        p = &lbl_8031E7D4;
        temp_r11 = lbl_8031E7C8;
        var_r0 = lbl_8031E7D4;
        lbl_8031E7DC = (u16) temp_r3;
        var_r0 = (var_r0 == temp_r11) ? lbl_8031E7CC : temp_r11;
        *p = var_r0;
        VISetNextFrameBuffer((void *) lbl_8031E7D4);
        VIFlush();
        VIDSimpleAudioStartPlayback((s32) lbl_80290D20, 1);
        lbl_8031E7DA = 1;
    }
}
