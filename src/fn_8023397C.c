// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023397C-0x802339F8 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void* lbl_802FFE98;
extern char lbl_802B0914[];
s32 MemAvailable(Unk_C8FEE62D *);
s32 fn_8023FB5C(char *, s32);
s32 ScriptRequiresDefragment(CStruct *pParams, CScript *pScript) {
    s32 temp_r30;

    temp_r30 = MemAvailable(*(s32 *)((char *)(((Unk_9994C3F5 *)lbl_802FFE98)->unk0x118) + 0x34));
    if (temp_r30 < fn_8023FB5C(lbl_802B0914, -1)) {
        return 1;
    }
    return *(s32 *)((char *)(((Unk_9994C3F5 *)lbl_802FFE98)->unk0x11C) + 0x2C) > 200000;
}
