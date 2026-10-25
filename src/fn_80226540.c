// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80226540-0x802266A4 (356B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
void fn_80137CB4(Unk_9F066EC1 *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(CStruct *, s32, s32);
void fn_80009C00(CStruct *);
void fn_8022019C(CScript *, s32);
s32 Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
void fn_8013DE78(void *, Unk_C71E6DE1 *);
s32 fn_801F672C();
void fn_801F5218(Unk_F0C166E4 *, s32, void *);
register s32 r31_guard __asm__("r31");

s32 fn_80226540(Unk_C8FEE62D *arg0) {
    struct { u8 b; char pad1[0xB]; s32 w; u8 e; char pad2[0x10]; } sp;
    Unk_FFAD6788 *obj;
    Unk_71062261 *mgr;
    s32 handle;
    void *pp;

    fn_80137CB4(&sp.b);
    obj = arg0->unk0x18;
    mgr = lbl_80305EAC;
    if (arg0->unk0x14 & 4) {
        if (mgr->unk0x388 == -QB_UNKNOWN_0x16D13502) {
            fn_80009C00(obj->unk0xF0);
            fn_8022019C((void *)obj, 2);
            handle = CStruct_ctor(CStruct_new(8));
            AddChecksum(handle, 0, QB_SHOW_TIMEOUT);
            Script_RunScript(QB_CANCEL_JOIN_SERVER, handle, 0, 0, 0);
            if (handle != 0) {
                CStruct_delete(handle, 3);
            }
            return 5;
        }
        sp.b = 0x8A;
        sp.w = 2;
        sp.e = 8;
        fn_8013DE78(arg0->unk0xC, &sp.b);
        return 4;
    } else {
        void *p = (void *)*(s32 *)arg0;
        s32 a = *(s32 *)p;
        void *b = (void *)((char *)p + 4);
        fn_801F5218(fn_801F672C(), a, b);
        handle = CStruct_ctor(CStruct_new(8));
        AddChecksum(handle, 0, QB_DONOTCREATEGOALPEDS);
        Script_RunScript(QB_INITIALISECREATEDGOALS, handle, 0, 0, 0);
        if (handle != 0) {
            CStruct_delete(handle, 3);
        }
    }
    return 1;
}
