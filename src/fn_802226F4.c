// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802226F4-0x8022273C (72B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305F9C;
s32 fn_8021B55C(void *arg0, s32 arg1);
void StartNetworkLobby(Unk_BF863306 * arg0, void * arg1);

bool ScriptReattemptJoinServer(CStruct *pParams, CScript *pScript) {
    s32 mgr;

    mgr = lbl_80305F9C;
    StartNetworkLobby(mgr, fn_8021B55C(mgr, 0));
    return true;
}
