// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018DE30-0x8018DFB4 (388B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_802A9638;
extern s32 lbl_802A963C;
s32 fn_801745B4(void *);
s32 GetChecksum_3(Unk_6A70655D *, s32);
s32 GetString(CStruct *, s32 *, s32 *, s32);
s32 GetChecksum_2(CStruct *, u32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_80182150(Unk_FFAD6788 *, s32, s32, s32, s32);
s32 Script_GenerateCRC(char *);
extern void strcat(char *, char *) __asm__("strcat");
bool fn_8018DE30(void *arg0) {
    s32 sp8[32];
    s32 sp8C;
    s32 *sp88;
    s32 temp_r31;
    register void *a0 __asm__("r30");
    register s32 t31 __asm__("r31");
    a0 = arg0;
    t31 = *(s32 *)((char *)GetChecksum_3((void *)fn_801745B4((void *)lbl_80305EAC), QB_SKATERSCORE) + 0x1C);
    GetString(((Unk_C7387A53 *)a0)->unk0x20, QB_TRICK_STRING, &sp88, 1);
    GetChecksum_2(((Unk_C7387A53 *)a0)->unk0x20, QB_TRICK_TYPE, &sp8C, 1);
    if (sp8C == QB_GRIND) {
        sp8[0] = lbl_802A9638;
        strcat((char *)sp8, (char *)sp88);
        if (fn_80182150(t31, Script_GenerateCRC(sp8), 0, 0, 1) != 0) {
            return true;
        } else {
            sp8[0] = lbl_802A963C;
            strcat((char *)sp8, (char *)sp88);
            if (fn_80182150(t31, Script_GenerateCRC(sp8), 0, 0, 1) != 0) {
                return true;
            }
        }
    }
    if (ContainsFlag(((Unk_C7387A53 *)a0)->unk0x20, QB_CREATE_A_TRICK) != 0) {
        if (fn_80182150(temp_r31, Script_GenerateCRC(sp88), 0, 0, 1) > 0) {
            return true;
        }
    } else {
        if (fn_80182150(temp_r31, Script_GenerateCRC(sp88), 0, 0, 1) > 0) {
            return true;
        }
    }
    return false;
}
