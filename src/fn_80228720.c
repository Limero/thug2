// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80228720-0x80228840 (288B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80305EC0;
extern char lbl_802A83F8[];
extern s32 Game_GetGoalManager(void);
extern s32 fn_80185940(Unk_9994C3F5 *, s32);
extern void *NextItem(void *);
extern s32 fn_80198F7C(s32);
extern void *fn_8021D454(s32, CStruct *, s32);
extern void *fn_8021D4E8(s32, CStruct *, s32);
extern s32 fn_80229B5C(CScript *);
extern s32 fn_8022989C(CScript *);
extern void *GetChecksum_3(Unk_6A70655D *, s32);
extern s32 fn_801813F0(CStruct *);

s32 fn_80228720(s32 arg0, s32 arg1) {
    s32 sp8[3];
    register s32 *it __asm__("r30");
    register s32 *rp __asm__("r25");
    register void *mgr __asm__("r26");
    register s32 sum __asm__("r27");
    s32 lblv;
    CScript *cur;
    s32 hz;
    s32 rv;

    it = &sp8[0];
    it[1] = 0;
    lblv = (s32)lbl_802A83F8;
    it[2] = lblv;
    rp = it;
    mgr = NextItem((void *)arg0);
    sum = 0;
    hz = (fn_80198F7C(lbl_80305EC0) == QB_NETGOALATTACK);
    cur = fn_8021D454(arg0, it, 0);
    while (cur != NULL) {
        if ((fn_80229B5C(cur) != 0) && (cur->unk0x34 == arg1)) {
            if ((hz != 0) && (fn_8022989C(mgr) == 0)) {
                rv = fn_80185940(Game_GetGoalManager(), arg1);
                rp[2] = lblv;
                return rv;
            }
            sum += fn_801813F0(*(s32 *)((char *)GetChecksum_3(cur->unk0x18, QB_SKATERSCORE) + 0x1C));
        }
        cur = fn_8021D4E8(arg0, &sp8[0], 0);
    }
    rp[2] = (s32)lbl_802A83F8;
    return sum;
}
