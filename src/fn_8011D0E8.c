// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011D0E8-0x8011D224 (316B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern bool lbl_802FFE58;
extern char lbl_8038C8C0[];
extern char lbl_8038E220[];
extern s32 lbl_80302C34;
extern s32 lbl_80302CA4;
extern f32 lbl_80302CA8;
extern s32 lbl_80302CD0;
s32 fn_8011BC38();
s32 Script_GetInteger(s32, s32);
f32 fn_8011A8FC(s32);
void fn_8011D810(s32);
s32 _PlayMusicTrack(s32, f32);
s32 Script_GenerateCRC(char *);
void SetTrackForbiddenStatus(s32, s32, s32);
void strcpy(char *, char *);
// PlayTrack @ 0x8011D0E8
void PlayTrack(void *arg0, s32 arg1) {
    volatile double _dummy;
    f32 var_f31;
    s32 temp_r27;
    s32 temp_r3;
    s32 i;
    Unk_B8BF4382 *tbl;
    char *entry;

    if ((fn_8011BC38() == 0) && (lbl_80302CD0 == 0)) {
        strcpy((char *)lbl_8038E220, (char *)arg0);
        temp_r27 = lbl_80302CA4;
        temp_r3 = Script_GetInteger(QB_FORCEAMBIENTSFXTOMUSICVOLUME, 0);
        if ((temp_r27 == 0) || (temp_r3 != 0)) {
            var_f31 = lbl_80302CA8;
        } else {
            var_f31 = fn_8011A8FC(lbl_80302C34);
        }
        fn_8011D810(arg1);
        if ((_PlayMusicTrack((s32)lbl_8038E220, var_f31) == 0) && (lbl_802FFE58 == 0)) {
            tbl = (char *)lbl_8038C8C0 + temp_r27 * 0xCB0;
            i = 0;
            if (i < tbl->unk0xC80) {
                entry = tbl;
                do {
                    if (Script_GenerateCRC(arg0) == Script_GenerateCRC(entry)) {
                        SetTrackForbiddenStatus(i, 1, temp_r27);
                        return;
                    }
                    i++;
                    entry += 0x28;
                } while (i < tbl->unk0xC80);
            }
        }
    }
}
