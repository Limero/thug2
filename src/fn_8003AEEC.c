// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003AEEC-0x8003AFC8 (220B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void Script_RunScript(void *, void *, void *, void *, void *);
void fn_8000F320(Unk_9994C3F5 *);
void fn_8000F2F8(Unk_9994C3F5 *, s32);
void *fn_8003A80C(CStruct *, Unk_31DE137E *);
void *fn_8003A754(CStruct *);
s32 fn_8003A8D0(CStruct *);
void *fn_800099AC(s32, s32, s32);
extern Unk_9994C3F5 *lbl_802FFE98;
extern void *lbl_803003E8;
extern void *lbl_803003EC;
extern CStruct *lbl_803003F0;
void fn_8003AEEC(void *arg0, Unk_31DE137E *arg1, void *arg2, void *arg3, void *arg4) {
    Unk_9994C3F5 *mgr;
    Unk_9994C3F5 *mgr2;
    CStruct *obj;
    CStruct *newobj;
    CStruct *tbl;

    mgr = lbl_802FFE98;
    lbl_803003E8 = arg2;
    lbl_803003EC = arg3;
    newobj = fn_8003A754(fn_800099AC(0x68, mgr->unk0x118, 1));
    lbl_803003F0 = newobj;
    fn_8003A8D0(newobj);
    mgr2 = lbl_802FFE98;
    fn_8000F2F8(mgr2, mgr2->unk0x118);
    fn_8003A80C(lbl_803003F0, arg1);
    fn_8000F320(lbl_802FFE98);
    Script_RunScript(arg4, 0, arg0, 0, 0);
    obj = lbl_803003F0;
    lbl_803003E8 = 0;
    lbl_803003EC = 0;
    if (obj != NULL) {
        tbl = (CStruct *)obj->unk0x8;
        ((s32 (*)(void *, s32))tbl->unk0xC)((char *)obj + *((s16 *)&tbl->unk0x8), 3);
    }
    lbl_803003F0 = 0;
}
