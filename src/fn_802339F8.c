// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802339F8-0x80233A50 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void* lbl_802FFE98;
extern char lbl_802B0914[];
s32 MemAvailable(Unk_C8FEE62D *);
s32 fn_8023FB5C(s32, s32);
s32 ScriptTopDownHeapTooLow(CStruct *pParams, CScript *pScript) {
    return MemAvailable(*(s32 *)(((Unk_4216A3DD *)lbl_802FFE98)->unk0x118 + 0x34)) <
           fn_8023FB5C((s32)lbl_802B0914, -1);
}
