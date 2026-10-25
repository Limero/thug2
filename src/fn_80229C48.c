// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80229C48-0x80229E18 (464B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F9C;
extern char lbl_802B02A4[];
s32 NextItem(s32 mgr);
s32 CStruct_new(s32 size);
s32 CStruct_ctor(s32 obj);
s32 fn_8022986C(CScript * arg0);
s32 fn_801258E8(void *buf, s32 flag);
void AddComponent(CStruct * obj, u32 hash, s32 type, void * val);
void AddInteger(CStruct * obj, u32 hash, s32 val);
void Script_RunScript(u32 hash, s32 obj, s32 a3, s32 a4, s32 a5);
s32 fn_8022989C(CScript * node);
s32 fn_80229BAC(CScript * node);
void CStruct_delete(CStruct * node, s32 flag);
s32 sprintf(s32 ctx, ...);

void fn_80229C48(void *arg0, s32 arg1) {
    s32 sp8[16];
    register void *self __asm__("r28");
    register s32 arg1v __asm__("r29");
    Unk_C7387A53 *node;
    register s32 mgr __asm__("r30");

    self = arg0;
    arg1v = arg1;
    mgr = lbl_80305F9C;
    /* varargs QB-parse call — want keeps its crclr cr1eq */
    sprintf((s32)sp8, (s32)lbl_802B02A4, arg1v + 1);
    node = NextItem(mgr);
    mgr = CStruct_ctor(CStruct_new(8));
    if (fn_8022986C(self) != 0) {
        AddComponent(mgr, QB_STRING0, 3, fn_801258E8(sp8, 0));
        AddInteger(mgr, QB_TEAM, arg1v);
        Script_RunScript(QB_CAPTURED_FLAG_YOU, mgr, 0, 0, 0);
    } else if (fn_8022989C(node) == 0 &&
               node->unk0x34 == arg1v) {
        AddComponent(mgr, QB_STRING0, 3, (s32)((char *)self + 0x3C));
        AddInteger(mgr, QB_TEAM, arg1v);
        Script_RunScript(QB_HIDE_CTF_ARROW, 0, 0, 0, 0);
        Script_RunScript(QB_CAPTURED_YOUR_FLAG, mgr, 0, 0, 0);
    } else {
        AddComponent(mgr, QB_STRING0, 3, (s32)((char *)self + 0x3C));
        AddComponent(mgr, QB_STRING1, 3, fn_801258E8(sp8, 0));
        AddInteger(mgr, QB_TEAM, arg1v);
        Script_RunScript(QB_CAPTURED_FLAG_OTHER, mgr, 0, 0, 0);
    }
    ((CScript *)self)->unk0x1D8 &= QB_UNKNOWN_0xFFFF87FF;
    if (mgr != 0) {
        CStruct_delete(mgr, 3);
    }
}
