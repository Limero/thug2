// PARKED 2026-10-05 (w_80124478): hand rewrite of fn_80124478 — body is
// SEMANTICALLY COMPLETE (was m2c DIFF 5.5%), still DIFF 20.1% masked.
//   measured: tools/want_got.py 0x80124478 -> 362/455 words differ (20.09%),
//   object 1812B vs want 1820B (2 words SHORT); official verdict DIFF.
//   first 7 instructions (frame + stfd f29/f30/f31 + stmw r16 + LR) are
//   byte-identical, and the mnemonic stream now matches want op-for-op over
//   almost the whole function; the residual is REGISTER ALLOCATION plus three
//   local scheduling differences (see RESIDUAL at the bottom).
// family=m2c range=0x80124478-0x80124B94 size=1820B
// extra_cflags: -Ilibs/dolphin/include
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// WHAT IS SOLVED (was wrong/absent in the m2c body):
//  * frame 0x2a0, f29/f30/f31 at 0x288/0x290/0x298, stmw r16 at 0x248 — all 16
//    callee-saved GPRs allocated; the FPR saves sit ABOVE the GPR area here, so
//    want_fpr_frame() returns None (no +8 dummy needed) and the default flag
//    set reaches it.  Local map: buf r1+0x08, ScreenDesc r1+0x108 (the 0x110
//    twin of matched fn_80019800/9B90/9958), sp218 r1+0x218, the two
//    fn_801224E8 out-params r1+0x21C/r1+0x220, int<->double temp r1+0x240;
//    0x224..0x23B is retail padding, reproduced with 3 f64 pads (see below).
//  * lbl_8029E3B0 is the STRING "movies/vid/" — copied as 3 word stores.
//  * lbl_8029E3C0 = 0.0, 0x8029E3D8 = 512.0f, 0x8029E3DC = 1.0f,
//    0x8029E3E0 = 1000.0; 0x8029E3C8 = 2^52 and 0x8029E3D0 = 2^52+2^31 are
//    the compiler's int->double BIAS constants (the `fsub f,f,bias` after each
//    `lfd` from the 0x240 temp).  They are NOT subtracted by the source, so
//    they are not referenced here — ngccc takes them from its own pool (the
//    instruction SHAPE `lis`+`lfd` matches want; the reloc masks hide it).
//  * the aspect/scale math: r23 = (s32)(sp220 * (r21/sp21C)) then
//    (s32)((f32)r23 * (512.0f/r21)).  sp21C/sp220/r21 are UNSIGNED (want uses
//    the unsigned magic 0x43300000, no `xoris`); r23 is signed, and the
//    `xoris rX,0x8000` at 0x8012474C is the signed-bias of (f64)r23, NOT a
//    negation (m2c read it as `-r23`).
//  * the timing divide is by 4000 (magic 0x10624DD3), unsigned.
//  * fn_80122554 is consumed as a DOUBLE (no frsp) => declared `double` here.
//  * lbl_80312434 is a u16[] indexed [0] | [6] (byte +0xC, not +6).
//  * AXRegisterCallback gets the fn_8011E8D0 SYMBOL (lis+addi, not ori).
//  * full control flow: the 4-way probe chain, the stream loop, the DVD-error
//    screen loop (fn_800181A4 poll + state-1/8/2 continue + the 5-case
//    Script_RunScript switch), the 0x1100 mask check, the r17/timing block and
//    the shared 5-call teardown.
//  * GQR1..4: SPR 0x392..0x395 = Gekko graphics-quantization registers, not
//    reachable from C (recipes §4c, src/wip/fn_80003300.c).  Kept as the same
//    12-instruction asm block the game's `main` uses (src/fn_80145BB4.c).
//
// RESIDUAL (all measured, none of it semantic):
//  1. Register allocation. Every value is 1-2 registers off.  The allocator's
//     4-value group is PERMUTED: got r20..r23 = {u16, cfg-base, value, mask}
//     vs want r20..r23 = {mask, u16, cfg-base, value}; arg0 lands in r30 (want
//     r29), &buf in r31 (want r30 + a copy in r28).  r17/r18/r19 and r24..r29
//     hold the same values in both.  Live ranges are equal, so this is GCC's
//     priority order, not a source difference I could find.
//  2. `li r0,0` missing at 0x801244D0: ngccc shares r16's zero with
//     `lbl_80300120 = 0` (`stw r16,0(r8)`) instead of rematerializing it.  Both
//     source orders of the store measured identical.
//  3. the trailing `b 0x80124AAC` after `fmr f29,f0` is missing: block layout
//     of the `if (r17)` arm is inverted (`beq <timing>` vs want `bne`).
//     Swapping the if/else arms measured WORSE (16.1%).
//  4. the float block hoists `frsp f12` early (separate f32 temps) where want
//     emits it just before `fmuls`; the single-expression form measured worse
//     (11.1%), and the `andc`-shaped mask test made no difference.
//
// RULED OUT (do not re-derive): `volatile double` frame pads (recipes §4c) —
//   the want's first stfd is at frame-0x18, not frame-8, so the FPR-frame
//   classifier correctly returns None and the frame is native; 1/2/3 pads all
//   land the same way.  The 0x224..0x23B hole is 3 f64 pads referenced by a
//   ZERO-CODE `__asm__("" :: "m"(..))` so they are allocated after the
//   address-taken out-params (volatile pads are allocated before them and push
//   sp21C/sp220 to 0x238/0x23c — measured).  The promoted twins
//   (src/fn_80019800.c, fn_80019958.c, fn_80019B90.c) spell the `set_blend_mode`
//   call as a 4-insn inline-asm wedge; it is NOT needed here — the plain
//   `set_blend_mode(0, 5, 0)` call is 0.2% behind and this function is parked
//   anyway, because ngccc CSEs retail's two separate `li r3,0` / `li r5,0` into
//   one register and neither spelling recovers all three.  The ONLY asm left in
//   this file is the Gekko SPE init below (mtspr 0x392..0x395), which has no C
//   spelling in this compiler and is the same house idiom as promoted
//   src/fn_80145BB4.c.
//   The 4 dead `mr rX,r9` copies at 0x801246C0..0x80124700 ARE reproduced
//   naturally by this float block (got emits 4 `mr rX,r10`), so they are not
//   a blocker.
#include "qb_constants.h"

/* The 0x110-byte screen descriptor every ScriptNgc_Set* passes to
   queue_front / Camera_orthographic / fn_8001737C / fn_800173CC /
   fn_80016A88 (identical to the matched fn_80019800/9B90/9958 twins). */
typedef struct ScreenDesc {
    char pad0[0x30];
    f32 sub0[3];
    f32 sub1[3];
    char pad48[0x60];
    void *unk0xA8;
    char padAC[0x64];
} ScreenDesc;

/* lbl_803613E4 holds a pointer to this (see fn_801224A8 / fn_801227CC). */
typedef struct DvdCfg {
    char pad0[4];
    u16 q;
    u16 r;
} DvdCfg;

/* r26 = 0x8037B5E8; fields at +0x184 (f32) and +0x1BC (s32). */
typedef struct DvdDbg {
    char pad0[0x184];
    f32 f184;
    char pad188[0x34];
    s32 f1BC;
} DvdDbg;

extern s32 lbl_80300120;
extern u16 lbl_80312434[0x30];
extern s32 lbl_80300125;
extern s32 lbl_80303140;
extern s32 lbl_80303144;
extern DvdCfg *lbl_803613E4;
extern u32 lbl_8039BE9C[2];
extern u32 lbl_8029E3B0[4];
extern f64 lbl_8029E3C0;
extern f32 lbl_8029E3D8;
extern f32 lbl_8029E3DC;
extern f64 lbl_8029E3E0;
extern char lbl_8037B5E8[];

s32 strlen(const char *);
s32 strncpy(char *, const char *, s32);
s32 fn_8001E17C(s32);
void StopMusic(void);
void fn_80261038(void *);
void fn_80261860(void);
void fn_80260B70(void);
void fn_80263488(void);
void fn_802634C0(void);
void fn_80278B7C(void *);
s32 DVDGetDriveStatus(void);
void AXSetVoiceState(s32, s32);
void GXSetZMode(s32, s32, s32);
void GXSetColorUpdate(s32);
void GXSetAlphaUpdate(s32);
void queue_front(ScreenDesc *);
void Camera_orthographic(ScreenDesc *, s32, s32, s32, s32);
void fn_80016A88(ScreenDesc *, s32);
void fn_8001737C(ScreenDesc *);
void fn_800173CC(ScreenDesc *);
void fn_80016C70(void);
void fn_80017DA4(void);
void fn_80017E20(s32);
void fn_80018064(s32 *);
void fn_800181A4(s32, s32);
void fn_8001B8B0(void);
void fn_8001B8C0(void);
void fn_8001B8D0(void);
void fn_8001B9C8(void);
void fn_8001CEAC(void);
void set_blend_mode(s32, s32, u8);
void fn_80131008(s32, s32, s32, s32, s32);
void fn_80121518(s32, s32, s32);
s32 fn_80121798(void);
s32 fn_80121900(s32);
s32 fn_80121AD4(s32);
s32 fn_80121D80(char *, s32);
s32 fn_80121CD0(void);
s32 fn_8012227C(void);
void fn_80121874(void);
void fn_80121A78(void);
void fn_801232EC(void);
s32 fn_80122304(void);
void fn_80122450(s32, s32, s32, s32, s32);
void fn_801224A8(DvdCfg *, s32);
void fn_801224E8(u32 *, u32 *);
double fn_80122554(void);
s32 fn_80122C40(void);
void fn_80124110(void);
u32 OSGetTick(void);
void fn_80122560(void);
void fn_80269EC0(s32, s32, s32, s32);
void fn_80269EF8(s32, s32, s32, s32);
void fn_8011E8D0(void);
void fn_801225F8(void);
void fn_80122648(void);

void fn_80124478(char *arg0) {
    char buf[256];
    ScreenDesc sp108;
    volatile s32 sp218;
    u32 sp21C;
    u32 sp220;
    f64 _d1;
    f64 _d2;
    f64 _d3;
    DvdDbg *dbg;
    s32 len;
    s32 pos;
    s32 n;
    s32 state;
    s32 r16;
    s32 r17;
    s32 r20;
    u32 r21;
    s32 r23;
    s32 r24;
    u32 r28;
    f64 f29;
    f64 f30;
    f32 t_h;
    f32 t_r;
    f32 t_w;
    f32 t_s;
    f64 f0;
    f64 f13;
    s32 m;
    s32 diff;

    r16 = 0;
    r17 = 1;
    r24 = 0;
    fn_8001E17C(1);
    fn_80261038(lbl_803613E4);
    fn_80261860();
    fn_80260B70();
    lbl_80300120 = 0;
    r20 = lbl_80312434[0] | lbl_80312434[6];
    StopMusic();
    f29 = lbl_8029E3C0;
    f30 = f29;
    __asm__ volatile("li 3,4\n\toris 3,3,4\n\tmtspr 0x392,3\n\t"
                     "li 3,5\n\toris 3,3,5\n\tmtspr 0x393,3\n\t"
                     "li 3,6\n\toris 3,3,6\n\tmtspr 0x394,3\n\t"
                     "li 3,7\n\toris 3,3,7\n\tmtspr 0x395,3\n\t"
                     ::: "r3");
    fn_80124110();
    fn_80263488();
    lbl_80303140 = QB_UNKNOWN_0xE0000000;
    fn_80121518((s32)fn_80122560, (s32)fn_801225F8, (s32)fn_80122648);
    *(u32 *)&buf[0] = lbl_8029E3B0[0];
    *(u32 *)&buf[4] = lbl_8029E3B0[1];
    *(u32 *)&buf[8] = lbl_8029E3B0[2];
    memset(&buf[12], 0, 0xF4);
    len = strlen(arg0);
    pos = len;
    if (pos != 0) {
        if (arg0[pos] == '\\') {
            pos++;
        } else {
            for (;;) {
                pos--;
                if (pos == 0) {
                    break;
                }
                if (arg0[pos] == '\\') {
                    pos++;
                    break;
                }
            }
        }
    }
    strncpy(&buf[11], &arg0[pos], len - pos);
    n = strlen(buf);
    buf[n] = '.';
    buf[n + 1] = 'v';
    buf[n + 2] = 'i';
    buf[n + 3] = 'd';
    buf[n + 4] = 0;
    if (fn_80121D80(buf, 0) != 0) {
        if (fn_80121798() == 0) {
            fn_80121CD0();
            fn_8012227C();
        } else if (fn_80121900(1) == 0) {
            fn_80121CD0();
            fn_8012227C();
            fn_80121874();
        } else if (fn_80122C40() != 0) {
            fn_80121CD0();
            fn_8012227C();
            fn_80121874();
            fn_80121A78();
        } else {
            fn_80121AD4(0);
            dbg = (DvdDbg *)lbl_8037B5E8;
            fn_801224E8(&sp21C, &sp220);
            r21 = lbl_803613E4->q;
            __asm__ volatile("" :: "m"(_d1), "m"(_d2), "m"(_d3));
            t_h = (f32)sp220;
            t_r = (f32)r21;
            t_s = lbl_8029E3D8 / t_r;
            t_w = (f32)sp21C;
            r23 = (s32)(t_h * (t_r / t_w));
            r23 = (s32)((f32)r23 * t_s);
            for (;;) {
                r28 = OSGetTick();
                fn_8001E17C(0);
                fn_80017DA4();
                fn_8001B8D0();
                if (fn_80122304() == 0) {
                    break;
                }
                if (r16 == 0) {
                    fn_80122450((s32)lbl_803613E4, 0, 0, r21, r23);
                } else {
                    fn_801224A8(lbl_803613E4, lbl_80303144);
                }
                state = DVDGetDriveStatus();
                if ((u32)state > 1 && state != 10 && state != 8 && state != 2) {
                    fn_80261038(lbl_803613E4);
                    AXSetVoiceState(lbl_8039BE9C[0], 0);
                    AXSetVoiceState(lbl_8039BE9C[1], 0);
                    fn_8001CEAC();
                    GXSetZMode(1, 3, 1);
                    GXSetColorUpdate(1);
                    GXSetAlphaUpdate(1);
                    dbg->f184 = lbl_8029E3DC;
                    for (;;) {
                        state = DVDGetDriveStatus();
                        fn_800181A4(0, 0);
                        if (state == 0 || state == 10) {
                            break;
                        }
                        if (state != 1) {
                            if (state != 8 && state != 2) {
                                fn_80017DA4();
                                fn_8001B8D0();
                                queue_front(&sp108);
                                Camera_orthographic(&sp108, 0, 0, 0x280, 0x1C0);
                                fn_80016C70();
                                fn_8001B8B0();
                                fn_8001737C(&sp108);
                                GXSetZMode(0, 7, 1);
                                                                    set_blend_mode(0, 5, 0);
                                switch (state) {
                                case 5:
                                    fn_80131008(QB_NGC_DVD_COVER_OPEN, 0, 0, 0, 0);
                                    dbg->f1BC = 0;
                                    break;
                                case 4:
                                    fn_80131008(QB_NGC_DVD_NO_DISK, 0, 0, 0, 0);
                                    dbg->f1BC = 0;
                                    break;
                                case 6:
                                    fn_80131008(QB_NGC_DVD_WRONG_DISK, 0, 0, 0, 0);
                                    dbg->f1BC = 0;
                                    break;
                                case 0xB:
                                    fn_80131008(QB_NGC_DVD_RETRY, 0, 0, 0, 0);
                                    break;
                                case -1:
                                    fn_80131008(QB_NGC_DVD_FATAL, 0, 0, 0, 0);
                                    dbg->f1BC = 1;
                                    break;
                                }
                                sp218 = lbl_80300125;
                                fn_80018064(&sp218);
                                fn_800173CC(&sp108);
                                fn_8001B8C0();
                                fn_8001B9C8();
                                fn_80017E20(1);
                                fn_80016A88(&sp108, 2);
                            }
                        }
                    }
                    fn_80124110();
                    AXSetVoiceState(lbl_8039BE9C[0], 1);
                    AXSetVoiceState(lbl_8039BE9C[1], 1);
                    fn_80261038(lbl_803613E4);
                    r28 = OSGetTick();
                }
                fn_8001B9C8();
                fn_80017E20(1);
                m = lbl_80312434[0] | lbl_80312434[6];
                diff = m & ~r20;
                if ((diff & 0x1100) != 0) {
                    break;
                }
                r20 = m;
                if (r17 != 0) {
                    r17 = 0;
                } else {
                    f30 += lbl_8029E3E0 / fn_80122554();
                    do {
                        f13 = (f64)(OSGetTick() - r28) /
                              (f64)(*(u32 *)0x800000F8 / 4000);
                        f0 = f29 + f13;
                    } while (f0 < f30);
                    f29 = f0;
                }
            }
            fn_80121CD0();
            fn_8012227C();
            fn_80121874();
            fn_80121A78();
            fn_801232EC();
        }
    }
    sp218 = 0;
    fn_80018064(&sp218);
    fn_80269EC0(6, 7, 6, 7);
    fn_80269EF8(0xE, 7, 0xE, 7);
    fn_8001CEAC();
    GXSetZMode(1, 3, 1);
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(1);
    fn_80278B7C(fn_8011E8D0);
    fn_802634C0();
    fn_8001E17C(1);
    fn_80261038(lbl_803613E4);
    fn_80261860();
    fn_80260B70();
    fn_8001E17C(0);
}