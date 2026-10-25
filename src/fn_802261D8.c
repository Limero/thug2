// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802261D8-0x802263BC (484B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305FF8;
extern char lbl_802B0154[];
extern char lbl_802B0160[];
extern char lbl_802B010C[];
s32 fn_8021D2C4(s32, s32);
s32 fn_802332B8(s32, s32);
void fn_8013DC7C(s32, s32, s32, s32, void *, void *, s32, s32, s32);
s32 fn_801FC0E0();
s32 fn_801FA284(s32);
s32 fn_80222D6C(s32);
void fn_80222DA4(Unk_B8D659B7 *, s32);
s32 fn_80222DFC(Unk_C5BAE83F *);
s32 fn_80222DF4(void *);
void fn_80137CB4(Unk_9F066EC1 *);
s32 fn_800145AC(void);
s32 fn_8022A9B8(Unk_31DE137E *);
void fn_8013CC84(void *, s32, Unk_C71E6DE1 *);
void fn_8022A860(CScript *, s32);
void fn_8013E184(s32 *, s32);

bool fn_802261D8(void *arg0) {
    struct { u8 kind; u16 len; void *ptr; char _p[4]; s32 two; u8 eight; char _q[0x12]; } msg;
    struct { s32 v; u8 z; } sp38;
    s32 id;
    s32 nine;
    s32 mgr;
    s32 node;
    s32 hud;
    Unk_6A78CE27 *t27;
    s32 f1;
    s32 f2;
    s32 f3;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 t_typ;
    s32 typ;
    register void *a0 __asm__("r29");

    __asm__("mr %0,%1" : "=r"(a0) : "r"(arg0));
    nine = 1;
    mgr = ((Unk_C8FEE62D *)a0)->unk0x18;
    node = fn_8021D2C4(mgr, ((Unk_C8FEE62D *)a0)->unk0x10);
    hud = ((Unk_C8FEE62D *)a0)->unk0xC;
    t27 = *(void **)a0;
    f1 = *(s32 *)(((Unk_C8FEE62D *)a0)->unk0x10 + 0x48);
    t1 = fn_802332B8(lbl_80305FF8, 0);
    fn_8013DC7C(hud, f1, 0x6C, 0x3A98, t1, (s32)lbl_802B0154, 8, 0, nine);
    f2 = *(s32 *)(((Unk_C8FEE62D *)a0)->unk0x10 + 0x48);
    fn_801FC0E0();
    t2 = fn_801FA284(fn_801FC0E0());
    fn_8013DC7C(hud, f2, 0x88, 0x1132, t2, (s32)lbl_802B0160, 8, 0, nine);
    if (fn_80222D6C(mgr) != 0) {
        fn_80222DA4(mgr, *(s32 *)t27);
        f3 = *(s32 *)(((Unk_C8FEE62D *)a0)->unk0x10 + 0x48);
        t_typ = (u16)fn_80222DFC(mgr);
        t3 = fn_80222DF4(mgr);
        fn_8013DC7C(hud, f3, 0x87, t_typ, t3, (s32)lbl_802B010C, 8, 0, nine);
    }
    typ = (s8)t27->unk0x4;
    if (typ == 0x46) {
        fn_80137CB4(&msg);
        sp38.v = *(s32 *)t27;
        sp38.z = 0;
        id = fn_800145AC();
        msg.eight = msg.len = 8;
        msg.two = 2;
        msg.ptr = &sp38;
        msg.kind = (u8)typ;
        fn_8013CC84(hud, fn_8022A9B8(node), &msg);
        msg.ptr = &id;
        msg.len = 4;
        msg.kind = 0x25;
        fn_8013CC84(hud, fn_8022A9B8(node), &msg);
        fn_8022A860(node, id);
        fn_8013E184(hud, 0);
    }
    return true;
}
