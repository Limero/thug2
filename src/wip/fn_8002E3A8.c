// WIP DRAFT (non-matching)
// family=m2c range=0x8002E3A8-0x8002F178 size=3536B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-05 (switch-rebuild): best measured 24.91% (score_wip,
// got 3404B vs want 3536B); the previous m2c if/else body scored 5.55%.
// WHAT WAS FIXED (all verified against the retail bytes):
//   * retail is a real `switch (arg1)` over 28 hashed QB opcodes, not m2c's
//     nested if/else chain.  Rewriting it as a switch makes ngccc emit the
//     *identical* binary-search dispatch: all 142 words of the prologue +
//     decision tree now match (modulo the frame offsets, see below).
//   * the case-value set / grouping was recovered from the retail tree:
//     QB_OBJ_PLAYANIM+0xB1E7291, QB_OBJ_ANIMCOMPLETE+QB_ANIMFINISHED,
//     QB_ANIMEQUALS+QB_OBJ_ANIMEQUALS, and the six-way group
//     {QB_UPDATEDIFFERENCEANIM, QB_INCREMENTPARTIALANIMTIME,
//      QB_ADDANIMCONTROLLER, QB_SETPARTIALANIMSPEED,
//      QB_GETPARTIALANIMPARAMS, QB_REVERSEPARTIALANIMDIRECTION}.
//     QB_OBJ_ANIMCOMPLETE was missing from the m2c body entirely.
//   * fn_80030B1C takes (obj, arg2, arg3, <float>) - m2c's 4th int arg
//     0x80290000 was the `lis` base of the lfs, not a parameter.
//   * fn_8002FB24 / fn_8002FBA8 take ONE arg, not three.
//   * fn_8002F4E0 takes THREE args (obj, node, arg3->unk0x18).
//   * fn_8012EFCC takes 2 args (track, 0), fn_8012F024 takes 1.
//   * fn_80032088 must be prototyped as returning void* (retail keeps its
//     r3 and feeds it straight into fn_8012ED98); the promoted
//     src/fn_80032088.c declares it void.
//   * every callee got a real prototype (the m2c body had none, so ngccc
//     emitted `crclr cr1eq` before many bl's).
//   * local structs A2E3A8/N2E3A8/V2E3A8/T2E3A8/S2E3A8 give the right field
//     widths (lha 0x30 vtable adjust, lha 0x18 wobble adjust, f32 0x24).
//   * hoisting lbl_8029197C[0] into a local before the 0x4FAF61A9 loop is
//     what makes ngccc allocate f31 (`stfd f31` / frame 0x80).
//   * QB_OBJ_SETANIMCYCLEMODE: `if (c != 0) f(a,0,1); else f(a,1,1);`
//     reproduces retail's `cmpwi r3,0 / beq`; every value-context spelling
//     of `ContainsFlag(...) == 0` becomes `subfic/adde` (<= 0) instead.
// RESIDUAL:
//   * FRAME / LOCAL AREA (blocks everything else).  Retail's save area
//     starts at 0x64 => local_alloc_size 0x54, i.e. TWENTY-ONE 4-byte stack
//     slots, of which only nineteen (0x8..0x50) are ever touched; the top
//     two are never read or written in the retail bytes.  This body only
//     accounts for nineteen, so the frame came out 0x78.  The only lever
//     found that grows the local area is a `volatile` local, and ngccc
//     always places volatile locals at the BOTTOM of the local area (0x8),
//     which shifts every named local up by 8 instead of padding the top.
//     `_pad0/_pad1` below are that placeholder: they fix the frame (0x80,
//     stmw r27/0x64, stfd f31/0x78, stw r0/0x84) but cost an 8-byte shift in
//     the named-local offsets (sp8 lands at 0x10 instead of 0x8).  Remove
//     them once the two missing locals are identified - the local offsets
//     then become correct on their own.
//   * With the placeholder in place the case bodies still differ.  Measured
//     per body (stack offsets normalised):
//       - 0xE638 QB_OBJ_SETANIMCYCLEMODE and 0xE668 QB_OBJ_PLAYANIM match
//         except for register choice in the `p[1]==-1 / p-4` node idiom
//         (retail r9/r11, got r11/r30) - needs register pins.
//       - 0xE6F0: retail keeps the shared `!!v` tail inline right after the
//         first user; ngccc tail-merged it to the function epilogue.
//       - 0xE79C (0x4FAF61A9 loop): retail re-materialises `addi r4/r1,0x10`,
//         `r5,0x14`, `r6,0x18` every iteration; ngccc hoists them into
//         r28/r29/r31 (lower register pressure than the original).
//       - QB_FRAMEIS and QB_WAITANIM carry hand-transcribed boolean
//         reconstructions of m2c's `0 &&` garbage and do NOT match yet
//         (the `cror`/`mfcr`/`rlwinm` sequences in WAITANIM are still wrong).
//       - QB_REPLACEANIM's blend-channel walk and QB_OBJ_FLIP's counting walk
//         are not verified byte-for-byte.
// RULED OUT: nested if/else (the m2c shape) can never match - the retail
// tree is a switch binary search; `ContainsFlag()==0` as a value (always
// `<=0`); non-volatile or single-s32 pads (no stack slot at all).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern float lbl_80291974[1];
extern float lbl_80291978[1];
extern float lbl_8029197C[1];
extern float lbl_80291980[1];
extern float lbl_80291984[1];

s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
void AddChecksum(CStruct *, s32, s32);
void fn_8012772C(void *, s32, f32);
void fn_8012F024(void *);
void fn_8012EFCC(void *, s32);
void *fn_8012ED98(void *);
void *fn_80032088(s32);
void fn_80030B1C(void *, void *, void *, f32);
f32 fn_80030A64(void *, s32, s32);
void fn_80030ADC(void *, s32);
void fn_80030580(void *, s32, s32);
void fn_8002DDAC(void *, f32 *, f32 *, f32 *);
void fn_8002E34C(void *);
void fn_8002F4E0(void *, void *, void *);
s32 fn_8002F5AC(void *, void *, void *);
f32 fn_8002F700(void *, s32);
s32 fn_8002F724(void *, s32);
s32 fn_8002FBA8(void *);
s32 fn_8002FB24(void *);
void fn_8002FEB8(void *);
void fn_8002FEF0(void *, s32);

typedef struct {
    char pad0x0[0x18];
    s16 unk0x18;
    char pad0x1A[2];
    s32 unk0x1C;
    char pad0x20[0x10];
    s16 unk0x30;
    char pad0x32[2];
    s32 unk0x34;
} V2E3A8;

typedef struct {
    char pad0x0[0x10];
    s32 unk0x10;
    char pad0x14[4];
    V2E3A8 *unk0x18;
    char pad0x1C[0xC];
    f32 unk0x28;
    char pad0x2C[4];
    s32 unk0x30;
} N2E3A8;

typedef struct {
    char pad0x0[0x14];
    void *unk0x14;
} T2E3A8;

typedef struct {
    char pad0x0[0x18];
    s32 *unk0x18;
} S2E3A8;

typedef struct {
    char pad0x0[0x18];
    s32 unk0x18;
    char pad0x1C[8];
    s32 unk0x24;
    char pad0x28[0x24];
    s32 unk0x4C;
    f32 unk0x50;
    char pad0x54[0x10];
    u32 unk0x64;
    char pad0x68[4];
    f32 unk0x6C;
    s32 unk0x70;
    f32 unk0x74;
    T2E3A8 *unk0x78;
} A2E3A8;

s32 fn_8002E3A8(A2E3A8 *arg0, u32 arg1, CStruct *arg2, S2E3A8 *arg3) {
    volatile s32 _pad0;
    volatile s32 _pad1;
    s32 sp8;
    f32 spC;
    f32 sp10;
    f32 sp14;
    f32 sp18;
    s32 sp1C;
    f32 sp20;
    f32 sp24;
    f32 sp28;
    f32 sp2C;
    f32 sp30;
    f32 sp34;
    f32 sp38;
    f32 sp3C;
    s32 sp40;
    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    f32 temp_f0;
    f32 temp_f31;
    f32 temp_f12;
    f32 temp_f13;
    char *p;
    N2E3A8 *n;
    s32 v;
    s32 ret;

    switch (arg1) {
    case QB_OBJ_ENABLEANIMBLENDING:
        GetInteger(arg2, QB_ENABLED, &sp8, 1);
        fn_80030ADC(arg0, sp8 != 0);
        break;
    case QB_OBJ_SETANIMCYCLEMODE:
        if (ContainsFlag(arg2, QB_OFF) != 0) {
            fn_80030580(arg0, 0, 1);
        } else {
            fn_80030580(arg0, 1, 1);
        }
        break;
    case QB_OBJ_PLAYANIM:
    case 0xB1E7291:
        fn_80030B1C(arg0, arg2, arg3, lbl_80291974[0]);
        p = (char *)arg0->unk0x24;
        if (*(s32 *)(p + 4) == -1) {
            p = 0;
        }
        n = (p != 0) ? (N2E3A8 *)(p - 4) : 0;
        if (n != 0 && n->unk0x30 == 3) {
            V2E3A8 *v2 = *(V2E3A8 **)((char *)arg0->unk0x78 + 8);
            ((void (*)(void *, s32, CStruct *, void *))v2->unk0x1C)((char *)arg0->unk0x78 + v2->unk0x18, QB_SETWOBBLEDETAILS, arg2, arg3);
        }
        break;
    case QB_OBJ_ANIMCOMPLETE:
    case QB_ANIMFINISHED:
        if (fn_8002FB24(arg0) != 0) {
            return 1;
        }
        return 0;
    case QB_ANIMEQUALS:
    case QB_OBJ_ANIMEQUALS:
        if (fn_8002F5AC(arg0, arg2, arg3) != 0) {
            return 1;
        }
        return 0;
    case QB_OBJ_GETANIMSPEED:
        {
            s32 *t = arg3->unk0x18;
            fn_8012772C(t, QB_SPEED, fn_80030A64(arg0, arg2, arg3));
        }
        break;
    case QB_UNKNOWN_0x4FAF61A9:
        spC = lbl_80291978[0];
        GetFloat(arg2, QB_CYCLE_LENGTH, &spC, 1);
        p = (char *)arg0->unk0x24;
        if (*(s32 *)(p + 4) == -1) {
            p = 0;
        }
        n = (p != 0) ? (N2E3A8 *)(p - 4) : 0;
        if (n != 0) {
            temp_f31 = lbl_8029197C[0];
            do {
                N2E3A8 *cur = (N2E3A8 *)((char *)n + 4);
                fn_8002DDAC(cur, &sp10, &sp14, &sp18);
                temp_f12 = sp18;
                if (sp10 > sp18) {
                    temp_f12 = sp10;
                }
                cur->unk0x28 = (temp_f12 / spC) / temp_f31;
                p = (char *)cur->unk0x10;
                if (*(s32 *)(p + 4) == -1) {
                    p = 0;
                }
                n = (p != 0) ? (N2E3A8 *)(p - 4) : 0;
            } while (n != 0);
        }
        break;
    case QB_BLENDPERIODOUT:
        GetFloat(arg2, 0, &arg0->unk0x50, 0);
        arg0->unk0x4C = 1;
        break;
    case QB_LOOPINGANIM:
        if (fn_8002FBA8(arg0) != 0) {
            return 1;
        }
        return 0;
    case QB_GETANIMLENGTH:
        sp1C = 0;
        GetChecksum_2(arg2, QB_ANIM, &sp1C, 0);
        if (fn_8002F724(arg0, sp1C) != 0) {
            s32 *t = arg3->unk0x18;
            temp_f0 = fn_8002F700(arg0, sp1C);
            fn_8012772C(t, QB_LENGTH, temp_f0 < 0.0f ? -temp_f0 : temp_f0);
        }
        break;
    case QB_FRAMEIS:
        sp20 = 0.0f;
        sp24 = 0.0f;
        sp28 = 0.0f;
        p = (char *)arg0->unk0x24;
        if (*(s32 *)(p + 4) == -1) {
            p = 0;
        }
        n = (p != 0) ? (N2E3A8 *)(p - 4) : 0;
        if (n != 0) {
            p = (char *)arg0->unk0x24;
            if (*(s32 *)(p + 4) == -1) {
                p = 0;
            }
            n = (p != 0) ? (N2E3A8 *)(p - 4) : 0;
            fn_8002DDAC((char *)n + 4, &sp20, &sp24, &sp28);
        }
        sp2C = 0.0f;
        GetFloat(arg2, 0, &sp2C, 0);
        temp_f12 = sp2C / lbl_8029197C[0];
        temp_f13 = sp24 - sp20;
        sp2C = temp_f12;
        temp_f0 = arg0->unk0x6C - sp20;
        if (temp_f12 == temp_f13 || (temp_f0 < temp_f12 && temp_f12 < temp_f13)
            || (temp_f13 < temp_f0 && temp_f0 < temp_f12)
            || (temp_f12 < temp_f13 && temp_f13 < temp_f0)) {
            return 1;
        }
        return 0;
    case QB_WAITANIM:
        sp30 = 0.0f;
        sp34 = 0.0f;
        sp38 = 0.0f;
        p = (char *)arg0->unk0x24;
        if (*(s32 *)(p + 4) == -1) {
            p = 0;
        }
        n = (p != 0) ? (N2E3A8 *)(p - 4) : 0;
        if (n != 0) {
            p = (char *)arg0->unk0x24;
            if (*(s32 *)(p + 4) == -1) {
                p = 0;
            }
            n = (p != 0) ? (N2E3A8 *)(p - 4) : 0;
            fn_8002DDAC((char *)n + 4, &sp30, &sp34, &sp38);
        }
        sp3C = 0.0f;
        GetFloat(arg2, 0, &sp3C, 0);
        if (ContainsFlag(arg2, QB_FRAME) != 0 || ContainsFlag(arg2, QB_FRAMES) != 0) {
            temp_f0 = sp3C / lbl_8029197C[0];
        } else if (ContainsFlag(arg2, QB_PERCENT) != 0) {
            temp_f0 = sp30 + (sp38 - sp30) * sp3C / lbl_80291980[0];
        } else if (ContainsFlag(arg2, QB_SECOND) != 0 || ContainsFlag(arg2, QB_SECONDS) != 0) {
            temp_f0 = sp3C;
        } else {
            temp_f0 = sp3C / lbl_80291984[0];
        }
        sp3C = temp_f0;
        if (ContainsFlag(arg2, QB_RELATIVE) != 0) {
            if (sp30 > sp38) {
                temp_f0 = sp34 - sp3C;
            } else {
                temp_f0 = sp34 + sp3C;
            }
        } else if (ContainsFlag(arg2, QB_FROMEND) != 0) {
            if (sp30 > sp38) {
                temp_f0 = sp30 + sp3C;
            } else {
                temp_f0 = sp38 - sp3C;
            }
        } else {
            temp_f0 = sp3C;
        }
        arg0->unk0x74 = temp_f0;
        if (sp30 <= sp38) {
            if (arg0->unk0x74 > sp38) {
                arg0->unk0x74 = sp38;
            }
        } else {
            if (arg0->unk0x74 < sp38) {
                arg0->unk0x74 = sp38;
            }
        }
        if (arg0->unk0x78->unk0x14 == 0) {
            arg0->unk0x78->unk0x14 = (s32)fn_8012ED98(fn_80032088(0xF8));
        }
        if ((sp30 <= sp38 && sp34 >= arg0->unk0x74) || (sp30 >= sp38 && sp34 <= arg0->unk0x74)) {
            fn_8012F024(arg0->unk0x78->unk0x14);
            arg0->unk0x70 = 0;
        } else {
            fn_8012EFCC(arg0->unk0x78->unk0x14, 0);
            arg0->unk0x70 = 1;
        }
        break;
    case QB_ANIMEXISTS:
        GetChecksum_2(arg2, 0, &sp40, 0);
        if (fn_8002F724(arg0, sp40) != 0) {
            return 1;
        }
        return 0;
    case QB_GETCURRENTANIMINFO:
        GetInteger(arg2, QB_BLENDCHANNEL, &sp44, 0);
        p = (char *)arg0->unk0x24;
        if (*(s32 *)(p + 4) == -1) {
            p = 0;
        }
        n = (p != 0) ? (N2E3A8 *)(p - 4) : 0;
        while (n != 0 && sp44 != 0) {
            p = (char *)n->unk0x10;
            if (*(s32 *)(p + 4) == -1) {
                p = 0;
            }
            n = (p != 0) ? (N2E3A8 *)(p - 4) : 0;
            sp44 -= 1;
        }
        if (n != 0) {
            fn_8002F4E0(arg0, n, arg3->unk0x18);
        }
        break;
    case QB_REPLACEANIM:
        GetChecksum_2(arg2, QB_ANIM, &sp48, 0);
        if (fn_8002F724(arg0, sp48) == 0) {
            sp48 = QB_DEFAULT;
            AddChecksum(arg2, QB_ANIM, QB_DEFAULT);
        }
        fn_8012772C(arg2, QB_DURATION, fn_8002F700(arg0, sp48));
        GetInteger(arg2, QB_BLENDCHANNEL, &sp4C, 0);
        {
            char *base = (char *)&arg0->unk0x18;
            char *hd = *(char **)(base + 0xC);
            N2E3A8 *m;
            if (*(s32 *)(hd + 4) == -1) {
                hd = 0;
            }
            m = (hd != 0) ? (N2E3A8 *)(hd - 4) : 0;
            if (m == 0) {
                return 0;
            }
            while (sp4C != 0) {
                char *q = (char *)m->unk0x10;
                if (*(s32 *)(q + 4) == -1) {
                    q = 0;
                }
                m = (q != 0) ? (N2E3A8 *)(q - 4) : 0;
                sp4C -= 1;
                if (m == 0) {
                    return 0;
                }
            }
            hd = *(char **)(base + 0xC);
            if (*(s32 *)(hd + 4) == -1) {
                hd = 0;
            }
            if ((char *)m == ((hd != 0) ? hd - 4 : 0)) {
                fn_8002FEB8(arg0);
                fn_8002FEF0(arg0, sp48);
            }
            {
                V2E3A8 *vt = m->unk0x18;
                if (((s32 (*)(void *, s32, CStruct *, void *))vt->unk0x34)((char *)m + vt->unk0x30, arg1, arg2, arg3) == 0) {
                    return 0;
                }
            }
            return 1;
        }
    case QB_UPDATEDIFFERENCEANIM:
    case QB_INCREMENTPARTIALANIMTIME:
    case QB_ADDANIMCONTROLLER:
    case QB_SETPARTIALANIMSPEED:
    case QB_GETPARTIALANIMPARAMS:
    case QB_REVERSEPARTIALANIMDIRECTION:
        p = (char *)arg0->unk0x24;
        if (*(s32 *)(p + 4) == -1) {
            p = 0;
        }
        n = (p != 0) ? (N2E3A8 *)(p - 4) : 0;
        if (n != 0) {
            V2E3A8 *vt = n->unk0x18;
            if (((s32 (*)(void *, s32, CStruct *, void *))vt->unk0x34)((char *)n + vt->unk0x30, arg1, arg2, arg3) != 0) {
                return 1;
            }
            return 0;
        }
        break;
    case QB_REMOVEANIMCONTROLLER:
        p = (char *)arg0->unk0x24;
        if (*(s32 *)(p + 4) == -1) {
            p = 0;
        }
        n = (p != 0) ? (N2E3A8 *)(p - 4) : 0;
        if (n != 0) {
            do {
                V2E3A8 *vt = n->unk0x18;
                char *q;
                N2E3A8 *m;
                ((void (*)(void *, s32, CStruct *, void *))vt->unk0x34)((char *)n + vt->unk0x30, arg1, arg2, arg3);
                q = (char *)n->unk0x10;
                if (*(s32 *)(q + 4) == -1) {
                    q = 0;
                }
                m = (q != 0) ? (N2E3A8 *)(q - 4) : 0;
                n = m;
            } while (n != 0);
        }
        break;
    case QB_OBJ_FLIP:
        if (GetFloat(arg2, QB_BLENDCHANNEL, (f32 *)&sp50, 0) == 0) {
            fn_8002E34C(arg0);
            p = (char *)arg0->unk0x24;
            if (*(s32 *)(p + 4) == -1) {
                p = 0;
            }
            n = (p != 0) ? (N2E3A8 *)(p - 4) : 0;
            if (n != 0) {
                do {
                    V2E3A8 *vt = n->unk0x18;
                    char *q;
                    N2E3A8 *m;
                    ((void (*)(void *, s32, CStruct *, void *))vt->unk0x34)((char *)n + vt->unk0x30, arg1, arg2, arg3);
                    q = (char *)n->unk0x10;
                    if (*(s32 *)(q + 4) == -1) {
                        q = 0;
                    }
                    m = (q != 0) ? (N2E3A8 *)(q - 4) : 0;
                    n = m;
                } while (n != 0);
            }
            break;
        }
        if (sp50 == 0) {
            fn_8002E34C(arg0);
        }
        p = (char *)arg0->unk0x24;
        if (*(s32 *)(p + 4) == -1) {
            p = 0;
        }
        n = (p != 0) ? (N2E3A8 *)(p - 4) : 0;
        while (n != 0) {
            if (sp50 != 0) {
                p = (char *)n->unk0x10;
                if (*(s32 *)(p + 4) == -1) {
                    p = 0;
                }
                n = (p != 0) ? (N2E3A8 *)(p - 4) : 0;
                sp50 -= 1;
                continue;
            }
            {
                V2E3A8 *vt = n->unk0x18;
                ((void (*)(void *, s32, CStruct *, void *))vt->unk0x34)((char *)n + vt->unk0x30, arg1, arg2, arg3);
            }
            break;
        }
        break;
    case QB_OBJ_ANIMATIONFLIPPED:
        return (arg0->unk0x64 >> 0x1D) & 1;
    case QB_SETWOBBLEDETAILS:
        break;
    default:
        return 2;
    }
    return 1;
}