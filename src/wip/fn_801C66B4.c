// WIP DRAFT (non-matching) — hand-rebuilt from disasm (ps_disasm)
// family=hand range=0x801C66B4-0x801C6AC8 size=1044B
// UPDATED 2026-09-13 (c): extended flag matrix (recipe 49) found `-O1` -> 32.57% to 52.87%.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float -fno-sched-spec -O1
// RE-TRIAGED 2026-10-13: 53.6% NEAR (sweep, flagless score;
// header notes ~96% with extra_cflags -mps-float -fno-sched-spec -O1).
// Residual is missing reload + scratch-reg flips per header. No new lever;
// body unchanged.
// PARKED ~96%: remaining diffs are one missing reload of *(arg0+0xC) before
// the second psq pair-copy group (GCC copy-prop coalesces it with pair 1;
// want keeps a fresh load into r11) plus two scratch-reg name flips
// (b8n->r9/c->r11 and b8g->r10/cb->r11) that resist web-splitting,
// "+r" barriers, volatile loads, memory clobbers, and schedule flags.
// Key levers that DID land: -fno-sched-spec fixes the arg0/mgr saved-reg
// home swap (sched1 speculatively hoists the param copy above the first
// call, flipping allocation order); chained fn_8022989C(NextItem(mgr));
// EC0 page anchor routed through the recycled mgr variable.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 53.6% ([12]rev->53.6%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern void *lbl_80305EC0;
extern void *lbl_80305F9C;
extern f32 lbl_802ACD64;
extern f32 lbl_802ACD68;

typedef struct { __ps_t x; __ps_t y; } pspair_t;

f64 fn_800144EC(void);
void fn_801CA5C8(Unk_67E10D8C *);
void fn_801C9464(Unk_47DE0370 *);
void *NextItem(void *);
s32 fn_8022989C(CScript *);
s32 fn_802298B4(CScript *);
s32 fn_8021A18C(Unk_C7387A53 *);
s32 fn_80198F7C(s32);
void fn_801C9404(Unk_47DE0370 *);
void fn_801C9F40(Unk_B46CA436 *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(CStruct *, s32, s32);
s32 Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
s32 GetChecksum_3(Unk_6A70655D *, s32);
f32 sqrtf(f32);
void fn_801C1A9C(Unk_FFAD6788 *, f32);

void fn_801C66B4(Unk_0D44E0BF *arg0) {
    Unk_EFD74FFD *mgr = lbl_80305F9C;
    Unk_3336C6BE *b8a;
    Unk_130D31C8 *ca;
    Unk_073F5245 *b8n;
    Unk_31DE137E *b8h;
    Unk_130D31C8 *cn2;
    s32 moda;
    s32 t28;
    Unk_31DE137E *b8b;
    Unk_FFAD6788 *cb;
    s32 modb;
    s32 modc;
    Unk_FFAD6788 *cc;
    f32 lim;
    Unk_DF2324A8 *cm;
    Unk_31DE137E *b8g;
    s32 mg;
    void *cx;
    f32 sq1;
    f32 sq2;
    s32 msync;
    s32 fl1;
    s32 rs1;
    u8 u50;
    u8 u148;
    s32 fl2;
    s32 rs2;
    s32 e8v;
    s32 ecv;
    s32 v7c;
    s32 fl3;
    s32 rs3;

    arg0->unk0x2A4 = fn_800144EC();
    b8a = arg0->unk0x2B8;
    moda = b8a->unk0x1C;
    t28 = ((moda ^ 3) == 0);
    if (moda != 1) {
        ca = arg0->unk0xC;
        b8a->unk0x168 = ca->unk0x88;
        b8a->unk0x170 = ca->unk0x90;
        b8n = arg0->unk0x2B8;
        cn2 = arg0->unk0xC;
        b8n->unk0x178 = cn2->unk0x88;
        b8n->unk0x180 = cn2->unk0x90;
    }
    fn_801CA5C8(arg0);
    cm = arg0->unk0xC;
    arg0->unk0x50 = cm->unk0x58;
    arg0->unk0x58 = cm->unk0x60;
    cm->unk0x68 = cm->unk0x58;
    cm->unk0x70 = cm->unk0x60;
    fn_801C9464(arg0);
    mgr = NextItem(mgr);
    if ((fn_8022989C((void *)mgr) == 0) && (fn_802298B4((void *)mgr) == 0)) {
        if ((fn_8021A18C((s32)lbl_80305F9C) != 0) ||
            ((mgr = (void *)0x80300000,
              fn_80198F7C((s32)mgr->unk0x5EC0) == QB_NETFIREFIGHT)) ||
            (fn_80198F7C((s32)mgr->unk0x5EC0) == QB_FIREFIGHT)) {
            fn_801C9404(arg0);
        }
    }
    fn_801C9F40(arg0);

    if (t28 != 0) {
        b8b = arg0->unk0x2B8;
        modb = b8b->unk0x1C;
        if (modb != 3) {
            b8b->unk0x160 = 0;
            b8g = arg0->unk0x2B8;
            modc = b8g->unk0x1C;
            if (modc == 1) {
                lim = lbl_802ACD64;
                cb = arg0->unk0xC;
                if ((fabsf(*((f32 *)&cb->unk0xB8)) < lim) &&
                    (fabsf(*((f32 *)&cb->unk0xC0)) < lim)) {
                    b8g->unk0x160 = modc;
                }
            }
        }
    }
    b8h = arg0->unk0x2B8;
    mg = b8h->unk0x1C;
    if (mg != 1) {
        b8h->unk0x160 = 0;
    }

    if ((b8g->unk0x188 != 0) &&
        (((Unk_B1050619 *)arg0->unk0x2AC)->unk0x11F8 != 0)) {
        mgr = (void *)CStruct_ctor(CStruct_new(8));
        AddChecksum(mgr, QB_SKATERID, ((CScript *)arg0->unk0xC)->unk0x18);
        AddChecksum(mgr, QB_CONTROL_TYPE, ((Unk_B1050619 *)arg0->unk0x2AC)->unk0x11F8);
        Script_RunScript(QB_NONLOCALCLIENTINVEHICLE, mgr, 0, 0, 0);
        if (mgr != NULL) {
            CStruct_delete(mgr, 3);
        }
    } else if ((((Unk_2DD055BA *)arg0->unk0x2B8)->unk0x188 == 0) &&
               (arg0->unk0x2A8 != 0)) {
        mgr = (void *)CStruct_ctor(CStruct_new(8));
        AddChecksum(mgr, QB_SKATERID, ((CScript *)arg0->unk0xC)->unk0x18);
        Script_RunScript(0xF02E44F, mgr, 0, 0, 0);
        if (mgr != NULL) {
            CStruct_delete(mgr, 3);
        }
    }

    arg0->unk0x2A8 =
        ((Unk_2DD055BA *)arg0->unk0x2B8)->unk0x188;
    mgr = (void *)GetChecksum_3(*((s32 *)&arg0->unk0xC), QB_SKATERLOOPINGSOUND);

    if (((Unk_2DD055BA *)arg0->unk0x2B8)->unk0x20 == 0) {
        if (mgr->unk0xF8 != 1) {
            void *vt = mgr->unk0x18;
            ((s32 (*)(void *, s32))((Unk_DB0E2BAB *)vt)->unk0x44)
                ((void *)((char *)mgr + (s32)((Unk_DB0E2BAB *)vt)->unk0x40), 0);
            mgr->unk0xF8 = 1;
        }
        cc = arg0->unk0xC;
        fn_801C1A9C(mgr, sqrtf(
            (*((f32 *)&cc->unk0xB8) * *((f32 *)&cc->unk0xB8)) +
            (*((f32 *)&cc->unk0xC0) * *((f32 *)&cc->unk0xC0))) /
            lbl_802ACD68);

        msync = ((Unk_2DD055BA *)arg0->unk0x2B8)->unk0x1C;
        fl1 = mgr->unk0xE0;
        if (mgr->unk0x54 != msync) {
            fl1 |= 1;
        }
        rs1 = (fl1 != 0);
        mgr->unk0x54 = msync;
        mgr->unk0xE0 = rs1;
        fl2 = rs1;

        u50 = mgr->unk0x50;
        u148 = ((Unk_2DD055BA *)arg0->unk0x2B8)->unk0x148;
        if (u50 != u148) {
            fl2 |= 1;
        }
        rs2 = (fl2 != 0);
        mgr->unk0x50 = u148;
        mgr->unk0xE0 = rs2;
        fl3 = rs2;

        mgr->unk0xE8 =
            ((Unk_2DD055BA *)arg0->unk0x2B8)->unk0xA0;
        ecv = mgr->unk0xEC;
        v7c = ((Unk_2DD055BA *)arg0->unk0x2B8)->unk0x7C;
        if (ecv != v7c) {
            fl3 |= 1;
        }
        rs3 = (fl3 != 0);
        mgr->unk0xEC = v7c;
        mgr->unk0xE0 = rs3;
    } else {
        if (mgr->unk0xF8 != 0) {
            void *vt = mgr->unk0x18;
            ((s32 (*)(void *, s32))((Unk_DB0E2BAB *)vt)->unk0x44)
                ((void *)((char *)mgr + (s32)((Unk_DB0E2BAB *)vt)->unk0x40), 1);
            mgr->unk0xF8 = 0;
        }
    }
}
