// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80018098-0x80018178 (224B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8031E748[];
extern char lbl_8031E788[];
extern bool lbl_8030011C;
extern s32 lbl_80300154;
extern s32 lbl_8031E7C8;
extern s32 lbl_8031E7CC;
extern s32 lbl_8031E7D0;
extern s32 lbl_8031E7D4;
extern s8 lbl_8031E7D8;
extern s8 lbl_8031E7D9;
extern s8 lbl_8031E7DA;
extern s16 lbl_8031E7DC;
extern s16 lbl_8031E7DE;
extern s32 lbl_803213CC;
extern s32 lbl_803213D0;
void VIWaitForRetrace(void);
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32);
void fn_8001CA24(void);
void GX_Flush(void);
void fn_800186CC(Unk_F6ED4C32 *);
void Display_flush(void) {
    s32 var_r31;
    s32 temp_r26;
    s32 temp_r4;
    s32 temp_r5;

    if (lbl_8030011C != 0) {
        var_r31 = 3;
        lbl_8030011C = 0;
        do {
            fn_8001CA24();
            GX_Flush();
            VIWaitForRetrace();
            var_r31 -= 1;
        } while (var_r31 != 0);
        temp_r26 = OSDisableInterrupts();
        temp_r4 = lbl_803213CC;
        temp_r5 = lbl_803213D0;
        lbl_80300154 = (s32)var_r31;
        *(s8 *)&lbl_8031E7D8 = (s8)var_r31;
        *(s8 *)&lbl_8031E7D9 = (s8)var_r31;
        *(s8 *)&lbl_8031E7DA = (s8)var_r31;
        *(s16 *)&lbl_8031E7DC = var_r31;
        *(s16 *)&lbl_8031E7DE = 1;
        lbl_8031E7C8 = temp_r4;
        lbl_8031E7CC = temp_r5;
        lbl_8031E7D4 = temp_r4;
        lbl_8031E7D0 = temp_r5;
        fn_800186CC((Unk_F6ED4C32 *)lbl_8031E748);
        fn_800186CC((Unk_F6ED4C32 *)lbl_8031E788);
        OSRestoreInterrupts(temp_r26);
    }
}
