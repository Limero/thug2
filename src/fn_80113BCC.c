// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80113BCC-0x80113C5C (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetText(CStruct *, void *, void *, void *);
s32 ContainsFlag(CStruct *, void *);
void AddTrackToPlaylist(void *, s8, void *);

bool ScriptAddMusicTrack(CStruct *arg0) {
    s32 spC;
    s32 sp8;
    s32 f;
    s32 b;

    sp8 = 0;
    spC = 0;
    GetText(arg0, 0, &sp8, NULL);
    GetText(arg0, (void *)QB_TRACKTITLE, &spC, 0);
    f = ContainsFlag(arg0, QB_FLAG_PERM);
    b = (f == 0);
    if (sp8 != 0) {
        AddTrackToPlaylist((void *)sp8, (s8)b, (void *)spC);
    }
    return true;
}
