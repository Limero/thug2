// WIP DRAFT (non-matching) — hand-rebuilt from disasm 2026-08-25
// family=m2c range=0x8024B208-0x8024B690 size=1160B
// PARKED 4.2%: semantically complete rebuild, but the register cascade starts
// at insn #2 and never re-syncs.
//
// WALL 1 — tail clear window frozen as asm (~11 insns of 290): same ProDG
// doloop template as fn_8024AEF0 WALL 1 ([li size into reg][mfctr save]
// [srwi from REG-held count][addi -1][mtctr][stw peel][stwu loop][bdnz]
// [mtctr restore]); semantics = memset(*(arg0+0x10C)+off, 0, 0x80). The size
// is loop-invariant here (li r25,0x80 hoisted before the plane loop), which is
// WHY retail's count stays register-born — but this cc1 still folds constant
// memset-loops even inside enclosing loops (probe-verified), so plain C cannot
// reproduce it either way.
//
// WALL 2 — whole-body allocator cascade. Want homes: arg0 r31/arg1 r21/
// arg2 r20/arg3 r18/arg4 r19/&dims r22(born right after div rounds)/width lhz
// r23/x16 slwi r7/y16 slwi r5; div-round webs live in SCRATCH regs (val74 r11,
// shift lha r8, m r10 persisting across BOTH ceil-div rounds); dims w/h are
// stack-backed (address escapes into fn_802518D8). Every reconstruction keeps
// `shift` alive across the four bl calls (one C name = one web) -> saved-reg
// home -> everything shifts. Splitting shiftA/shiftB per phase did not
// re-sync: divergence begins at the prologue param-save interleave
// (want hoists lwz 0x74 + lha 0x72 ABOVE the r5-r7 saves).
//
// Structure truth for future attempts:
//  - two inline ceil-divs: q=(v+(1<<(sh-1)))>>sh if v>0 else ((v+(1<<(sh-1)))-1)>>sh,
//    results stored to arg1+8/0xC, then RELOADED from arg1 for the six-store
//    run to arg1+0x20/24/10/14/18/1C;
//  - dims dance per component: xo=w>>(sh+1); w<<=3-sh; clamp xo>=-16;
//    lim=lhz(arg0+0) with DOUBLE extsh ((s16)lim tested twice);
//    if result==(s16)lim -> w=0 (same for y with lhz@2 / phase-2 >>1 via lha+srawi);
//  - phase-1 clamps -0x10 / limits u16@0,+2; phase-2 clamps -8 / limits (s16)>>1;
//  - 4 Y calls share dstBase(+0x20)/(width<<3 variants), texBase *(r11+8),
//    width=lhz(*(arg0+C)+4); 2 UV calls use uvW=width>>1, dst from *(r9+0xC)
//    and *(r9+0x10), offsets arg2<<5 / (arg3<<3)*uvW;
//  - fn_802511DC is called via a 3-ARG PROTO (callee reads garbage r4!);
//  - tail loop bit-test order i/bit/off/clrSize = r28/r26/r30/r25.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 4.5% ([7]rev->4.5%).
#include "types.h"
#include "structs.h"
extern void fn_802518D8(void *dst, s32 a, s32 b, s32 c, s32 d, CStruct * src, s32 e);
extern void fn_802511DC(s32 a, s32 b, s32 c);
extern void fn_80250900(void * a, void * b, s32 c);
extern void fn_80250A1C(void * a, void * b, s32 c, u8 * d);
extern void fn_8024EF18(s32 a);
extern void fn_8024F65C(void * a, s32 b, s32 c, void * d, s32 e);
extern void fn_8024FD90(Unk_5B449B03 * a, s32 b, s32 c);

void fn_8024B208(Unk_7AAECE1C *arg0, Unk_1D62F22E *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp8;
    s32 spC;
    s16 shiftA;
    s16 shiftB;
    s32 val74;
    s32 val78;
    s32 m1;
    s32 q;
    s32 temp_r9;
    s32 temp_r10;
    s32 x16;
    s32 y16;
    s32 texBase;
    s32 dstBase;
    s32 dstV;
    s32 uvOff;
    s32 uvA;
    s32 uvB;
    u32 limitX;
    u32 limitY;
    s32 var_r25;
    s32 var_r24;
    s32 var_r26;
    s32 var_r27;
    s32 width;
    s32 widthHalf;
    u32 i;
    u32 bit;
    s32 off;
    s32 clrSize;
    s32 uvW;

    shiftA = arg0->unk0x72;
    val74 = arg0->unk0x74;
    if (val74 > 0) {
        m1 = shiftA - 1;
        q = (val74 + (1 << m1)) >> shiftA;
    } else {
        m1 = shiftA - 1;
        q = ((val74 + (1 << m1)) - 1) >> shiftA;
    }
    arg1->unk0x8 = q;
    val78 = arg0->unk0x78;
    if (val78 > 0) {
        q = (val78 + (1 << m1)) >> shiftA;
    } else {
        q = ((val78 + (1 << m1)) - 1) >> shiftA;
    }
    arg1->unk0xC = q;
    temp_r9 = arg1->unk0x8;
    temp_r10 = arg1->unk0xC;
    arg1->unk0x20 = temp_r9;
    *((s32 *)&arg1->unk0x24) = temp_r10;
    arg1->unk0x10 = temp_r9;
    arg1->unk0x14 = temp_r10;
    arg1->unk0x18 = temp_r9;
    arg1->unk0x1C = temp_r10;
    val74 = arg0->unk0x74;
    val78 = arg0->unk0x78;
    shiftB = arg0->unk0x72;
    sp8 = val74;
    spC = val78;
    m1 = 3 - shiftB;
    temp_r9 = sp8 >> (shiftB + 1);
    sp8 <<= m1;
    var_r24 = y16 + (spC >> (shiftB + 1));
    var_r25 = x16 + temp_r9;
    y16 = arg3 * 0x10;
    x16 = arg2 * 0x10;
    spC <<= m1;
    if (var_r25 < -0x10) {
        var_r25 = -0x10;
    }
    limitX = arg0->unk0x0;
    var_r26 = (s16)limitX;
    if (var_r26 > var_r25) {
        var_r26 = var_r25;
    }
    var_r25 = var_r26;
    if (var_r25 == (s16)limitX) {
        sp8 = 0;
    }
    var_r27 = var_r24;
    if (var_r27 < -0x10) {
        var_r27 = -0x10;
    }
    limitY = arg0->unk0x2;
    var_r24 = (s16)limitY;
    if (var_r24 > var_r27) {
        var_r24 = var_r27;
    }
    if (var_r24 == (s16)limitY) {
        spC = 0;
    }
    width = *(u16 *)(arg0->unk0xC + 4);
    texBase = *(s32 *)(arg0->unk0x10 + 8);
    dstBase = arg0->unk0xC + 8 + y16 * width + (arg2 << 6);
    dstV = dstBase + (width << 3);
    fn_802518D8(dstBase,
                texBase,
                width,
                var_r25,
                var_r24,
                &sp8,
                arg0->unk0x48);
    fn_802518D8(dstBase + 0x20,
                texBase,
                width,
                var_r25 + 8,
                var_r24,
                &sp8,
                arg0->unk0x48);
    fn_802518D8(dstV,
                texBase,
                width,
                var_r25,
                var_r24 + 8,
                &sp8,
                arg0->unk0x48);
    fn_802518D8(dstV + 0x20,
                texBase,
                width,
                var_r25 + 8,
                var_r24 + 8,
                &sp8,
                arg0->unk0x48);
    val74 = arg0->unk0x7C;
    val78 = arg0->unk0x80;
    shiftB = arg0->unk0x72;
    sp8 = val74;
    spC = val78;
    m1 = 3 - shiftB;
    temp_r9 = sp8 >> (shiftB + 1);
    sp8 <<= m1;
    var_r25 = (arg2 << 3) + temp_r9;
    var_r24 = (arg3 << 3) + (spC >> (shiftB + 1));
    spC <<= m1;
    if (var_r25 < -8) {
        var_r25 = -8;
    }
    limitX = arg0->unk0x0;
    var_r26 = ((s16)limitX) >> 1;
    if (var_r26 > var_r25) {
        var_r26 = var_r25;
    }
    if (var_r26 == (s32)(((s16)limitX) >> 1)) {
        sp8 = 0;
    }
    var_r25 = var_r26;
    var_r27 = var_r24;
    if (var_r27 < -8) {
        var_r27 = -8;
    }
    limitY = arg0->unk0x2;
    var_r24 = ((s16)limitY) >> 1;
    if (var_r24 > var_r27) {
        var_r24 = var_r27;
    }
    if (var_r24 == (s32)(((s16)limitY) >> 1)) {
        spC = 0;
    }
    uvW = width >> 1;
    fn_802518D8(arg0->unk0xC + 0xC + (arg3 << 3) * uvW + (arg2 << 5),
                *(s32 *)(arg0->unk0x10 + 0xC),
                uvW,
                var_r25,
                var_r24,
                &sp8,
                arg0->unk0x48);
    fn_802518D8(arg0->unk0xC + 0x10 + (arg3 << 3) * uvW + (arg2 << 5),
                *(s32 *)(arg0->unk0x10 + 0x10),
                uvW,
                var_r25,
                var_r24,
                &sp8,
                arg0->unk0x48);
    if (arg4 != 0) {
        i = 0;
        bit = 5;
        off = 0;
        clrSize = 0x80;
        do {
            if (arg4 & (1 << bit)) {
                {
                    char *clrP = (char *)(off + arg0->unk0x10C);
                    __asm__ __volatile__("mfctr 11; srwi 10,%1,2; addi 10,10,-1; mtctr 10; mr 9,%0; li 10,0; stw 10,0(9); .Lw3: stwu 10,4(9); bdnz .Lw3; mtctr 11"
                                         :
                                         : "r"(clrP), "r"(clrSize)
                                         : "r9", "r10", "r11", "cc", "ctr", "memory");
                }
                fn_802511DC(arg0->unk0x90, (s32)arg0 + 0xB4, arg0->unk0x94);
                if (arg0->unk0x4C == 0) {
                    fn_80250900(arg0->unk0x110 + off, arg0->unk0x10C + off, arg1->unk0x1);
                } else {
                    fn_80250A1C(arg0->unk0x110 + off, arg0->unk0x10C + off, arg1->unk0x1, arg0->unk0x5C);
                }
                fn_8024EF18(arg0->unk0x110 + (i << 6) + (i << 6));
            }
            i += 1;
            off += 0x80;
            bit -= 1;
        } while (i <= 5U);
        fn_8024F65C(arg0->unk0xC, arg2, arg3, arg0->unk0x110, arg4);
    }
    fn_8024FD90(arg0->unk0xC, arg2, arg3);
}
