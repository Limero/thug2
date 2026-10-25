// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80173D30-0x80174090 (864B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EA4;
extern s32 lbl_80300460;
extern s32 lbl_80305E98;
extern s32 lbl_80301A38;
extern s32 lbl_80300E00;
extern void fn_8016D52C(void * arg0);
extern void fn_800DAFB4(void);
extern void fn_80054420(void);
extern s32 fn_801A269C(Unk_31DE137E * arg0);
extern s32 fn_801A297C(Unk_C7387A53 * arg0);
extern void fn_8005DDF4(s32 arg0, CStruct * arg1);
extern void Script_RunScript(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void fn_80176E68(Unk_BC2275DF * arg0);
extern void fn_800A3778(s32 arg0, s32 arg1, s32 arg2);
extern s32 fn_801745B4(void *arg0);
extern s32 fn_8005DE90(s32 arg0);
extern s32 fn_8005DDBC(s32 arg0);
extern s32 fn_80024660(void * arg0);
extern void fn_800B120C(s32 arg0, CScript * arg1, s32 arg2, s32 arg3);
extern s32 fn_800A398C(s32 arg0, s32 arg1);
extern s32 ScriptIsObserving(s32 arg0, s32 arg1);
extern void fn_80173CFC(void);
void fn_80173D30(Unk_F7B7E582 *arg0) {
    s32 temp_r0;
    Unk_9994C3F5 *temp_r11;
    Unk_EFE13F4E *temp_r9;
    Unk_9994C3F5 *temp_r3;
        Unk_EFE13F4E *temp_r9_2;
    register s32 tmp __asm__("r30");
    s32 flag;

    fn_8016D52C(lbl_80305EA4);
    fn_800DAFB4();
    if ((lbl_80300460 == 0) && (lbl_80305E98 == 0)) {
        fn_80054420();
        flag = 1;
        if (fn_801A269C(arg0->unk0x378) == 0) {
            flag = 0;
        }
        if (flag != 0) {
            if (fn_801A297C(arg0->unk0x378) != 0) {
                fn_8005DDF4(0, fn_801A297C(arg0->unk0x378));
            }
            if (arg0->unk0x60 != 0) {
                Script_RunScript(QB_HIDE_LOADING_SCREEN, 0, 0, 0, 0);
            }
            temp_r11 = arg0->unk0x378;
            temp_r9 = temp_r11->unk0x8;
            ((void (*)(void *))temp_r9->unk0x4C)(
                (char *)temp_r11 + temp_r9->unk0x48);
            arg0->unk0x60 = 1;
        } else if (arg0->unk0x60 != 0) {
            Script_RunScript(QB_RESTORE_SKATER_CAMERA, 0, 0, 0, 0);
            arg0->unk0x60 = 0;
        }
        temp_r0 = fn_801A269C(arg0->unk0x37C) != 0;
        if (temp_r0 != 0) {
            temp_r3 = arg0->unk0x37C;
            temp_r9_2 = temp_r3->unk0x8;
            ((void (*)(void *))temp_r9_2->unk0x4C)(
                (char *)temp_r3 + temp_r9_2->unk0x48);
        }
    }
    fn_80176E68(arg0);
    Script_RunScript(QB_GAME_UPDATE, 0, 0, 0, 0);
    if (lbl_80300460 != 0) {
        fn_800A3778(lbl_80301A38, (s32)fn_80173CFC, 0);
    }
    if (fn_801745B4(arg0) != 0) {
        switch (lbl_80300E00) {
        case 1:
            if (fn_8005DE90(0) != 0) {
                tmp = fn_801745B4(arg0);
                fn_800B120C(1, tmp, fn_80024660(fn_8005DE90(0)), 1);
                tmp = fn_801745B4(arg0);
                fn_800B120C(1, tmp, fn_801745B4(arg0) + 0x58, 2);
            }
            break;
        case 2:
            if (fn_8005DDBC(0) != 0) {
                tmp = fn_800A398C(lbl_80301A38, 0);
                fn_800B120C(1, tmp, fn_80024660(fn_8005DDBC(0)), 1);
                fn_800B120C(1, tmp, tmp + 0x58, 2);
            }
            if ((fn_8005DDBC(1) != 0) && (fn_800A398C(lbl_80301A38, 1) != 0)) {
                tmp = fn_800A398C(lbl_80301A38, 1);
                fn_800B120C(2, tmp, fn_80024660(fn_8005DDBC(1)), 1);
                fn_800B120C(2, tmp, tmp + 0x58, 2);
            }
            break;
        }
    } else if ((ScriptIsObserving(0, 0) != 0) && (lbl_80300E00 == 1) &&
               (fn_8005DE90(0) != 0)) {
        fn_800B120C(1, 0, fn_80024660(fn_8005DE90(0)), 1);
    }
    if (arg0->unk0x6C != 0) {
        arg0->unk0x6C = 0;
    }
}
