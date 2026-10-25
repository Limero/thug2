// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A8148-0x801A8204 (188B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AB954[];
register s32 g31 __asm__("r31");
s32 fn_800546A0(s32);
s32 fn_80125A08(s32, s32);
s32 fn_8012954C(CStruct *, s32);
s32 fn_801293FC(CStruct *, s32);
bool fn_801A8148(CScript *arg0, s32 t) {
    struct {
        s32 sp8;
        s32 h1;
        s32 color;
        s32 h2;
    } fr;
    u8 *pc;
    CStruct *mgr;
    Unk_C8FEE62D *obj;
    Unk_C6B642AC *vt;
    s32 cw;

    pc = (u8 *)&fr.color;
    mgr = fn_800546A0(arg0->unk0x18);
    t = fn_8012954C(fn_80125A08((s32)lbl_802AB954, 0), t);
    *(u8 *)&fr.color = fn_801293FC(t, 0);
    *((u8 *)&fr.color + 1) = fn_801293FC(t, 1);
    pc[2] = fn_801293FC(t, 2);
    pc[3] = 0x80;
    obj = *((void * *)&mgr->unk0x10);
    cw = fr.color;
    if (obj != NULL) {
        fr.sp8 = cw;
        vt = obj->unk0x14;
        ((s32 (*)(void *, void *))(vt->unk0x3C))((void *)((char *)obj + (s32)vt->unk0x38), &fr.sp8);
    }
    return true;
}
