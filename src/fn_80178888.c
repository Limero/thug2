// PROMOTED 2026-08-31 — fn_80178888 (byte-identical, verified 77/77 masked)
// range=0x80178888-0x801789BC size=308B. Registered + DOL byte-identical.
// Suggested rename: SkaterZoneIterFrame (iterates the lbl_802A83F8 frame list
// owned by g = lbl_80305F9C, copies arg0 fields into fr.a/b/c, dispatches via
// fn_8013CC84; returns 4 on null entry else 1).
//
// MATCHED 2026-08-31 (was parked at 97.4%): the residual doc-15 scheduler
// swap (want `li r0,0` where ngccc emitted `mr r26,r11`, and vice versa) was
// caused by the parked draft's own `__asm__("" : "+r"(sp))` barrier between
// the frame stores and `iter = (s32)sp;`. Removing the barrier lets the
// scheduler emit `li r0,0` (fr.count) before `mr r26,r11` (iter = sp) exactly
// as WANT — the copy-prop that barrier was blocking never happens once the
// `iter` pin (register s32 iter __asm__("r26")) is in place. Frame-template
// struct + r26 pin are the load-bearing parts; NO asm remains in the body.
// Semantics: iterates the lbl_802A83F8 sentinel-terminated frame list owned
// by global g = lbl_80305F9C (skater zone), copying arg0 fields into fr.a/b/c
// and dispatching via fn_8013CC84; returns 4 if the list entry is null, else
// 1. No symbol; suggest `SkaterZoneIterFrame`-style name if the owner struct
// is ever identified.
#include "types.h"
#include "structs.h"

extern s32 lbl_80305F9C;
extern char lbl_802A83F8[];

extern s32 fn_8021D2C4(s32 arg0, s32 arg1);
extern s32 fn_8021D454(s32 arg0, CStruct * arg1, s32 arg2);
extern s32 fn_8021D4E8(s32 arg0, CStruct * arg1, s32 arg2);
extern void fn_80137CB4(Unk_9F066EC1 * arg0);
extern s32 fn_8022A9B8(Unk_31DE137E * arg0);
extern void fn_8013CC84(void * arg0, s32 arg1, Unk_C71E6DE1 * arg2);
extern void fn_8021FE30(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

// frame template: pins the exact sp layout incl. holes (recipe 86)
struct iter_frame {
    s32 pad08;      /* +0x00 -> r1+0x08 */
    s32 count;      /* +0x04 */
    char *sentinel; /* +0x08 */
    s32 pad14;      /* +0x0C */
    u8 a;           /* +0x10 -> r1+0x18 */
    u8 pad19;       /* +0x11 */
    u16 b;          /* +0x12 */
    s32 c;          /* +0x14 */
    s32 hole20;     /* +0x18 */
    s32 e;          /* +0x1C */
    u8 f;           /* +0x20 */
    char tail[0x17];
};

s32 fn_80178888(Unk_A2CA54F3 *arg0) {
    struct iter_frame fr;
    char *sp;
    register s32 iter __asm__("r26");
    s32 g;
    s32 two;
    s32 eight;
    s32 entry;
    s32 walker;
    s32 obj;
    Unk_A8B25094 *p;

    g = lbl_80305F9C;
    sp = (char *)&fr;
    ((struct iter_frame *)sp)->count = 0;
    ((struct iter_frame *)sp)->sentinel = lbl_802A83F8;
    iter = (s32)sp;
    entry = fn_8021D2C4(g, arg0->unk0x10);
    if (entry == 0) {
        ((Unk_42076946_2 *)iter)->unk0x8 = lbl_802A83F8;
        return 4;
    }
    walker = fn_8021D454(g, iter, 1);
    two = 2;
    eight = 8;
    while (walker != 0) {
        fn_80137CB4((s32)((char *)&fr.a));
        if (walker != entry) {
            fr.c = arg0->unk0x0;
            fr.b = arg0->unk0xA;
            fr.a = arg0->unk0x4;
            obj = arg0->unk0xC;
            fr.e = 2;
            fr.f = 8;
            fn_8013CC84(obj, fn_8022A9B8(walker), (s32)((char *)&fr.a));
        }
        walker = fn_8021D4E8(g, (s32)&fr, 1);
    }
    if (arg0->unk0x4 == 0x49) {
        p = arg0->unk0x0;
        if (p->unk0xC != 0) {
            fn_8021FE30(g, p->unk0x8,
                        p->unk0x4, *(s32 *)p);
        }
    }
    ((Unk_42076946_2 *)iter)->unk0x8 = lbl_802A83F8;
    return 1;
}
