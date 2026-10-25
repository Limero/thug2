// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80226068-0x802261D8 (368B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802B0130[];
s32 fn_8021D358(s32, u16);
s32 fn_80229B94(CScript *);
s32 fn_80229BAC(CScript *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddInteger(CStruct *, s32, s32);
s32 fn_801258E8(void *, s32);
void AddComponent(CStruct *, s32, s32, void *);
s32 Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
s32 fn_8022986C(CScript *);
s32 NextItem(s32);
s32 fn_8022989C(CScript *);
s32 fn_80229C38(CScript *);

bool fn_80226068(CScript *arg0) {
    char sp8[0x40];
    u8 *tbl;
    s32 mgr;
    s32 entry;
    s32 idx;
    s32 handle;
    Unk_C7387A53 *tmp;

    tbl = *(u8 **)arg0;
    mgr = arg0->unk0x18;
    entry = fn_8021D358(mgr, (u16)(s8)*tbl);
    if ((entry != 0) && (fn_80229B94(entry) != 0)) {
        idx = fn_80229BAC(entry);
        sprintf(sp8, (s32)lbl_802B0130, idx + 1);
        handle = CStruct_ctor(CStruct_new(8));
        AddInteger(handle, QB_TEAM, idx);
        AddComponent(handle, QB_STRING0, 3, fn_801258E8(sp8, 0));
        Script_RunScript(QB_FLAG_RETURNED, handle, 0, 0, 0);
        if (handle != 0) {
            CStruct_delete(handle, 3);
        }
        if (fn_8022986C(entry) != 0) {
            Script_RunScript(QB_DESTROY_CTF_PANEL_MESSAGE, 0, 0, 0, 0);
        }
        tmp = NextItem(mgr);
        if ((tmp != 0) && (fn_8022989C(tmp) == 0) && (tmp->unk0x34 == idx)) {
            Script_RunScript(QB_HIDE_CTF_ARROW, 0, 0, 0, 0);
        }
        fn_80229C38(entry);
    }
    return true;
}
