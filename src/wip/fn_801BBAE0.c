// WIP DRAFT — RE-AUDIT RETRY 2026-08-25 ("VMX" park overturned, doc06 M5.0q).
// family=vmx range=0x801BBAE0-0x801BE6A8 size=11208B
// extra_cflags: -mps-float
//
// =============================================================================
// VERDICT 2026-08-25: NOT VMX. Hand-decoded ALL 252 opcode-4 words in
// [0x801BBAE0,0x801BE6A8) against BOTH forms (X-form XO10@21-30 /
// A-form xo5@26-30 via tools/ps_diff.py tables + <scratch>):
// ZERO undecodable words. Census (all standard emittable Gekko PS):
//   ps_mul x46, ps_mr x40, ps_merge00 x34, ps_muls0 x30, ps_sub x22,
//   ps_merge10 x20, ps_madd x19, ps_sum0 x19, ps_rsqrte x13, ps_add x8,
//   ps_res x1  (+ ~500 psq_l/psq_st pair accesses).
// capstone vmhaddshs/vmsumshm/vsel/maddhd labels were misdecodes (PS A-form
// frC @bits21-25 collides w/ VMX VA-form vc). TOOLING: ps_disasm.py DROPPED
// one word here (@BBD34 psq_l f11,192(r31)) shifting later labels — verify
// against raw words (§7c-155).
//
// PARKED (best-match compiling body): sweep DIFF under -mps-float,
// ps_diff 2/296 (0.7%) — got spans only the front ~0x4A0 of want's 0x2BC8;
// streams desync at the prologue's entry `mfcr r12` + early block layout.
// Walls + retry levers at bottom.
// =============================================================================
// FUNCTION IDENTITY: camera/cinematic update for skater entity arg0.
// State: countdown arg0+0x30, angle accum +0x78, FOV +0x134, orbit angles
// +0x138/+0x13C/+0x140, cam mode +0x12C (0/1/2), smoothing +0x100/+0x114.
// QB hashes QB_CAMERA(0xC4E311FA)/0x5BD63B29(camstate)/0x589E5FB3(camcfg)/
// 0x16B8E4CB(bit idx). Float kit = rodata page lbl_802AC3B4..FC; basis table
// lbl_802AC368[0x2C]. NOTE: psq displacements print DECIMAL (88(r1)=0x58).
//
// FRAME (stwu r1,-0x3F0): CR->r12@0x390; stmw r15..r31@0x394;
// f29/f30/f31@0x3D8/E0/E8; LR@0x3F4; locals sp8..sp38F (0x388B frame struct).
//
// REGISTER ROLES: r31=arg0; r20=QB_CAMERA cfg; r28=*(*(r20)+0xC)+0x78 camdata
// (recycled *(arg0+0x178) later); r30=mode (*(*(arg0+0x180))+0x1C, recycled);
// r22=CR snapshot (mfcr after countdown tests; mtcrf 0x80,r22 TWICE mid-body
// @BBFAC/@BE654 re-installs cached cr0 countdown flag AFTER calls);
// r12=entry-CR save; epilogue mtcrf 0x38,r12 restores cr2/cr3/cr4 = THREE
// cached mode compares (cr3==2 @BBC78, cr2==3 @BC038, cr4==1 @BC03C) live
// across ~50 calls — doc-28 MEGA-case; r18=bool countdown-active;
// r19=bool angle-delta>0.02; bases r15=&sp8 r16=&sp26C r17=&sp268 r21=&spB8
// r23=&sp28 r25=&sp68(recycled &sp88) r26=&sp38 r27=&sp78 r29=&sp18;
// r24=lis 0x802A0000 anchor; f29=time; f30/f31 const reloads (0.0f/1.0f).
//
// SECTION MAP (rel offsets; ground truth = raw words):
//   +0x000 prologue; !*(arg0+0x17C)->epi. +0x014 early-out |=1.
//   +0x044 countdown/QB/time/BF230/24610.
//   +0x0D8 COPY WINDOW: 5 psq pairs arg0+0x48..->cam+0x78..; sp8 vec =
//     cam->98/9C/A0/1.0f; 9 base setups; li r0,4; mtctr; bdnz . <- EMPTY
//     DOLOOP WINDOW (doc-30; frozen verbatim below — recycling web no C web
//     reproduces; builtin-equivalent = __ps_t pair copies + pointer assigns).
//   +0x084 camstate fetch; cmpwi cr3,mode,2 (CACHED); copy arg0+128..184->
//     sp24..87 (8 pairs).
//   +0x1F4 mode!=2 path: basis load (cam->C8 ? fn_80144CB0()+0x20 : ->F0);
//     arg0+192={p1.x,0,p1.y,0}; TWO normalize webs
//     dot=sum0(madd(p1,p1,merge00(mul(p2,p1),tbl))) >0 ->
//     rsqrte/muls0 (web A -> arg0+192/200; web B -> sp88/sp90 w/ sp92=0);
//     wrap angles atan2f + 2pi fixups; |delta|>0.02 -> r19=1;
//     *(arg0+0x78)+=1.
//   +0x3A4 else: *(arg0+0x78)=0; vectors from fn_80144CB0()+0 or
//     camstate+0xD0 -> sp24..87; copy back to arg0+128..184.
//   +0x484 FOV: (mode==4 && cam->C8) ? cfg->CC*-1.27832e-4 : 0.0f;
//     if != *(arg0+0x134): mtcrf 0x80,r22; bne(restored cr0!) ->
//     smooth lerp store [doc-28].
//   +0x504 sp88/sp96 = mode==0 ? sp40/sp48 : *(*(arg0+0x180)+0x168/0x170);
//     stage sp68..74 floats {c17c->B8, 0.0, c17c->C0, 1.0}; fn_801BECBC(arg0)
//     (ret tested later as cr7).
//   +0x548 conditional tree (r184 null / ->1C, cr7, *(r180)->AC) builds
//     sp38/sp78 basis groups from rodata kit + staged rsqrte normalize webs
//     into sp2B4..sp2CC; vsel clamps.
//   +0x62C transform #1: P = M1(&sp18 cols) x M2(fn_80003EB0(&sp98,f) ret)
//     -> spD8..sp117 (fmadds k-desc chains, ~230 insns).
//   +0x9E8 guard tree (mode cr3 / *(arg0+0x130)!=0 / r19) -> PS dot block vs
//     arg0->17C vectors; fneg guard; spin; fn_80003EB0; transform #2
//     (dst spC8..). +0xEB8 fn_801BB4A0 x3 guards (+0x138/13C/140).
//   +0xF44 spins; GIANT LOOP REGION +0xF60..+0x135C: fn_8010794C(&sp272);
//     fn_80107A80(&sp272,0x90,0); fn_80108094(&sp118,&sp88,&sp98,1) probe ->
//     *(arg0+0x12C)=0/1/2; two retry passes (+-offset fn_80003EB0 args);
//     CObject_RemoveRefLink cleanup.
//   +0x1D8C flag-bit set/clear via Script_GetInteger(HASH_BITIDX,0) slw/rotlw(-2).
//   +0x1DF8 fn_80003830(&sp78,c,c,c); negated basis rows -> cam+0x30..3F.
//   +0x1EBC |.|>0.9999 tests; fn_80007BFC submit; spins; fn_801FF554 x4 +
//     fn_800086B0 x4 passes; fdivs normalize; 0.9998 clamps.
//   +0x21C8 fn_801BEE7C(&spB8,arg0,r18); guarded fn_801BF080 x2; final PS
//     assembly; draw submits fn_800B69A0/fn_800B6A88 x2; fn_801BED44 guard;
//     mfcr-r11 bit test; fn_801FF57C(r21,r28,&spD8,1,1); mtcrf 0x80,r22;
//     copy spB8/spC0 -> cam+0x58/5C; maybe fn_80024610(*(r20+0x1C)); epi.
//
// NOTE: 0x2BC8 = 11208B (symbols.txt end-start; earlier notes saying 11144
// were arithmetic slips).
// PARKED walls (byte-exactness blockers, none emission-related) + PROVEN
// levers this round (2026-08-25):
//  PROVEN: frame = volatile S V[110] (0x370) + saves => stwu -0x3F0 EXACT w/
//    stfd f29/f30/f31 @0x3D8/E0/E8, stmw r15 @0x394 (V[108..113] all give
//    0x408 — locals granularity is 8B but overhead differs; 110 is the hit).
//  PROVEN: register pins flag18->r18 / camcfg->r20 hold (want roles).
//  PROVEN: countdown bool wants the BRANCHY-BOOLEAN shape (r11=1 default;
//    bit==0 -> r11=0; if(r11) flag=1) -> andi./bne/li r11,0/cmpwi/beq exact;
//    ternary folds to xoris class and never matches.
//  PROVEN: li r18,0 dead-init must precede bl GetChecksum_3.
//  NEW DATapoint (doc-28): ngccc DOES emit its own CR-save machinery from
//    plain C here (mfcr r28/r30 + mtcrf 0x80,r30 for the FOV cr0 restore!)
//    but homes differ from want's r12-entry-save/r22-snapshot and it places
//    saves lazily before first use instead of eagerly in the prologue.
//  W1 remaining: force eager entry mfcr r12 + cr2/3/4 colors to match
//    (cr3=mode==2 first compare @BBC78). Try: make a mode-field test live
//    BEFORE fn_800144C8() so GCC allocates callee-saved CR at entry.
//  W2 scale: six ~230-insn transform runs + PS webs scheduler-exact =
//    multi-session grind (sibling fn_801BF5B8 parked same grounds).
//  W3 empty bdnz windows solvable via bdnz $ wedges (copy window frozen
//    verbatim above, raw words 0x801BBBE0-60 incl. self-targeting bdnz).
// =============================================================================
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// FLAG: -mps-float -Os -fno-expensive-optimizations
void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_80024610(Unk_DF2324A8 *);
void fn_801BF230(Unk_FFAD6788 *);
void fn_801BECBC(Unk_C7387A53 *);
void *fn_80144CB0(void);
void fn_801BB4A0(void *, f32);
void fn_8010794C(Unk_C7387A53 *);
void fn_80107A80(Unk_C5652918 *, s32, s32);
s32 fn_80108094(Unk_E9DCA07D *, void *, void *, s32);
void fn_80003830(Unk_DB0E2BAB *, f32, f32, f32);
void fn_80007BFC(s32, void *, void *);
s32 Script_GetInteger(s32, s32);
void fn_801BF080(Unk_1FAB9257 *, f32 *, f32 *);
void fn_801BEE7C(CStruct *, Unk_F947A964 *, s32);
void fn_801BED44(Unk_31DE137E *, CStruct *, CStruct *);
void *GetChecksum_3(Unk_6A70655D *, s32);
f32 fn_800144C8(void);
void *fn_80003EB0(Unk_DB0E2BAB *, f32);
f32 fn_801FF554(f32, f32);
void fn_800086B0(void *, void *);
f32 atan2f(f32, f32);
void fn_800B69A0(void *, void *);
void fn_800B6A88(void *, CStruct *, CStruct *);
void fn_801FF57C(void *, void *, void *, s32, s32);
extern f32 lbl_802AC3B4, lbl_802AC3B8, lbl_802AC3BC, lbl_802AC3C0;
extern f32 lbl_802AC3C4, lbl_802AC3C8, lbl_802AC3CC, lbl_802AC3D0;
extern f32 lbl_802AC3D4, lbl_802AC3D8, lbl_802AC3DC, lbl_802AC3E0;
extern f32 lbl_802AC3E4, lbl_802AC3E8, lbl_802AC3EC, lbl_802AC3F0;
extern f32 lbl_802AC3F4, lbl_802AC3F8, lbl_802AC3FC;
extern __ps_t lbl_802AC368;
#define HASH_CAMSTATE QB_SKATERCOREPHYSICS
#define HASH_CAMCFG QB_SKATERBALANCETRICK
#define HASH_BITIDX QB_FLAG_SKATER_LIPTRICK_CAM_REVERSED
typedef union { __ps_t p; f32 w[2]; } S;
void fn_801BBAE0(Unk_5B483C70 *arg0) {
    volatile S V[110]; /* 0x388-byte locals region */
    register s32 flag18 __asm__("r18");
    register void *camcfg __asm__("r20");
    char *const fp = (char *)&V[0];
    Unk_E722A5F0 *cs;
    s32 mode;
    s32 delta19;
    f32 time_f29;
    if (*((s32 *)&arg0->unk0x17C) == NULL) {
        return;
    }
    cs = *((void * *)&arg0->unk0x184);
    if (cs != NULL && *(s32 *)(cs->unk0x38 + 0x188) != 0) {
        ((Unk_31DE137E *)arg0->unk0xC)->unk0x114 |= 1;
        return;
    }
    flag18 = 0;
    camcfg = GetChecksum_3(arg0->unk0xC, QB_CAMERA);
    {
        s32 r11 = 1;
        if ((*(volatile s32 *)((char *)arg0->unk0x17C + 0x114) & 8) == 0) {
            r11 = 0;
        }
        if (r11 != 0) {
            flag18 = 1;
        }
    }
    if (flag18 != 0) {
        arg0->unk0x30 = 3;
    }
    {
        s32 n = arg0->unk0x30;
        if (n > 0) {
            arg0->unk0x30 = n - 1;
            flag18 = 1;
        }
    }
    time_f29 = fn_800144C8();
    fn_801BF230(arg0);
    fn_80024610(((Unk_31DE137E *)camcfg)->unk0x1C);
    {
        /* COPY WINDOW (frozen verbatim, raw words 0x801BBBE0-0x801BBC60):
           pair copies arg0+0x48..0x6F -> cam+0x78..0x9F; sp8 vec =
           {cam->98, cam->9C, cam->A0, 1.0f}; base-ptr setups r15=&sp8,
           r23=&sp28, r29=&sp18, r21=&spB8, r17=&sp268, r16=&sp26C,
           r28=cam+0x78, r9=*(arg0+0x180), r30=mode; empty bdnz spin. */
        register void *w_arg0 __asm__("r31");
        register char *w_cam __asm__("r9");
        register char *w_pg __asm__("r10");
        register char *w_mode __asm__("r30");
        w_arg0 = arg0;
        w_cam = (char *)((Unk_31DE137E *)camcfg)->unk0xC;
        w_pg = (char *)0x802A0000;
        __asm__ __volatile__(
            ".long 0xE01F0048\n\t"
            ".long 0x39610008\n\t"
            ".long 0x3B890078\n\t"
            ".long 0x38000004\n\t"
            ".long 0xF0090078\n\t"
            ".long 0x7C0903A6\n\t"
            ".long 0x3AE10028\n\t"
            ".long 0x3BA10018\n\t"
            ".long 0xE07F0050\n\t"
            ".long 0x7D6F5B78\n\t"
            ".long 0x3AA100B8\n\t"
            ".long 0x3A210268\n\t"
            ".long 0xF0690080\n\t"
            ".long 0x3A01026C\n\t"
            ".long 0xE17F0058\n\t"
            ".long 0xF1690088\n\t"
            ".long 0xE19F0060\n\t"
            ".long 0xF1890090\n\t"
            ".long 0xE1BF0068\n\t"
            ".long 0xF1A90098\n\t"
            ".long 0xE01F0070\n\t"
            ".long 0xC1A90098\n\t"
            ".long 0xF00900A0\n\t"
            ".long 0xC009009C\n\t"
            ".long 0xC16900A0\n\t"
            ".long 0xC18AC3B4\n\t"
            ".long 0xD1A10008\n\t"
            ".long 0xD00B0004\n\t"
            ".long 0xD16B0008\n\t"
            ".long 0xD18B000C\n\t"
            ".long 0x813F0180\n\t"
            ".long 0x83C9001C\n\t"
            "bdnz $"
            : "=r"(w_mode)
            : "r"(w_arg0), "r"(w_cam), "r"(w_pg)
            : "r0", "ctr", "memory", "fr0", "fr3", "fr11", "fr12", "fr13",
              "r11", "r15", "r16", "r17", "r21", "r23", "r28", "r29");
        mode = ((Unk_31DE137E *)arg0->unk0x180)->unk0x1C;
    }
    cs = GetChecksum_3(arg0->unk0x17C, HASH_CAMSTATE);
    delta19 = 0;
    if (!(mode == 2) && cs != NULL && cs->unk0x33C != 0) {
        int k;
        for (k = 0; k < 8; k++) {
            *(__ps_t *)((char *)fp + 0x18 + 8 * k) =
                *(__ps_t *)((char *)arg0 + 0x80 + 8 * k);
        }
        if (!(mode == 2)) {
            void *src;
            src = (((Unk_9994C3F5 *)arg0->unk0x17C)->unk0xC8 != 0)
                      ? (char *)fn_80144CB0() + 0x20
                      : (char *)arg0->unk0x17C + 0xF0;
            {
                /* want: psq_l p1; psq_st -> arg0+192; stfs 0.0 -> +196;
                   psq p2 -> arg0+200 */
                __ps_t p1 = *(__ps_t *)src;
                ((Unk_4169B2AE *)arg0)->unk0xC0 = p1;
                arg0->unk0xC4 = lbl_802AC3B8;
                ((Unk_4169B2AE *)arg0)->unk0xC8 = ((Unk_EA529D06 *)src)->unk0x8;
            }
            /* web A: lensq = sum(p1*p1 + merge00(p2*p1, tbl)); if > 0:
               rsqrte -> normalize p1 -> arg0+192, p2 -> arg0+200 */
            {
                __ps_t p1 = *(__ps_t *)src;
                __ps_t p2 = ((Unk_EA529D06 *)src)->unk0x8;
                __ps_t tbl = lbl_802AC368;
                __ps_t t = __builtin_ps_mul(p2, p1);
                t = __builtin_ps_merge00(t, tbl);
                t = __builtin_ps_madd(p1, p1, t);
                t = __builtin_ps_sum0(t, t, t);
                V[13].p = t;
                if (V[13].w[1] > lbl_802AC3B8) {
                    __ps_t inv = __builtin_ps_rsqrte(t);
                    __ps_t n1;
                    V[13].p = inv;
                    n1 = __builtin_ps_muls0(p1, inv);
                    ((Unk_4169B2AE *)arg0)->unk0xC0 = n1;
                    ((Unk_1D69B796 *)fp)->unk0x74 = lbl_802AC3B4;
                    n1 = __builtin_ps_mul(p2, inv);
                    ((Unk_4169B2AE *)arg0)->unk0xC8 = n1;
                }
            }
            /* web B: same shape onto sp88/sp90 with sp92 = 0.0f */
            {
                __ps_t p1 = *(__ps_t *)src;
                __ps_t p2 = ((Unk_EA529D06 *)src)->unk0x8;
                ((Unk_5F85C510 *)fp)->unk0x58 = p1;
                ((Unk_5F85C510 *)fp)->unk0x60 = p2;
                ((Unk_1D69B796 *)fp)->unk0x5C = lbl_802AC3B8;
                {
                    __ps_t q1 = ((Unk_5F85C510 *)fp)->unk0x58;
                    __ps_t tbl = lbl_802AC368;
                    __ps_t t = __builtin_ps_mul(p2, p1);
                    t = __builtin_ps_merge00(t, tbl);
                    t = __builtin_ps_madd(q1, q1, t);
                    t = __builtin_ps_sum0(t, t, t);
                    V[13].p = t;
                    if (V[13].w[1] > lbl_802AC3B8) {
                        __ps_t inv = __builtin_ps_rsqrte(t);
                        __ps_t n1 = __builtin_ps_muls0(q1, inv);
                        __ps_t n2 = __builtin_ps_mul(p2, inv);
                        V[13].p = inv;
                        ((Unk_5F85C510 *)fp)->unk0x58 = n1;
                        ((Unk_5F85C510 *)fp)->unk0x60 = n2;
                    }
                }
            }
            {
                f32 zero = lbl_802AC3B8;
                f32 two_pi = lbl_802AC3BC;
                f32 eps = lbl_802AC3C0;
                f32 w0 = atan2f(*((f32 *)&((Unk_4169B2AE *)arg0)->unk0xC0),
                                     *((f32 *)&((Unk_4169B2AE *)arg0)->unk0xC8));
                f32 w1 = atan2f(*((f32 *)&((Unk_5F85C510 *)fp)->unk0x58),
                                     *((f32 *)&((Unk_5F85C510 *)fp)->unk0x60));
                f32 d;
                if (w0 < zero) {
                    w0 += two_pi;
                }
                if (w1 < zero) {
                    w1 += two_pi;
                }
                d = w1 - w0;
                if (d < 0.0f) {
                    d = -d;
                }
                if (d > eps) {
                    delta19 = 1;
                }
            }
        }
        arg0->unk0x78 += 1;
    } else {
        int k;
        arg0->unk0x78 = 0;
        if (((Unk_9994C3F5 *)arg0->unk0x17C)->unk0xC8 != 0) {
            void *rr = fn_80144CB0();
            for (k = 0; k < 8; k++) {
                *(__ps_t *)((char *)fp + 0x18 + 8 * k) =
                    *(__ps_t *)((char *)rr + 8 * k);
            }
        } else {
            for (k = 0; k < 8; k++) {
                *(__ps_t *)((char *)fp + 0x18 + 8 * k) =
                    *(__ps_t *)((char *)cs + 0xD0 + 8 * k);
            }
        }
        for (k = 0; k < 8; k++) {
            *(__ps_t *)((char *)arg0 + 0x80 + 8 * k) =
                *(__ps_t *)((char *)fp + 0x18 + 8 * k);
        }
    }
    /* FOV block */
    {
        f32 f0 = lbl_802AC3B8;
        if (mode == 4 && ((Unk_9994C3F5 *)arg0->unk0x17C)->unk0xC8 != 0) {
            void *cf = GetChecksum_3(arg0->unk0x17C, HASH_CAMCFG);
            f0 = *((f32 *)&((Unk_FFAD6788 *)cf)->unk0xCC) * lbl_802AC3C4;
        }
        {
            f32 fov = arg0->unk0x134;
            if (f0 != fov) {
                /* want gates the lerp on the RESTORED cr0 (countdown flag) */
                if (flag18 != 0) {
                    f0 = (f0 - fov) * arg0->unk0x100 + fov;
                }
                arg0->unk0x134 = f0;
            }
        }
    }
    /* sp88/sp96 select + stage sp68.. + fn_801BECBC */
    {
        f32 z = lbl_802AC3B8;
        if (mode == 0) {
            ((Unk_5F85C510 *)fp)->unk0x58 = ((Unk_1D69B796 *)fp)->unk0x28;
            ((Unk_5F85C510 *)fp)->unk0x60 = ((Unk_1D69B796 *)fp)->unk0x30;
        } else {
            void *g180 = arg0->unk0x180;
            ((Unk_5F85C510 *)fp)->unk0x58 = ((Unk_073F5245 *)g180)->unk0x168;
            ((Unk_5F85C510 *)fp)->unk0x60 = ((Unk_073F5245 *)g180)->unk0x170;
        }
        {
            void *c17c = arg0->unk0x17C;
            ((Unk_1D69B796 *)fp)->unk0x68 = *((f32 *)&((Unk_FFAD6788 *)c17c)->unk0xB8);
            ((Unk_1D69B796 *)fp)->unk0x6C = z;
            ((Unk_1D69B796 *)fp)->unk0x70 = *((f32 *)&((Unk_FFAD6788 *)c17c)->unk0xC0);
            ((Unk_1D69B796 *)fp)->unk0x74 = lbl_802AC3B4;
        }
        fn_801BECBC(arg0);
    }
}
