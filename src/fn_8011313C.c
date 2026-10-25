// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011313C-0x80113224 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetText(CStruct *, s32, char **, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
char *fn_8011E39C(s32 track, s32 sel);
s32 sprintf(char *buf, const char *fmt, ...);
void StopMusic(void);
void PlayTrack(s32 *name, s32 loop);
void fn_8011E5D4(s32 track);

bool ScriptPlayTrack(CStruct *arg0) {
    char buf[0x28];
    s32 *sp30;
    s32 sp34;
    s32 sp38;

    sp30 = 0;
    sp38 = 0;
    sp34 = 0x3E7;
    if (GetText(arg0, 0, &sp30, 0) == 0) {
        GetInteger(arg0, 0, &sp34, 0);
        sp30 = fn_8011E39C(sp34, 0);
        sprintf(buf, "MUSIC\\VAG\\SONGS\\%s", sp30);
        sp30 = buf;
    }
    GetInteger(arg0, QB_LOOP, &sp38, 0);
    if (sp30 != 0) {
        StopMusic();
        PlayTrack(sp30, sp38 != 0 ? 1 : 0);
        fn_8011E5D4(sp34);
    }
    return true;
}
