// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80141B08-0x80141BC8 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Pause timer setup: once-per-frame guard (0x354/0xC8), sets flags,
// schedules two pause callbacks and fires QB_PAUSE_RUN_TIMER.
// Suggested rename: PauseTimer
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_8029F794;
extern s32 lbl_80302C34;
static void fn_801812B8(s32 arg0, s32 arg1, f32 arg2);
static void fn_801812DC(s32 arg0, s32 arg1, f32 arg2);
static void Script_RunScript(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
static void fn_8000C79C(void *arg0);
static void fn_80119AF8(s32 arg0);
void fn_80141B08(Unk_4701C175 *arg0) {
    Unk_264DC741 *temp_r3;

    if ((arg0->unk0x354 == 0) && (arg0->unk0xC8 != 0)) {
        arg0->unk0x354 = 1;
        arg0->unk0x114 |= 1;
        fn_801812B8(*(s32 *)(arg0->unk0x2A4 + (s32)0x1C), 0, lbl_8029F794);
        fn_801812DC(*(s32 *)(arg0->unk0x2A4 + (s32)0x1C), 0, lbl_8029F794);
        Script_RunScript(QB_PAUSE_RUN_TIMER, 0, 0, 0, 0);
        temp_r3 = arg0->unk0x290;
        if (temp_r3 != NULL) {
            fn_8000C79C((void *)*(s32 *)(temp_r3->unk0x51C + (s32)0x20));
        }
        fn_80119AF8(lbl_80302C34);
    }
}
