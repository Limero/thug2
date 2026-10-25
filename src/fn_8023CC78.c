// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023CC78-0x8023CDCC (340B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_80238AC0(Unk_F0530266 *, void *, s32);
extern s32 fn_8023821C(s32, Unk_5D1D68CC *, s32 *);
extern s32 fn_8023B17C(s32, s32);
extern s32 fn_80230B18(s32, s32);
extern s32 fn_802403A4(s32);
extern s32 fn_80236EF4(CStruct *, s32, s32 *);
extern s32 fn_80236FE4(CStruct *, CStruct *, s32);
extern void fn_80241804(void *, s32);
extern void fn_802377C8(s32, void *, s32);
extern void fn_802361E8(Unk_7BAE36EB *, void *, s32);
extern void fn_802403A0(s32);

extern s32 lbl_802FFE98;
extern char lbl_802B0E98[];

typedef struct {
    s32 w;
    u16 h;
} pair_t;

bool fn_8023CC78(CStruct *arg0) {
    pair_t sp8;
    pair_t *q;
    pair_t *p;
    Unk_21634967 *ha;
    Unk_21634967 *hb;
    s32 t;
    s32 t2;
    s32 t3;
    s32 ta;
    s32 w2;
    u16 h2;

    q = &sp8;
    __asm__("mr %0,%1" : "=&r"(p) : "r"(q));
    ha = (char *)arg0 + 4;
    sp8.w = arg0->unk0x4;
    q->h = ha->unk0x4;
    if (fn_80238AC0(arg0->unk0x0, q, 0) != 1) {
        return false;
    }
    w2 = arg0->unk0x4;
    h2 = ha->unk0x4;
    t = fn_8023821C(arg0->unk0x0,
                    (sp8.w = w2, p->h = h2, p),
                    0);
    if (t + ((Unk_6A78CE27 *)ha)->unk0x4 > 0x11) {
        return false;
    }
    t2 = fn_8023B17C(arg0->unk0x0,
                     *(s32 *)(arg0->unk0x48 + 0x34));
    if (t2 != 0) {
        if (fn_80230B18(**((s32 * *)&arg0->unk0x0), t2) == 0) {
            return false;
        }
    }
    fn_802403A4(*(s32 *)(*(s32 *)&lbl_802FFE98 + 0x11C));
    ta = fn_80236EF4(arg0->unk0x0,
                     *(s32 *)(arg0->unk0x48 + 0x34), 0);
    t3 = fn_80236FE4(*(s32 *)arg0, ta, 0);
    fn_80241804(t3, arg0->unk0x3C);
    hb = (char *)arg0 + 4;
    w2 = arg0->unk0x4;
    h2 = hb->unk0x4;
    fn_802377C8(*(s32 *)arg0, (sp8.w = w2, p->h = h2, p), t3);
    fn_802403A4(*(s32 *)(*(s32 *)&lbl_802FFE98 + 0x11C));
    fn_802361E8(*((u32 *)&arg0->unk0x0), hb, 0);
    fn_802403A0(lbl_802B0E98);
    return true;
}
