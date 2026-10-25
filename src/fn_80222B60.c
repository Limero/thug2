// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80222B60-0x80222C2C (204B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F9C;
s32 NextItem(void *arg0);
s32 fn_802298B4(CScript * arg0);
void fn_8021CB74(CScript * arg0, CScript * arg1);

bool ScriptExitSurveyorMode(CStruct *pParams, CScript *pScript) {
    Unk_FFAD6788 *mgr;
    CScript *e;
    register void *obj __asm__("r11");
    Unk_4E705049 *vt;

    mgr = (s32 *)lbl_80305F9C;
    if ((e = (void *)NextItem((void *)mgr)) == NULL) {
        return false;
    }
    if (fn_802298B4((s32)e) == 0) {
        return true;
    }
    fn_8021CB74((void *)mgr, e);
    obj = *((void * *)&e->unk0x1F4);
    if (obj != NULL) {
        vt = *((void * *)&((CScript *)obj)->unk0x18);
        ((s32 (*)(void *, s32)) *((void * *)&vt->unk0x1C))(
            (char *)obj + vt->unk0x18, 3);
    }
    e->unk0x1F4 = 0;
    obj = *((void * *)&mgr->unk0x108);
    if (obj != NULL) {
        vt = *((void * *)&((CScript *)obj)->unk0x18);
        ((s32 (*)(void *, s32)) *((void * *)&vt->unk0x1C))(
            (char *)obj + vt->unk0x18, 3);
    }
    mgr->unk0x108 = 0;
    e->unk0x1D8 &= QB_UNKNOWN_0xFFFEFFFF;
    return true;
}
