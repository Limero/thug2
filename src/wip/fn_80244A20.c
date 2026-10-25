// WIP DRAFT (non-matching) — hand-rebuilt from disasm
// family=m2c range=0x80244A20-0x80244BC4 size=420B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// RE-TRIAGED 2026-10-16: still 81% NEAR, size-exact 420B. Retried the two
// open levers from the header: (1) swapping the tail equality to
// (wlk->unk0xC == arg1->unk0xC) only swaps the load order, the cmpw stays
// inverted either way (79%, -1); (2) precomputing the call#2 byte-sums in
// want order via named u8 temps spills and cascades to 61%. A fully
// byte-typed quadkey_t rewrite also collapses the key-copy shape (6%) — the
// cast-based member accesses are load-bearing. Body unchanged.
// PARKED 81%: structure fully matches (goto state-machine list walk kills the
// GCSE address-split copy; s8 temp gives the double-extsb; manual b0 hoist;
// chained fn_80238964()->fn_80236EF4(); 0-arg F738/F758 getters; chained
// fn_80245624(0x1C)->fn_80243F58). Residual 20 insns = two doc-15-class
// coin-flips that resist ~50 source shapes + flags (-fno-gcse,
// -fno-rerun-cse-after-loop, sched set): (a) arg0/id callee-saved home swap
// (want arg0=r27,id=r29; got arg0=r29,id=r27; local a0-pin fixes arg0 but
// rotates arg1/id instead); (b) call#2 arg-sum order (want computes r5sum
// b5+b2 first with loads [b0,b2,b5,b3]; got computes r4sum first with loads
// [b2,b0,b3,b5]). NOTE: want reloads key bytes across calls (no CSE) -
// suggest &key escaped in original TU; try passing &key-derived ptrs to an
// opaque helper if reopened.
#include "types.h"
#include "structs.h"
s32 fn_80238964(void);
void *fn_80236EF4(CStruct *, s32, s32 *);
s32 fn_8023F738(void);
s32 fn_8023F758(void);
s32 fn_80245624(s32);
void *fn_80243F58(void *);
void fn_802449DC(Unk_F96D0DC8 *, u8, u8);
typedef struct { u32 w; u16 h; } quadkey_t;

s32 fn_80244A20(Unk_C7387A53 *arg0, Unk_4A174A22 *arg1, s32 arg2) {
    quadkey_t key;
    u8 b0v;
    register s32 wlk __asm__("r11");
    s32 id;
    Unk_6E48A312 *node;
    s32 var_r3;

    *((u32 *)&((Unk_3CB0ABEC *)&key)->unk0x0) = *((u32 *)&arg1->unk0x0);
    ((Unk_638CF717 *)&key)->unk0x4 = arg1->unk0x4;
    {
        s8 t = ((Unk_CE0FDCCC *)&key)->unk0x1;
        t = t + arg2;
        ((Unk_CE0FDCCC *)&key)->unk0x1 = t;
    }
    id = fn_80236EF4((void *)fn_80238964(), arg1->unk0x34, 0);
    wlk = arg0->unk0xC;
    if (wlk != 0) {
        b0v = ((Unk_3CB0ABEC *)&key)->unk0x0;
    loop_2:
        if (((((Unk_6E48A312 *)wlk)->unk0x4 == id) &&
             (((Unk_6E48A312 *)wlk)->unk0x8 == b0v) &&
             (((Unk_6E48A312 *)wlk)->unk0x9 == ((Unk_638CF717 *)&key)->unk0x1) &&
             (((Unk_6E48A312 *)wlk)->unk0xA == ((Unk_638CF717 *)&key)->unk0x2) &&
             (((Unk_6E48A312 *)wlk)->unk0x10 == ((Unk_638CF717 *)&key)->unk0x3) &&
             (((Unk_6E48A312 *)wlk)->unk0x11 == ((Unk_CE0FDCCC *)&key)->unk0x5) &&
             (arg1->unk0xC == ((Unk_6E48A312 *)wlk)->unk0xC))) {
            return 1;
        }
        wlk = ((Unk_6E48A312 *)wlk)->unk0x18;
        if (wlk != 0) {
            goto loop_2;
        }
    }
    if (fn_8023F738() == fn_8023F758()) {
        return 0;
    }
    node = fn_80243F58((void *)fn_80245624(0x1C));
    node->unk0x4 = id;
    node->unk0x8 = ((Unk_3CB0ABEC *)&key)->unk0x0;
    node->unk0x9 = ((Unk_638CF717 *)&key)->unk0x1;
    node->unk0xA = ((Unk_638CF717 *)&key)->unk0x2;
    node->unk0x10 = ((Unk_638CF717 *)&key)->unk0x3;
    node->unk0x11 = ((Unk_CE0FDCCC *)&key)->unk0x5;
    fn_802449DC(arg0, ((Unk_3CB0ABEC *)&key)->unk0x0, ((Unk_638CF717 *)&key)->unk0x2);
    fn_802449DC(arg0, (u8)(((Unk_638CF717 *)&key)->unk0x3 + ((Unk_3CB0ABEC *)&key)->unk0x0 - 1),
                (u8)(((Unk_CE0FDCCC *)&key)->unk0x5 + ((Unk_638CF717 *)&key)->unk0x2 - 1));
    node->unk0xC = arg1->unk0xC;
    node->unk0x18 = arg0->unk0xC;
    arg0->unk0xC = (s32)node;
    var_r3 = 1;
    return var_r3;
}
