// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80112A94-0x80112C0C (376B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_8029D0C4;
extern f32 lbl_8029D0C8;
extern f32 lbl_8029D0CC;
extern void* lbl_80302C34;

s32 GetText(CStruct *, s32, char **, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 ContainsFlag(CStruct *, s32);
void fn_8011A2AC(s32 *, char *, s32, s32, s32, f32, f32, f32);

bool ScriptLoadSound(CStruct *arg0) {
    char *sp8;
    f32 spC;
    f32 sp10;
    f32 sp14;
    s32 sp18;
    s32 flags;
    s32 mode;

    if (GetText(arg0, 0, &sp8, 1) != 0) {
        sp14 = lbl_8029D0C4;
        spC = lbl_8029D0C4;
        flags = 0;
        sp10 = lbl_8029D0C8;
        sp18 = 0;
        GetFloat(arg0, (s32)0xD8604126, &spC, 0);
        mode = 1;
        if (GetFloat(arg0, (s32)0xFF2020EC, &sp10, 0) != 0) {
            sp10 = sp10 * lbl_8029D0CC;
        }
        GetFloat(arg0, (s32)0xF6A36814, &sp14, 0);
        if (ContainsFlag(arg0, QB_FLAG_PERM) != 0) {
            mode = 0;
        } else if (GetInteger(arg0, QB_BANK, &sp18, 0) != 0) {
            mode = 2;
        }
        if (ContainsFlag(arg0, (s32)0xCF15C120) != 0) {
            flags |= 1;
        } else if (ContainsFlag(arg0, (s32)0x8B87176F) != 0) {
            flags |= 2;
        }
        fn_8011A2AC(lbl_80302C34, sp8, flags, mode, sp18, sp10, spC, sp14);
    }
    return true;
}
