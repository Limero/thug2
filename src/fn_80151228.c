// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80151228-0x80151320 (248B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_802FFE98;
extern s32 lbl_80301B40;
extern s32 lbl_80301B48;
extern char lbl_803A0010[];
bool ScriptNodeArrayManUnload(void *arg0, s32 arg1);
bool ScriptNodeArrayManLoad(void *arg0, s32 arg1);
void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
s32 Script_GenerateCRC(s32 arg0);
s32 fn_800F2A48(s32 arg0, s32 arg1, s32 arg2);
void fn_800F28E4(Unk_C7387A53 * arg0, CStruct * arg1);
void CStruct_ctor(void *arg0);
void AddString(CStruct * arg0, s32 arg1, void * arg2);
void fn_8016A67C(s32 arg0, s32 arg1);
void fn_800F1034(void);
s32 fn_800F1B30(Unk_A231C4C2 * arg0);
s32 fn_800F1E1C(void * arg0, s32 arg1);
void fn_800F1C34(Unk_A231C4C2 * arg0, s32 arg1, s32 arg2);
void fn_8000F320(Unk_F12C5E01 * arg0);
void CStruct_delete(CStruct * arg0, s32 arg1);
bool ScriptReLoadNodeArray(s32 arg0, s32 arg1) {
    volatile s32 sp8;
    char *buf;
    s32 temp_r28;
    s32 temp_r30;
    register s32 ret131 __asm__("r31");
    register s32 temp_r3_2 __asm__("r31");

    fn_8000F2F8((void *)lbl_802FFE98, ((Unk_C7387A53 *)lbl_802FFE98)->unk0x178);
    buf = lbl_803A0010;
    temp_r28 = lbl_80301B40;
    ret131 = Script_GenerateCRC(buf);
    temp_r30 = lbl_80301B48;
    fn_800F28E4(temp_r30, fn_800F2A48(temp_r30, ret131, 0));
    CStruct_ctor(&sp8);
    AddString(&sp8, 0, buf);
    ScriptNodeArrayManUnload(&sp8, arg1);
    ScriptNodeArrayManLoad(&sp8, arg1);
    fn_8016A67C(buf, 0);
    fn_800F1034();
    temp_r3_2 = fn_800F1B30(temp_r28);
    fn_800F1E1C(temp_r28, temp_r3_2);
    fn_800F1C34(temp_r28, temp_r3_2, 1);
    fn_8000F320((void *)lbl_802FFE98);
    CStruct_delete(&sp8, 2);
    return true;
}
