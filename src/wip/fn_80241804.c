// RE-TRIAGED 2026-10-13: still 18.5% DIFF, size-exact 672B.
// Whole-function allocator cascade (homes/frame/stmw span per header). No new
// lever; body unchanged.
// 2026-10-17: shed-webs rewrite tried (old/delta scoped to block, mode used in
// loop via (x+delta)&3==(x+mode)&3 fold, res scoped to braces, tail p/d reused
// from dst/src): 17.3%, REGRESSES 1.2%. Frame/stmw span unchanged — the extra
// webs are not what sizes the frame; reverted to this body as best match.
// WIP DRAFT (non-matching) — PARKED 2026-08-25
// Reached 16.7% best (hand-rebuilt from disasm; full semantics reconstructed).
// Body is an undo/redo record transformer; every statement verified against
// want. Remaining diff = whole-function allocator cascade: arg0 homes r29 vs
// want r28, stmw span r17.. vs r22.. (15 saved webs vs want's 10), frame 0x68
// vs 0x50. Want's register plan: r22=arr,r23=aoff(-0x18),r24=doff(0) [IVs],
// r25=&sp8,r26=mode(delta&3; delta DIES via (x+delta)&3==(x+mode)&3 fold),
// r27=i,r28=o,r29=&sp20(sp+0x20),r30=dst walker,r31=src walker. Levers tried:
// old-=4 delta spelling (fixes prologue subf shape ✓), explicit doff/aoff
// accumulator vars (matches li -0x18/li 0 preheader ✓ but adds webs),
// post-loop pointer walk reuse of dst/src (REGRESSES -14%), p/d separate
// walkers. Frame slots: &sp8 must be sp+8 (24B), &sp20 sp+0x20.
// Callee truths: fn_8000F10C(MEM[0x802FFE98],(cnt-2)*12,1,0)->ptr;
// fn_80240B0C(&sp20,0,0,0,0,0,0) 7-arg; fn_80238964() 0-arg;
// fn_80236EF4(rec->f8,0)->ptr {w,h,...}; fn_80240BB4(ptr,&sp20);
// Mem_Free() 0-arg. Needs a dedicated allocator-coupling pass:
// try shedding webs one at a time w/ per-insn diff after each.
// family=m2c range=0x80241804-0x80241AA4 size=672B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 18.5% ([10]rev->18.5%).
#include "types.h"
#include "structs.h"
extern s32 lbl_802FFE98;
s32 fn_8000F10C(Unk_4897C6F8 *, s32, s32, Unk_E15B2970 *);
void fn_80240B0C(Unk_F96D0DC8 *, s32, s32, s32, s32, s32, s32);
void fn_80238964(void);
s32 fn_80236EF4(s32, s32);
void fn_80240BB4(void *, Unk_F96D0DC8 *);
void Mem_Free(void);
void fn_80241804(void *arg0, s32 arg1) {
    u8 sp8[24];
    u8 sp20[8];
    s32 *arr;
    u8 *src;
    u8 *dst;
    u8 *p;
    u8 *e;
    u8 *d;
    Unk_21634967 *res;
    s32 old;
    s32 delta;
    s32 mode;
    s32 i;
    s32 doff;
    s32 aoff;
    char *o;

    o = (char *)arg0;
    old = ((Unk_1D62F22E_2 *)o)->unk0xC;
    ((Unk_1D62F22E_2 *)o)->unk0xC = arg1;
    old -= 4;
    delta = arg1 - old;
    mode = delta & 3;
    if (delta & 1) {
        u8 t = o[5];
        o[5] = o[3];
        o[3] = t;
    }
    arr = NULL;
    if (((Unk_C4D756ED *)o)->unk0x28 != 0) {
        arr = (s32 *)fn_8000F10C(
            lbl_802FFE98, (((Unk_C4D756ED *)o)->unk0x2C - 2) * 12, 1, 0);
    }
    doff = 0;
    aoff = -0x18;
    for (i = 0; (u32)i < ((Unk_1D62F22E_2 *)o)->unk0x30; i++) {
        if (i <= 1) {
            dst = sp8 + doff;
            src = (u8 *)o + 0x10 + i * 12;
        } else {
            dst = (u8 *)arr + aoff;
            src = (u8 *)((Unk_C4D756ED *)o)->unk0x28 + i * 12 - 0x18;
        }
        ((Unk_41EA2015 *)dst)->unk0x4 = ((Unk_41EA2015 *)src)->unk0x4;
        ((Unk_41EA2015 *)dst)->unk0x0 = ((Unk_41EA2015 *)src)->unk0x0;
        ((Unk_59AB5482_2 *)dst)->unk0x8 = ((Unk_59AB5482_2 *)src)->unk0x8;
        fn_80240B0C((s32 *)sp20, 0, 0, 0, 0, 0, 0);
        if (((Unk_1D62F22E_2 *)o)->unk0x8 & 2) {
            fn_80238964();
            res = fn_80236EF4(((Unk_59AB5482_2 *)src)->unk0x8, 0);
            *(s32 *)sp20 = *(s32 *)res;
            ((Unk_21634967 *)sp20)->unk0x4 = res->unk0x4;
            if (src[3] & 1) {
                u8 t = sp20[5];
                sp20[5] = sp20[3];
                sp20[3] = t;
            }
        } else {
            fn_80240BB4(((Unk_59AB5482_2 *)src)->unk0x8, sp20);
        }
        switch (mode) {
        case 0:
            dst[0] = src[0];
            dst[2] = src[2];
            break;
        case 1:
            dst[0] = src[2];
            dst[2] = (o[5] - src[0]) - sp20[3];
            break;
        case 2:
            dst[0] = (o[3] - src[0]) - sp20[3];
            dst[2] = (o[5] - src[2]) - sp20[5];
            break;
        case 3:
            dst[2] = src[0];
            dst[0] = (o[3] - src[2]) - sp20[5];
            break;
        }
        dst[1] = src[1];
        dst[3] = (src[3] + delta) & 3;
        ((Unk_59AB5482_2 *)dst)->unk0x8 = ((Unk_59AB5482_2 *)src)->unk0x8;
        doff += 12;
        aoff += 12;
    }
    if (((Unk_C4D756ED *)o)->unk0x28 != 0) {
        Mem_Free();
    }
    ((Unk_C4D756ED *)o)->unk0x28 = (s32)arr;
    p = sp8;
    d = (u8 *)o + 0x10;
    do {
        *(s32 *)d = *(s32 *)p;
        ((Unk_4C649A8C *)d)->unk0x4 = ((Unk_4C649A8C *)p)->unk0x4;
        ((Unk_4C649A8C *)d)->unk0x8 = ((Unk_4C649A8C *)p)->unk0x8;
        p += 12;
        d += 12;
    } while (p <= sp8 + 12);
}
