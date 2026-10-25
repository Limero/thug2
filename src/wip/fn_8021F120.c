// WIP DRAFT (non-matching) — rebuilt from want disasm 2026-08-25
// family=m2c range=0x8021F120-0x8021F500 size=992B
// RE-TRIAGED 2026-10-13: still 97.6% (242/248, 3 sched tie-breaks
// in entry block, RTL-birth-order wall per header). No new lever; body unchanged.
// PARKED 97.6% NEAR (242/248). The 4th blocker (f78c speculation
// window: want speculates the NEXT stmt's mode load between bl and
// result-store) was RESOLVED by the WA result-store split
// (t = fn_8021F78C(a0); mode = load; fr.sc.f78c = t;) — 240->242.
// Remaining 6 diffs are 3 pure doc-15-class sched1 ready-list tie-
// breaks in the ENTRY BLOCK on INDEPENDENT leaves (cbv-lo/m3 addis,
// they are 3 pairwise order swaps immune to EVERY lever tried):
//   1. At offsets 0x20/0x24 the want builds the cbv-lo address into r11 before
//   building m3 into r3, while this draft emits the m3 build before the lo
//   build. 2. At 0x28/0x2C the want zeroes r0 for the pad before loading g
//   into r31, while this draft emits the load before the zero. 3. At 0x34/0x3C
//   the want stores cb, stores pad, then copies into r25, while this draft
//   emits the r25 copy before the stores.
// Exhausted 2026-08-29: 30+ source-order permutations, volatile asm
// pins on every scratch, memory barriers, DAG reshapes (merged/removed
// pins), sched flags (-fno-schedule-insns{,2}, -fno-sched-interblock,
// -fno-sched-spec), -mcpu 7400/7410/750, flag combos, AND the C++
// frontend (.cpp per-object, 184/248 — far worse). All cap at 242.
// True bottleneck: GCC 2.95 sched1 breaks these equal-priority sibling
// ties by RTL birth order, which C source cannot reach without whole-
// body asm (banned, recipe 180).
// Retry hints: new sched lever from another function; a different
// compiler version (3.5/3.7/3.8/3.9) that schedules this block.
//
//
// Reg map (want): r30=arg0, r31=g(chase->hash->srcwalk->entry->d888),
// r29=mgr(recycled as mask 0xFFFF7FFF), r26=var_r26, r24=&es(esp),
// r25=&msg(msgp), r27=&sc(scp), r28=&buf(dst, recycled as zero).
// Levers proven here: pin-a-copy for a0/mgr/v26/scp/dst/esp/msgp;
// explicit "mr %0,%1" wedges for the two-web es/msg scratch-birth;
// struct-stride row walkers r6/r7 with (dp++)->v[5]-style advances to
// block ivopts final-value precompute; opaque asm counter births.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern s32 lbl_80305F04;
extern char lbl_802A83F8[];

void fn_80137CB4(Unk_9F066EC1 *);
s32 fn_8009CF2C(CStruct *);
s32 fn_8021E024(void *);
s32 fn_8017480C(Unk_FFAD6788 *);
s32 fn_8021B554(Unk_9994C3F5 *);
void fn_80216D10(Unk_A7137CF0 *);
s32 fn_8021F6D4(CStruct *);
void fn_8021EB8C(Unk_C7387A53 *);
void memset(void *, s32, s32);
s32 fn_80140010(s32, s32, void *);
s32 fn_8021F748(void *);
s32 fn_8021F78C(void *);
s32 fn_80140068(s32, void *, void *);
s32 fn_8021F010(Unk_C7387A53 *);
s32 fn_80219A80(void *);
s32 fn_8021F658(CStruct *);
s32 fn_8021F5D8(CStruct *);
s32 Mth_Rnd(s32);
void *fn_8021D454(void *, CStruct *, s32);
void *fn_8021D4E8(void *, CStruct *, s32);
void fn_80229C38(CScript *);
s32 fn_8022A9B8(Unk_31DE137E *);
void fn_8013CC84(void *, s32, Unk_C71E6DE1 *);
s32 NextNewPlayerInfo(void *);
void fn_8022A510(void *, s32);
void fn_8021FDF0(CScript *, s32);
void fn_8021FE00(CScript *, s32);
void fn_8021FF74(void *);
void fn_8021F500(void *);

typedef struct { void *iter; void *pad; void *cb; } ess120_t;
typedef struct {
    u8 b0; u8 _1; u16 bh; s32 w4; u8 _8[4]; s32 w8; u8 b10; u8 _11[0x17];
} msg120_t;
typedef struct { s32 v[6]; } row120_t;
typedef struct {
    s32 mode; s32 swres; s32 score; s32 f78c; u8 _10[4];
    u8 f010; u8 beq55; u8 rng56; u8 _17;
    s32 a80; s32 f658; s32 f5d8;
} sc120_t;

void fn_8021F120(void *arg0) {
    struct {
        ess120_t es;   /* r1+0x08 */
        char _p0[4];
        msg120_t msg;  /* r1+0x18 */
        sc120_t sc;    /* r1+0x40 */
        u8 x77;        /* r1+0x64 */
        char _p3[3];
        s32 buf[8];    /* r1+0x68 */
    } fr;
    register void *a0 __asm__("r30");
    register s32 mgrr __asm__("r29");
    register s32 v26 __asm__("r26");
    register sc120_t *scp __asm__("r27");
    register s32 *dst __asm__("r28");
    register ess120_t *esp __asm__("r24");
    register msg120_t *msgp __asm__("r25");
    Unk_AA185ABA *g;
    s32 mode;
    s32 t;
    s32 t8;
    s32 t9;
    s32 w;
    void *entry;

    register char *pg9 __asm__("r9");
    {
        __asm__ volatile("lis %0,%1@ha" : "=r"(pg9) : "s"(lbl_80305EAC));
    }
    a0 = arg0;
    {
        register ess120_t *e10 __asm__("r10");
        register msg120_t *m3 __asm__("r3");
        void *cbv;
        __asm__("" : "=r"(e10) : "r"(&fr.es));
        cbv = (void *)lbl_802A83F8;
        __asm__("" : "+r"(cbv));
        __asm__("" : "=r"(m3) : "r"(&fr.msg));
        g = ((Unk_5ACE0BC2 *)pg9)->unk0x5EAC;
        __asm__("mr %0,%1" : "=r"(esp) : "r"(e10));
        e10->cb = cbv;
        e10->pad = NULL;
        msgp = m3;
        fn_80137CB4(m3);
    }
    if (fn_8009CF2C(a0) != 0) {
        mgrr = fn_8021E024(a0);
    } else {
        mgrr = fn_8017480C(g);
    }
    v26 = fn_8021B554(a0);
    fn_80216D10(a0);
    ((Unk_F990A9AB *)a0)->unk0x28 = fn_8021F6D4(a0);
    fn_8021EB8C(a0);
    memset((char *)a0 + 0x7C, 0, 0x50);
    mode = ((Unk_F990A9AB *)a0)->unk0x28;
    if (mode == QB_HORSE) {
        g = fn_80140010(mgrr, QB_HORSE_TIME_LIMIT, QB_TIME);
    } else {
        g = fn_80140010(mgrr, QB_TIME_LIMIT, QB_TIME);
    }
    ((Unk_F990A9AB *)a0)->unk0x2C = fn_8021F748(a0);
    fr.sc.mode = ((Unk_F990A9AB *)a0)->unk0x28;
    t = fn_8021F78C(a0);
    mode = ((Unk_F990A9AB *)a0)->unk0x28;
    fr.sc.f78c = t;
    if (mode == (s32)QB_NETGOALATTACK || mode == QB_KING || mode == QB_NETKING ||
        mode == QB_NETSCORECHALLENGE || mode == (s32)QB_SCORECHALLENGE || mode == QB_FIREFIGHT ||
        mode == (s32)QB_NETFIREFIGHT) {
        fr.sc.swres = 0;
    } else if (mode == QB_NETCTF) {
        if (fn_80140068(mgrr, QB_CTF_GAME_TYPE, QB_CHECKSUM) == (s32)QB_TIMED_CTF) {
            fr.sc.swres = g;
        } else {
            fr.sc.swres = 0;
        }
    } else {
        fr.sc.swres = g;
    }
    dst = &fr.buf[0];
    fr.sc.beq55 = fn_80140068(mgrr, QB_SCORE_RESET, QB_CHECKSUM) == (s32)QB_BOOLEAN_TRUE;
    g = (s32)((char *)a0 + 0x54);
    scp = &fr.sc;
    fr.sc.f010 = (u8)fn_8021F010(a0);
    fr.sc.score = fn_80140010(mgrr, QB_TARGET_SCORE, (s32)QB_SCORE);
    fr.sc.a80 = fn_80219A80(a0);
    fr.sc.f658 = fn_8021F658(a0);
    fr.sc.f5d8 = fn_8021F5D8(a0);
    do {
        t = Mth_Rnd(0xFF) + 1;
        t9 = ((Unk_F990A9AB *)a0)->unk0x31;
        __asm__("clrlwi %0,%1,0x18" : "=&r"(t8) : "r"(t));
        fr.sc.rng56 = (u8)t;
    } while (t8 == t9);
    {
        register s32 cnt9 __asm__("r9");
        register row120_t *dp __asm__("r6");
        register row120_t *sp32 __asm__("r7");
        __asm__("mr %0,%1" : "=r"(dp) : "r"((row120_t *)dst));
        __asm__("mr %0,%1" : "=r"(sp32) : "r"((row120_t *)g));
        fr.x77 = ((Unk_F990A9AB *)a0)->unk0x77;
        cnt9 = 0x18;
        do {
            w = sp32->v[0];
            cnt9 -= 0x18;
            dp->v[0] = w;
            w = sp32->v[1];
            dp->v[1] = w;
            w = sp32->v[2];
            dp->v[2] = w;
            w = sp32->v[3];
            dp->v[3] = w;
            w = sp32->v[4];
            dp->v[4] = w;
            w = sp32->v[5];
            sp32++;
            (dp++)->v[5] = w;
        } while (cnt9 != 0);
        w = sp32->v[0];
        dp->v[0] = w;
        w = sp32->v[1];
        dp->v[1] = w;
    }
    {
        register s32 m29 __asm__("r29");
        register s32 z28 __asm__("r28");
        m29 = (s32)QB_UNKNOWN_0xFFFF0000;
        fr.msg.w4 = (s32)scp;
        __asm__("li %0,0" : "=r"(z28));
        fr.msg.bh = 0x48;
        m29 |= 0x7FFF;
        fr.msg.b0 = 0x34;
        fr.msg.w8 = 2;
        fr.msg.b10 = 8;
        g = (s32)fn_8021D454(a0, &fr.es, 1);
        while (g != 0) {
            g->unk0x28 = z28;
            fn_80229C38((void *)g);
            g->unk0x1D8 &= m29;
            fn_8013CC84(v26, fn_8022A9B8((void *)g), msgp);
            if (fn_8009CF2C(a0) == 0) {
                break;
            }
            g = (s32)fn_8021D4E8(a0, &fr.es, 1);
        }
    }
    if ((g = NextNewPlayerInfo(a0)) != 0) {
        fn_8022A510(g, 0);
    }
    fn_8021FDF0(a0, 0);
    fn_8021FE00(a0, -1);
    fn_8021FF74(a0);
    fn_8021F500(a0);
    {
        void *cbv = (void *)lbl_802A83F8;
        lbl_80305F04 = 0;
        esp->cb = cbv;
    }
}
