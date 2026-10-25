// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022D538-0x8022D6E4 (428B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_802B0580;
extern f32 lbl_802B0584;
extern f32 lbl_802B0588;
extern f32 lbl_802B058C;
extern f32 lbl_802B0590;
extern f32 lbl_802B0594;
extern f32 lbl_802B0598;
void *fn_80238970(void);
void fn_80236E70(void);
s32 fn_80054DC4(void);
s32 fn_80007264(void *, void *, void *);
void fn_80057334(s32, void *, s32, f32);
void fn_80240B0C(Unk_F96D0DC8 *, s32, s32, s32, s32, s32, s32);
void fn_80238784(void *, u8 *, f32 *, void *);

void fn_8022D538(void) {
    u8 fr[0x70];
    register char *pc __asm__("r26");
    s32 res;
    f32 c0;
    f32 c1;
    f32 c2;
    f32 inc;
    f32 *pa;
    f32 *pb;
    f32 *pv30;
    f32 *pv48;
    f32 *pd;
    Unk_BE7EBD4F *mgr;

    fn_80238970();
    fn_80236E70();
    res = fn_80054DC4();
    if (res != 0) {
        pc = (char *)0x802B0000;
        c0 = lbl_802B0580;
        c1 = lbl_802B0584;
        c2 = lbl_802B0588;
        pa = (f32 *)(fr + 0x20);
        pb = (f32 *)(fr + 0x30);
        pv30 = (f32 *)(fr + 0x28);
        pv48 = (f32 *)(fr + 0x40);
        pd = (f32 *)(fr + 0x50);
        ((Unk_9A7FD397 *)fr)->unk0x20 = c0;
        pa[1] = c0;
        pa[2] = c0;
        ((Unk_1D62F22E_2 *)fr)->unk0x2C = c1;
        ((Unk_9A7FD397 *)fr)->unk0x30 = c2;
        pb[1] = c2;
        pb[2] = c2;
        ((Unk_9A7FD397 *)fr)->unk0x3C = c1;
        fn_80007264(fr, pa, pb);
        fn_80057334(res, fr, 1, ((Unk_BCEF8EE8 *)pc)->unk0x58C);
        fn_80240B0C(pa, 0, 0, 0, 0, 0, 0);
        mgr = fn_80238970();
        {
            s32 tw = mgr->unk0x3524;
            u16 th = mgr->unk0x3528;
            ((Unk_1D62F22E_2 *)fr)->unk0x20 = tw;
            ((Unk_897A0ACF *)pa)->unk0x4 = th;
        }
        mgr = fn_80238970();
        fn_80238784(pv30, mgr, pa, 0);
        fr[0x20] = fr[0x20] + fr[0x23] - 1;
        fr[0x22] = fr[0x22] + fr[0x25] - 1;
        mgr = fn_80238970();
        fn_80238784(pv48, mgr, pa, 0);
        inc = lbl_802B0590;
        ((Unk_1D62F22E_2 *)fr)->unk0x28 += inc;
        ((Unk_9A7FD397 *)fr)->unk0x30 += inc;
        ((Unk_1D62F22E_2 *)fr)->unk0x40 += inc;
        ((Unk_9A7FD397 *)fr)->unk0x48 += inc;
        ((Unk_1D62F22E_2 *)fr)->unk0x2C = lbl_802B0594;
        ((Unk_9A7FD397 *)fr)->unk0x44 = lbl_802B0598;
        fn_80007264(pd, pv30, pv48);
        fn_80057334(res, pd, 0, ((Unk_BCEF8EE8 *)pc)->unk0x58C);
    }
}
