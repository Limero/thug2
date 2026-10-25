// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80228840-0x802288E0 (160B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80305EC0;
extern void *NextItem(void *);
extern s32 fn_80198F7C(s32);
extern s32 fn_8022989C(CScript *);
extern s32 Game_GetGoalManager(void);
extern s32 fn_80185898(Unk_9994C3F5 *, s32);
extern void *fn_8021D358(void *, u16);
extern void *GetChecksum_3(Unk_6A70655D *, s32);
extern s32 fn_801813F0(CStruct *);

void fn_80228840(s32 arg0, s32 arg1) {
    void *mgr;
    s32 hz;

    mgr = NextItem((void *)arg0);
    hz = (fn_80198F7C(lbl_80305EC0) == QB_NETGOALATTACK);
    if ((hz != 0) && (fn_8022989C(mgr) == 0)) {
        fn_80185898(Game_GetGoalManager(), arg1);
    } else {
        fn_801813F0(*(s32 *)((char *)GetChecksum_3(*(s32 *)((char *)fn_8021D358(arg0, arg1) + 0x18), QB_SKATERSCORE) + 0x1C));
    }
}
