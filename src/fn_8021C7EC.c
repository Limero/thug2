// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021C7EC-0x8021C9B0 (452B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AFE24[];

s32 fn_8021C9B8(CScript *);
void *NextItem(s32);
void fn_8021CB74(CScript *, CScript *);
s32 fn_8022A848(CScript *);
void fn_801AAC90(Unk_EE1FD121 *);
s32 fn_80229B94(CScript *);
s32 fn_80229BAC(CScript *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddInteger(CStruct *, s32, s32);
s32 fn_801258E8(void *, s32);
void AddComponent(CStruct *, s32, s32, void *);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
s32 fn_8022989C(CScript *);
void fn_80229C38(CScript *);

void fn_8021C7EC(Unk_031F7D04 *arg0, Unk_C8FEE62D *arg1) {
    char sp8[0x40];
    CScript *e;
    Unk_C7387A53 *e2;
    s32 res;
    s32 temp_r28;
    s32 temp_r31;

    if (arg1 == (void *)arg0->unk0x1F8) {
        res = fn_8021C9B8((s32 *)arg0);
        arg0->unk0x1F8 = res;
        if (arg1 == (void *)res) {
            arg0->unk0x1F8 = 0;
        }
        e = NextItem((s32)arg0);
        if (e != NULL && e->unk0x18 != 0) {
            fn_8021CB74(arg0, e);
        } else {
            fn_8021CB74(arg0, (void *)arg0->unk0x1F8);
        }
    }
    if (fn_8022A848(arg1) != 0 && arg0->unk0x78 != 0) {
        fn_801AAC90(arg0->unk0x78);
    }
    if (fn_80229B94(arg1) != 0) {
        temp_r28 = fn_80229BAC(arg1);
        sprintf(sp8, (s32)lbl_802AFE24, temp_r28 + 1);
        AddInteger((temp_r31 = CStruct_ctor(CStruct_new(8))), QB_TEAM, temp_r28);
        AddComponent(temp_r31, QB_STRING0, 3, fn_801258E8(sp8, 0));
        Script_RunScript(QB_FLAG_RETURNED, temp_r31, 0, 0, 0);
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
        e2 = NextItem((s32)arg0);
        if (e2 != NULL && fn_8022989C(e2) == 0 &&
            e2->unk0x34 == temp_r28) {
            Script_RunScript(QB_HIDE_CTF_ARROW, 0, 0, 0, 0);
        }
        fn_80229C38(arg1);
    }
    if (arg1 != NULL) {
        void *vt = *((void * *)&arg1->unk0x14);
        ((s32 (*)(void *, s32))((Unk_F5317C5D *)vt)->unk0xC)(
            (char *)arg1 + ((Unk_F5317C5D *)vt)->unk0x8, 3);
    }
}
