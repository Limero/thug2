// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80222930-0x80222A1C (236B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305F9C[];
s32 CStruct_new(s32 arg0);
s32 CStruct_ctor(s32 arg0);
s32 fn_80125A6C(void * arg0, s32 arg1);
void AddInteger(CStruct * arg0, s32 arg1, s32 arg2);
s32 Script_RunScript(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void CStruct_delete(CStruct * arg0, s32 arg1);

bool ScriptResetProSetFlags(CStruct *pParams, CScript *pScript) {
    s32 i;
    s32 one;
    register char *page __asm__("r27");
    Unk_7A675EAB *mgr;
    void *node;
    s32 flag;

    i = 0;
    mgr = *(s32 *)&lbl_80305F9C;
    page = (char *)0x802B0000;
    one = 1;
    for (;;) {
        node = (void *)CStruct_ctor(CStruct_new(8));
        AddInteger((s32)node, QB_FLAG, fn_80125A6C(page - 0x11C, 1) + i);
        flag = 1;
        if ((mgr->unk0x1BC & (one << (s8)i)) == 0) {
            flag = 0;
        }
        if (flag != 0) {
            Script_RunScript(QB_SETFLAG, node, 0, 0, 0);
        } else {
            Script_RunScript(QB_UNSETFLAG, node, 0, 0, 0);
        }
        if (node != NULL) {
            CStruct_delete((s32)node, 3);
        }
        i += 1;
        if (i > 6) {
            break;
        }
    }
    return true;
}
