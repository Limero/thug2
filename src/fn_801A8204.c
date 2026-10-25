// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A8204-0x801A82DC (216B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AB954[];
s32 fn_800546A0(s32);
s32 fn_80125A08(s32, s32);
s32 fn_8012954C(CStruct *, s32);
s32 fn_801293FC(CStruct *, s32);
void fn_80057CB0(CStruct *);
bool fn_801A8204(CScript *arg0, s32 t) {
    s32 color;
    s32 spC;
    u8 *pc;
    void *op;
    void *mgr;

    mgr = fn_800546A0(arg0->unk0x18);
    t = fn_8012954C(fn_80125A08((s32)lbl_802AB954, 0), t);
    *(u8 *)&color = fn_801293FC(t, 0);
    *((u8 *)&color + 1) = fn_801293FC(t, 1);
    pc = (u8 *)&color;
    op = &spC;
    pc[2] = fn_801293FC(t, 2);
    pc[3] = 0x80;
    fn_80057CDC(op, mgr);
    if ((*(u8 *)&spC == *(u8 *)&color)
        && (*((u8 *)&spC + 1) == *((u8 *)&color + 1))
        && (*((u8 *)&spC + 2) == *((u8 *)&color + 2))) {
        fn_80057CB0(mgr);
    }
    return true;
}
