// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80030290-0x80030580 (752B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

/* arg0+0x18: holder whose +0x0C is the head of the -1-terminated node list
   walked below.  0x18 sits inside a pad of Unk_C7387A53, so the shared header
   has no member for it (same local-typedef pattern as src/fn_800306D0.c). */
typedef struct {
    char pad0x0[0xC];
    s32 *node;
} WobbleMgr;

/* arg1: five f32 wobble parameters, read as lfs 0/4/8/0xC/0x10(r30). */
typedef struct {
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;
} WobbleParams;

extern s32 lbl_80305F9C;  /* script context pointer, cached in r29 */
extern u8 lbl_803003B5;   /* cached packed byte */

s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void CStruct_delete(void *, s32);
void fn_8012772C(void *, s32, f32);
s32 fn_8021D358(s32, s32);
s32 fn_8022986C(void *);
s32 fn_8022A9D0(void *);
s32 fn_8021B55C(void *, s32);
s32 fn_800301A0(s32, f32);
void fn_80137CB4(void *);
void fn_8013DE78(void *, Unk_C71E6DE1 *);

void fn_80030290(Unk_C7387A53 *arg0, WobbleParams *arg1, s32 arg2) {
    Unk_C71E6DE1 msg;   /* QB command message, 0x24B, at r1+8 */
    WobbleMgr *mgr;
    s32 *nd;            /* list node; same variable in BOTH walks on purpose */
    s32 *q1;
    s32 *q2;
    u16 h;              /* bit-packed u16 accumulator at r1+0x30 */
    u8 b_;
    s32 vt;
    s32 cstr;
    s32 cnode;
    s32 ctx;

    if (arg2 != 0 && arg0->unk0x30 == 0) {
        ctx = lbl_80305F9C;
        cnode = fn_8021D358(ctx, *(u16 *)((char *)arg0->unk0x78 + 0x1A));
        if (cnode != 0 && fn_8022986C(cnode) != 0) {
            cstr = fn_8021B55C(ctx, fn_8022A9D0(cnode));
            h = ((u8 *)&h)[1];
            h = (h & 0xFF) | (((u8)(((s16)h >> 8) | fn_800301A0(0, arg1->f0)) << 8) & 0xFF00);
            h = (h & 0xFF) | (((u8)(((s16)h >> 8) | (fn_800301A0(1, arg1->f1) << 2)) << 8));
            h = (h & 0xFF) | (((u8)(((s16)h >> 8) | (fn_800301A0(2, arg1->f2) << 3)) << 8));
            h = (h & 0xFF) | (((u8)(((s16)h >> 8) | (fn_800301A0(3, arg1->f3) << 4)) << 8));
            h = (h & 0xFF) | (((u8)(((s16)h >> 8) | (fn_800301A0(4, arg1->f4) << 5)) << 8));
            b_ = *(u8 *)((char *)arg0->unk0x78 + 0x1B);
            h = (h & 0xFF00) | b_;
            if (lbl_803003B5 != (h >> 8)) {
                fn_80137CB4(&msg);
                msg.unk0x4 = (s32)&h;
                msg.unk0x2 = 2;
                msg.unk0x0 = 0x3C;
                msg.unk0x14 = 1;
                fn_8013DE78(cstr, &msg);
                lbl_803003B5 = *(u8 *)&h;
            }
        }
    }
    mgr = (WobbleMgr *)((char *)arg0 + 0x18);
    nd = mgr->node;
    if (nd[1] == -1) {
        nd = NULL;
    }
    q1 = (nd != NULL) ? nd - 1 : NULL;
    if (q1 != NULL) {
        cstr = CStruct_ctor(CStruct_new(8));
        fn_8012772C(cstr, QB_WOBBLEAMPA, arg1->f0);
        fn_8012772C(cstr, QB_WOBBLEAMPB, arg1->f1);
        fn_8012772C(cstr, QB_WOBBLEK1, arg1->f2);
        fn_8012772C(cstr, QB_WOBBLEK2, arg1->f3);
        fn_8012772C(cstr, QB_SPAZFACTOR, arg1->f4);
        nd = mgr->node;
        if (nd[1] == -1) {
            nd = NULL;
        }
        q2 = (nd != NULL) ? nd - 1 : NULL;
        vt = *(s32 *)((char *)q2 + 0x18);
        ((void (*)(s32, s32, s32, s32))*(s32 *)((char *)vt + 0x34))(
            (s32)q2 + *(s16 *)((char *)vt + 0x30), QB_SETWOBBLEDETAILS, cstr, 0);
        if (cstr != 0) {
            CStruct_delete(cstr, 3);
        }
    }
}
