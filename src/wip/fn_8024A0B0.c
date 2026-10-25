// WIP DRAFT (non-matching) — C body hand-rebuilt from disasm
// family=m2c range=0x8024A0B0-0x8024A438 size=904B
// PARKED 89%: 5-web allocator-order permutation. All structure/widths/ops
// match; the remaining 25 words are register-home swaps among five short-lived
// webs {i+1 giv r21/r20, table base r22/r21, zn r20/r22, stream r26/r25,
// flag r25/r26} (got/want). Resisted: decl-order permutations, statement-order
// variants (zn before/after stb / inside arm / outer loop), named-vs-inline
// stream/table webs, -fno-gcse (destroys cr4-cache+hoists), -fno-sched-spec
// (+-interblock), -fno-branch-count-reg, single/full register pins (cascade:
// arg1 loses r19 home, frame shifts). The mfcr/cr4-cache + hoisted
// `cmpwi cr4,arg1` emerge naturally only with zn's web assigned BEFORE the
// first read() call — that placement also pins zn's allocation slot wrong.
// Zero-fill window frozen as short asm (li/addi/stb/mfctr/srwi/mtctr/stw/
// stwu/bdnz+/mtctr = 13 of 226 insns; want uses a hinted `bdnz+` + CTR
// save/restore idiom — only 4 sites DOL-wide, not plain-C loop codegen).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"

extern u8 lbl_802B1398[];
void fn_8024E0E0(CStruct * arg0);
void fn_80251EEC(Unk_80577C09 * arg0);
s32 fn_80250EAC(CStruct * stream, s32 nbits);
s32 fn_8024D4D0(Unk_C7387A53 * p);
s32 fn_8024D418(void *p, s32 f);
void fn_8024F4B0(Unk_1D9F1A68 * a, s32 b, s32 c, s32 d);
void fn_8024B208(Unk_7AAECE1C * a0, Unk_1D62F22E * a1, s32 a2, s32 a3, s32 a4);
void fn_8024AEF0(Unk_804E7039 * a0, Unk_12004030 * a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void fn_8024DC14(CStruct * a0, Unk_12004030 * a1, s32 a2, s32 a3, s32 a4);
void fn_8024B690(Unk_891D1D72 * a0, Unk_12004030 * a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void fn_8024A0B0(Unk_275B0766 *arg0, s32 arg1) {
    u8 *ent;
    u32 flags;
    u8 level;
    u32 fl2;
    s32 flag;
    char *rs;
    u32 j;
    u32 i;
    s32 zn;
    s32 vt;
    u32 type;
    s32 extra;
    u8 *tp;

    i = 0;
    fn_8024E0E0(arg0->unk0x2C);
    fn_80251EEC(arg0->unk0x10);
    level = arg0->unk0x4F;
    ent = (u8 *)arg0->unk0x24;
    while (i < arg0->unk0x6) {
        j = 0;
        while (j < arg0->unk0x4) {
            rs = (char *)arg0 + 0x30;
            vt = (s32)lbl_802B1398;
            ((Unk_12004030 *)ent)->unk0xDC = 0;
            zn = 0x20;
            if (fn_80250EAC(rs, 1) != 0) {
                if (arg1 == 0) {
                    __asm__ volatile(
                        "li 0, 0x10\n\t"
                        "addi 9, %0, 8\n\t"
                        "stb 0, 0(%0)\n\t"
                        "mfctr 10\n\t"
                        "srwi 8, %1, 2\n\t"
                        "addi 8, 8, -1\n\t"
                        "mtctr 8\n\t"
                        "mr 11, 9\n\t"
                        "li 8, 0\n\t"
                        "stw 8, 0(11)\n\t"
                        ".Lzw: stwu 8, 4(11)\n\t"
                        "bdnz+ .Lzw\n\t"
                        "mtctr 10"
                        :
                        : "r"(ent), "r"(zn)
                        : "r0", "r8", "r9", "r10", "r11", "memory");
                    fn_8024F4B0(arg0->unk0xC, j, i,
                                *((s32 *)&arg0->unk0x10));
                } else {
                    *(u8 *)ent = 0x11;
                    fn_8024B208(arg0, ent, j, i, 0);
                }
            } else {
                type = fn_8024D4D0((char *)arg0 + 0x48);
                flags = type >> 4;
                type &= 7;
                *(u8 *)ent = type;
                if ((type - 3) <= 1) {
                    flag = fn_80250EAC(rs, 1) != 0;
                    flags |= fn_8024D418((char *)arg0 + 0x48, 1) << 2;
                    if (*(u8 *)ent == 4) {
                        tp = (u8 *)(vt + (fn_80250EAC(rs, 2) << 2));
                        level += tp[3];
                        if (level > 0x1F) {
                            level = 0x1F;
                        } else if (level == 0) {
                            level = 1;
                        }
                    }
                    ((Unk_12004030 *)ent)->unk0x1 = level;
                    fn_8024AEF0(arg0, ent, j, i, flag, flags, level);
                } else {
                    if ((arg1 != 0) && !(flags & 0x10)) {
                        flag = fn_80250EAC(rs, 1);
                    } else {
                        flag = 0;
                    }
                    fl2 = (fn_8024D418((char *)arg0 + 0x48, 0) << 2) | flags;
                    if (*(u8 *)ent == 1) {
                        tp = (u8 *)(vt + (fn_80250EAC(rs, 2) << 2));
                        level += tp[3];
                        if (level > 0x1F) {
                            level = 0x1F;
                        } else if (level == 0) {
                            level = 1;
                        }
                    }
                    ((Unk_12004030 *)ent)->unk0x1 = level;
                    if ((arg0->unk0x84 != 0) && (fl2 != 0) &&
                        (fn_80250EAC(rs, 1) != 0)) {
                        ((Unk_12004030 *)ent)->unk0xDC |= 4;
                    }
                    if (flag == 0) {
                        extra = 0;
                        if ((arg0->unk0x84 != 0) &&
                            (fn_80250EAC(rs, 1) != 0)) {
                            ((Unk_12004030 *)ent)->unk0xDC |= 8;
                            extra = fn_80250EAC(rs, 1);
                            extra |= fn_80250EAC(rs, 1) << 1;
                            ((Unk_12004030 *)ent)->unk0xDC |= extra << 4;
                        }
                        fn_8024DC14(*((s32 *)&arg0->unk0x2C), ent, j, i,
                                    (*(u8 *)ent ^ 2) == 0);
                        fn_8024B690(arg0, ent, j, i, fl2, 0, extra);
                    } else {
                        fn_8024B208(arg0, ent, j, i, fl2);
                    }
                }
            }
            j++;
            ent += 0x100;
        }
        i++;
    }
}
