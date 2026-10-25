// WIP DRAFT (non-matching) — C body hand-rebuilt from disasm
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 10.3048% -> 10.4499% `volatile` keyword(s) removed from the body
// family=m2c range=0x8024A438-0x8024AEF0 size=2744B
// PARKED 6%: semantically complete hand rebuild (all 4 switch cases, both lerp
// loops, half-round E114 blocks, byte-width dc/dd fields verified against
// disasm); compiled size matches want exactly (2756B/689 insns). Remaining
// diffs are a function-wide register/slot permutation (~50 webs): arg0->r31 ok
// but every stack slot sits 4-8 lower than want (i@r1+0x30 vs 0x24), frame
// 0x80 vs 0x88, sdata globals lbl_803CAF88/8C emit lis/ori+lwz(0) instead of
// want's r13-form (-msdata=eabi -G4 scores WORSE: 24/684 — reroutes unrelated
// small data; inline-asm r13 loads also lose: 32/685), zero-fill window needs
// the mfctr/bdnz asm idiom (same as parked fn_8024A0B0), and the j/i counters
// live in MEMORY (want stores i at r1+0x24, reloads per outer test).
// Next-session levers not yet tried: frame-template struct pinning all sp
// slots (recipe 86/144) + decl-order steering (76-184) applied TOGETHER;
// per-web register pins are known-cascading here (see parked fn_8024A0B0).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 10.3% ([6]rev->9.7% [5]rev->10.3%).
#include "types.h"
#include "structs.h"
s32 OSPanic(s32, s32, s32);

extern s32 lbl_802B1408[];
extern s32 lbl_802B1428[];
extern u8 lbl_802B1448[];
extern u8 lbl_802B1458[];
extern s32 lbl_803CAF88;
extern s32 lbl_803CAF8C;
void fn_8024E0E0(CStruct * arg0);
void fn_80251EEC(Unk_80577C09 * arg0);
s32 fn_80250EAC(CStruct * stream, s32 nbits);
s32 fn_8024D5C4(Unk_C7387A53 * p);
void fn_8024E114(Unk_C7387A53 * ctx, CStruct * dst, s32 n, Unk_EA529D06 * src);
void fn_8024B690(Unk_891D1D72 * a0, Unk_12004030 * a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void fn_8024BA9C(Unk_25BF2A93 * a0, CStruct * a1, CStruct * a2, Unk_12004030 * a3, s32 a4, s32 a5, s32 a6,
                 s32 a7);

void fn_8024A438(Unk_897A0ACF *arg0) {
    s32 sp8;
    s32 spC;
    s32 sp10[2];
    s32 sp18[2];
    s32 sp20;
    s32 sp24;
    char *sp28;
    char *sp2C;
    char *sp30;
    char *sp34;
    s32 sp38;
    s32 zn;
    u32 i;
    u32 j;
    u32 k;
    s32 var_r24;
    s32 flagbits;
    s32 adj;
    u8 lvlbit;
    s32 hdelta;
    u8 level;
    u8 type;
    u8 *ent;
    u8 *out;
    s32 *zp;
    s32 *zq;
    s32 *ze0;
    s32 *ze4;
    s32 *evp;
    s32 *evq;
    char *rs;

    i = 0;
    fn_8024E0E0(*((void * *)&arg0->unk0x2C));
    fn_80251EEC(*((void * *)&arg0->unk0x10));
    out = (u8 *)arg0->unk0x28;
    ent = (u8 *)arg0->unk0x24;
    level = arg0->unk0x4F;
    hdelta = arg0->unk0x64 - arg0->unk0x60;
    sp20 = arg0->unk0x68 - arg0->unk0x60;
    while (i < arg0->unk0x6) {
        j = 0;
        sp34 = (char *)arg0 + 0x100;
        sp30 = (char *)arg0 + 0xF8;
        sp2C = (char *)arg0 + 0xF0;
        sp28 = (char *)arg0 + 0xE8;
        rs = (char *)arg0 + 0x30;
        arg0->unk0x104 = spC;
        arg0->unk0x100 = sp8;
        arg0->unk0xFC = spC;
        arg0->unk0xF8 = sp8;
        arg0->unk0xF4 = spC;
        arg0->unk0xF0 = sp8;
        arg0->unk0xEC = spC;
        arg0->unk0xE8 = sp8;
        spC = lbl_803CAF8C;
        sp8 = lbl_803CAF88;
        sp38 = i + 1;
        while (j < arg0->unk0x4) {
            *(u8 *)out = 0;
            if (*(u8 *)ent == 0x10) {
                ((Unk_B6371D19 *)out)->unk0xDD = 0;
                ((Unk_B6371D19 *)out)->unk0xDC = 3;
                zn = 0x20;
                __asm__ volatile(
                    "addi 11, %0, 8\n\t"
                    "mfctr 8\n\t"
                    "srwi 7, %1, 2\n\t"
                    "addi 7, 7, -1\n\t"
                    "mtctr 7\n\t"
                    "mr 10, 11\n\t"
                    "li 7, 0\n\t"
                    "stw 7, 0(10)\n\t"
                    ".Lzw2: stwu 7, 4(10)\n\t"
                    "bdnz .Lzw2\n\t"
                    "mtctr 8"
                    :
                    : "r"(out), "r"(zn)
                    : "r7", "r8", "r10", "r11", "memory");
                ((Unk_B6371D19 *)out)->unk0x1 = level;
                fn_8024B690(arg0, out, j, i, 0, 1, 0);
            } else {
                type = fn_80250EAC(rs, 1);
                if (type != 0) {
                    var_r24 = 0;
                    ((Unk_B6371D19 *)out)->unk0xDC = 0;
                    ((Unk_B6371D19 *)out)->unk0xDD = 0;
                    sp8 = lbl_803CAF88;
                    spC = lbl_803CAF8C;
                } else {
                    lvlbit = fn_80250EAC(rs, 1);
                    var_r24 = 1;
                    ((Unk_B6371D19 *)out)->unk0xDC = fn_8024D5C4((char *)arg0 + 0x48);
                    if (lvlbit == 0) {
                        ((Unk_B6371D19 *)out)->unk0xDD = fn_80250EAC(rs, 6);
                    } else {
                        ((Unk_B6371D19 *)out)->unk0xDD = type;
                    }
                    if (((((Unk_B6371D19 *)out)->unk0xDC & 3) != 0) && (lvlbit == 0)) {
                        adj = 0;
                        if (fn_80250EAC(
                                arg0->unk0x8C, 1) != 0) {
                            adj = 2;
                            if (fn_80250EAC(
                                    arg0->unk0x8C, 1) == 0) {
                                adj = -2;
                            }
                        }
                        level += adj;
                        if (level > 0x1F) {
                            level = 0x1F;
                        } else if (level == 0) {
                            level = 1;
                        }
                    }
                    if (arg0->unk0x84 != 0) {
                        if ((((Unk_B6371D19 *)out)->unk0xDD != 0) &&
                            (fn_80250EAC(rs, 1) != 0)) {
                            ((Unk_B6371D19 *)out)->unk0xDC |= 4;
                        }
                        if ((((Unk_B6371D19 *)out)->unk0xDC & 3) &&
                            (fn_80250EAC(rs, 1) != 0)) {
                            ((Unk_B6371D19 *)out)->unk0xDC |= 8;
                        }
                    }
                }
                ((Unk_B6371D19 *)out)->unk0x1 = level;
                switch ((((Unk_B6371D19 *)out)->unk0xDC & 3)) {
                case 0:
                    if (var_r24 != 0) {
                        fn_8024E114(arg0->unk0x2C, &sp8, 1,
                                    (void *)&lbl_803CAF88);
                    }
                    if ((arg0->unk0x84 != 0) &&
                        (*(u8 *)ent != 0x10) && (*(u8 *)ent != 3) &&
                        (*(u8 *)ent != 4) &&
                        ((((Unk_B6371D19 *)ent)->unk0xDC & 8) != 0)) {
                        k = (((Unk_B6371D19 *)ent)->unk0xDC >> 4) & 3;
                        if (arg0->unk0x88 != 0) {
                            k += 4;
                        }
                        sp18[0] = sp20 * 2 + lbl_802B1408[k];
                        sp18[1] = sp20 * 2 + lbl_802B1428[k];
                        sp10[0] = hdelta * 2 + lbl_802B1408[k];
                        sp10[1] = hdelta * 2 + lbl_802B1428[k];
                        zp = (s32 *)(out + 8);
                        zq = (s32 *)(ent + 8);
                        evp = (s32 *)(out + 0xC);
                        ze0 = (s32 *)(out + 0xE0);
                        ze4 = (s32 *)(out + 0xE4);
                        evq = (s32 *)(ent + 0xC);
                        k = 0;
                        do {
                            zp[k] = (sp18[k] * zq[k]) / sp10[k] + sp8;
                            evp[k] = (sp18[k] * evq[k]) / sp10[k] + spC;
                            ze0[k] = (sp8 == 0)
                                         ? (((sp18[k] - sp10[k]) * zq[k]) /
                                            sp10[k])
                                         : (zp[k] - zq[k]);
                            ze4[k] = (spC == 0)
                                         ? (((sp18[k] - sp10[k]) * evq[k]) /
                                            sp10[k])
                                         : (evp[k] - evq[k]);
                            k++;
                        } while (k <= 1);
                        ((Unk_B6371D19 *)out)->unk0xDC |= 8;
                        fn_8024BA9C(arg0, arg0->unk0x14,
                                    arg0->unk0x10, out, j, i,
                                    ((Unk_B6371D19 *)out)->unk0xDD,
                                    (((((Unk_B6371D19 *)ent)->unk0xDC >> 4) & 3) | 8));
                    } else {
                        zp = (s32 *)(out + 8);
                        zq = (s32 *)(ent + 8);
                        evp = (s32 *)(out + 0xC);
                        ze0 = (s32 *)(out + 0xE0);
                        ze4 = (s32 *)(out + 0xE4);
                        evq = (s32 *)(ent + 0xC);
                        k = 0;
                        do {
                            zp[k] = (sp20 * zq[k]) / hdelta + sp8;
                            evp[k] = (sp20 * evq[k]) / hdelta + spC;
                            ze0[k] = (sp8 == 0)
                                         ? (((sp20 - hdelta) * zq[k]) / hdelta)
                                         : (zp[k] - zq[k]);
                            ze4[k] = (spC == 0)
                                         ? (((sp20 - hdelta) * evq[k]) / hdelta)
                                         : (evp[k] - evq[k]);
                            k++;
                        } while (k <= 3);
                        *(u8 *)out = 2;
                        fn_8024BA9C(arg0, arg0->unk0x14,
                                    arg0->unk0x10, out, j, i,
                                    ((Unk_B6371D19 *)out)->unk0xDD, 0);
                    }
                    break;
                case 1:
                    flagbits = 0;
                    if ((((Unk_B6371D19 *)out)->unk0xDC & 8) != 0) {
                        flagbits = fn_80250EAC(rs, 1);
                        flagbits |= fn_80250EAC(rs, 1) << 1;
                        flagbits |= fn_80250EAC(rs, 1) << 2;
                        flagbits |= fn_80250EAC(rs, 1) << 3;
                        arg0->unk0xEC =
                            arg0->unk0xEC / 2;
                        fn_8024E114(arg0->unk0x2C, sp28,
                                    arg0->unk0x50, sp28);
                        arg0->unk0xEC =
                            arg0->unk0xEC * 2;
                        ((Unk_B6371D19 *)out)->unk0x8 = arg0->unk0xE8;
                        ((Unk_B6371D19 *)out)->unk0xC = arg0->unk0xEC;
                        arg0->unk0xF4 =
                            arg0->unk0xF4 / 2;
                        fn_8024E114(arg0->unk0x2C, sp2C,
                                    arg0->unk0x50, sp2C);
                        arg0->unk0xF4 =
                            arg0->unk0xF4 * 2;
                        ((Unk_B6371D19 *)out)->unk0x10 = arg0->unk0xF0;
                        ((Unk_B6371D19 *)out)->unk0x14 = arg0->unk0xF4;
                        arg0->unk0xFC =
                            arg0->unk0xFC / 2;
                        fn_8024E114(arg0->unk0x2C, sp30,
                                    arg0->unk0x52, sp30);
                        arg0->unk0xFC =
                            arg0->unk0xFC * 2;
                        ((Unk_B6371D19 *)out)->unk0xE0 = arg0->unk0xF8;
                        ((Unk_B6371D19 *)out)->unk0xE4 = arg0->unk0xFC;
                        arg0->unk0x104 =
                            arg0->unk0x104 / 2;
                        fn_8024E114(arg0->unk0x2C, sp34,
                                    arg0->unk0x52, sp34);
                        arg0->unk0x104 =
                            arg0->unk0x104 * 2;
                        ((Unk_B6371D19 *)out)->unk0xE8 = arg0->unk0x100;
                        ((Unk_B6371D19 *)out)->unk0xEC = arg0->unk0x104;
                    } else {
                        fn_8024E114(arg0->unk0x2C, out + 8,
                                    arg0->unk0x50,
                                    (char *)arg0 + 0xE8);
                        sp8 = ((Unk_B6371D19 *)out)->unk0x8;
                        spC = ((Unk_B6371D19 *)out)->unk0xC;
                        ((Unk_B6371D19 *)out)->unk0x20 = sp8;
                        ((Unk_B6371D19 *)out)->unk0x24 = spC;
                        ((Unk_B6371D19 *)out)->unk0x18 = sp8;
                        ((Unk_B6371D19 *)out)->unk0x1C = spC;
                        ((Unk_B6371D19 *)out)->unk0x10 = sp8;
                        ((Unk_B6371D19 *)out)->unk0x14 = spC;
                        arg0->unk0xE8 = sp8;
                        arg0->unk0xEC = spC;
                        arg0->unk0xF0 = sp8;
                        arg0->unk0xF4 = spC;
                        fn_8024E114(arg0->unk0x2C, out + 0xE0,
                                    arg0->unk0x52,
                                    (char *)arg0 + 0xF8);
                        sp8 = ((Unk_B6371D19 *)out)->unk0xE0;
                        spC = ((Unk_B6371D19 *)out)->unk0xE4;
                        ((Unk_B6371D19 *)out)->unk0xF8 = sp8;
                        ((Unk_B6371D19 *)out)->unk0xFC = spC;
                        ((Unk_B6371D19 *)out)->unk0xF0 = sp8;
                        ((Unk_B6371D19 *)out)->unk0xF4 = spC;
                        ((Unk_B6371D19 *)out)->unk0xE8 = sp8;
                        ((Unk_B6371D19 *)out)->unk0xEC = spC;
                        arg0->unk0xF8 = sp8;
                        arg0->unk0xFC = spC;
                        arg0->unk0x100 = sp8;
                        arg0->unk0x104 = spC;
                    }
                    fn_8024BA9C(arg0, arg0->unk0x14,
                                arg0->unk0x10, out, j, i,
                                ((Unk_B6371D19 *)out)->unk0xDD, flagbits);
                    break;
                case 2:
                    if ((((Unk_B6371D19 *)out)->unk0xDC & 8) != 0) {
                        flagbits = fn_80250EAC(rs, 1);
                        flagbits |= fn_80250EAC(rs, 1) << 1;
                        arg0->unk0xFC =
                            arg0->unk0xFC / 2;
                        fn_8024E114(arg0->unk0x2C, sp30,
                                    arg0->unk0x52, sp30);
                        arg0->unk0xFC =
                            arg0->unk0xFC * 2;
                        ((Unk_B6371D19 *)out)->unk0x8 = arg0->unk0xF8;
                        ((Unk_B6371D19 *)out)->unk0xC = arg0->unk0xFC;
                        arg0->unk0x104 =
                            arg0->unk0x104 / 2;
                        fn_8024E114(arg0->unk0x2C, sp34,
                                    arg0->unk0x52, sp34);
                        arg0->unk0x104 =
                            arg0->unk0x104 * 2;
                        ((Unk_B6371D19 *)out)->unk0x10 = arg0->unk0x100;
                        ((Unk_B6371D19 *)out)->unk0x14 = arg0->unk0x104;
                    } else {
                        flagbits = 0;
                        fn_8024E114(arg0->unk0x2C, out + 8,
                                    arg0->unk0x52,
                                    (char *)arg0 + 0xF8);
                        sp8 = ((Unk_B6371D19 *)out)->unk0x8;
                        spC = ((Unk_B6371D19 *)out)->unk0xC;
                        ((Unk_B6371D19 *)out)->unk0x20 = sp8;
                        ((Unk_B6371D19 *)out)->unk0x24 = spC;
                        ((Unk_B6371D19 *)out)->unk0x18 = sp8;
                        ((Unk_B6371D19 *)out)->unk0x1C = spC;
                        ((Unk_B6371D19 *)out)->unk0x10 = sp8;
                        ((Unk_B6371D19 *)out)->unk0x14 = spC;
                        arg0->unk0xF8 = sp8;
                        arg0->unk0xFC = spC;
                        arg0->unk0x100 = sp8;
                        arg0->unk0x104 = spC;
                    }
                    fn_8024B690(arg0, out, j, i, ((Unk_B6371D19 *)out)->unk0xDD, 0,
                                flagbits);
                    break;
                case 3:
                    if ((((Unk_B6371D19 *)out)->unk0xDC & 8) != 0) {
                        flagbits = fn_80250EAC(rs, 1);
                        flagbits |= fn_80250EAC(rs, 1) << 1;
                        arg0->unk0xEC =
                            arg0->unk0xEC / 2;
                        fn_8024E114(arg0->unk0x2C, sp28,
                                    arg0->unk0x50, sp28);
                        arg0->unk0xEC =
                            arg0->unk0xEC * 2;
                        ((Unk_B6371D19 *)out)->unk0x8 = arg0->unk0xE8;
                        ((Unk_B6371D19 *)out)->unk0xC = arg0->unk0xEC;
                        arg0->unk0xF4 =
                            arg0->unk0xF4 / 2;
                        fn_8024E114(arg0->unk0x2C, sp2C,
                                    arg0->unk0x50, sp2C);
                        arg0->unk0xF4 =
                            arg0->unk0xF4 * 2;
                        ((Unk_B6371D19 *)out)->unk0x10 = arg0->unk0xF0;
                        ((Unk_B6371D19 *)out)->unk0x14 = arg0->unk0xF4;
                    } else {
                        flagbits = 0;
                        fn_8024E114(arg0->unk0x2C, out + 8,
                                    arg0->unk0x50,
                                    (char *)arg0 + 0xE8);
                        sp8 = ((Unk_B6371D19 *)out)->unk0x8;
                        spC = ((Unk_B6371D19 *)out)->unk0xC;
                        ((Unk_B6371D19 *)out)->unk0x20 = sp8;
                        ((Unk_B6371D19 *)out)->unk0x24 = spC;
                        ((Unk_B6371D19 *)out)->unk0x18 = sp8;
                        ((Unk_B6371D19 *)out)->unk0x1C = spC;
                        ((Unk_B6371D19 *)out)->unk0x10 = sp8;
                        ((Unk_B6371D19 *)out)->unk0x14 = spC;
                        arg0->unk0xE8 = sp8;
                        arg0->unk0xEC = spC;
                        arg0->unk0xF0 = sp8;
                        arg0->unk0xF4 = spC;
                    }
                    fn_8024B690(arg0, out, j, i, ((Unk_B6371D19 *)out)->unk0xDD, 1,
                                flagbits);
                    break;
                default:
                    OSPanic(lbl_802B1448, 0x392, lbl_802B1458);
                    break;
                }
            }
            j++;
            out += 0x100;
            ent += 0x100;
        }
        i = sp38;
    }
}
