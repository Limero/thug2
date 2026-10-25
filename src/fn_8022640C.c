// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022640C-0x80226540 (308B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_802FFE98;
extern s32 lbl_80305F7C;
void fn_80137CB4(Unk_9F066EC1 *);
s32 fn_8000F2F8(Unk_9F352E7C *, s32);
s32 fn_801FC0E0();
void fn_801FA2B4(s32, void *);
void fn_801FA318(Unk_57FB3CEB *);
void fn_8000F320(Unk_F12C5E01 *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(CStruct *, s32, s32);
void fn_80009C00(CStruct *);
void fn_8022019C(CScript *, s32);
s32 Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
void fn_8013DE78(void *, Unk_C71E6DE1 *);

s32 fn_8022640C(Unk_C8FEE62D *arg0) {
    struct { u8 b; char pad1[0xB]; s32 w; u8 e; char pad2[0x10]; } sp;
    s32 t;
    Unk_FFAD6788 *obj;
    Unk_71062261 *m;
    s32 handle;

    obj = arg0->unk0x18;
    t = arg0->unk0x14 & 4;
    if (t != 0) {
        m = lbl_80305EAC;
        fn_80137CB4(&sp.b);
        if (m->unk0x388 == -QB_UNKNOWN_0x16D13502) {
            handle = CStruct_ctor(CStruct_new(8));
            AddChecksum(handle, 0, QB_SHOW_TIMEOUT);
            fn_80009C00(obj->unk0xF0);
            fn_8022019C((void *)obj, 2);
            Script_RunScript(QB_CANCEL_JOIN_SERVER, handle, 0, 0, 0);
            if (handle != 0) {
                CStruct_delete(handle, 3);
            }
            return 5;
        }
        sp.b = 0x8B;
        sp.w = 2;
        sp.e = 8;
        fn_8013DE78(arg0->unk0xC, &sp.b);
        return 4;
    } else {
        fn_8000F2F8((void *)lbl_802FFE98, ((Unk_9994C3F5 *)lbl_802FFE98)->unk0x11C);
        fn_801FA2B4(fn_801FC0E0(), (void *)*(s32 *)arg0);
        lbl_80305F7C = t;
        fn_801FA318(fn_801FC0E0());
        lbl_80305F7C = 1;
        fn_8000F320((void *)lbl_802FFE98);
    }
    return 1;
}
