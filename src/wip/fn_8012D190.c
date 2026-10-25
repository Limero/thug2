// WIP DRAFT — PARKED (non-matching), but this is the BEST BODY FOUND: the object
// is SIZE-EXACT against the want (1148 B). The m2c draft emitted 8 B of 1148 B.
// reproduce: LEAF_TMPDIR=<scratch> \
//     tools/venv/bin/python tools/want_got.py 0x8012D190  -> 1148B / 260 diffs / 9.41%
//
// Hand-rebuilt from the want; no inline asm anywhere.
//
// family=m2c range=0x8012D190-0x8012D60C size=1148B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Progression: 8 B (husk) -> 1144 B -> 1148 B size-exact.
//
// ------------------------------------------------------------------ decode
// 13-case switch on `arg0[0]` (u8): 0x16, 0x17, 0x1A, 0x1B, 0x1C, 0x1E, 0x1F,
// 0x23, 0x2C, 0x2D, 0x30, 0x38, 3, 5.
//
// The opcode field is written by `rlwimi r0, K, 0x10, 9, 0xf`, i.e.
//   res->unk0 = (res->unk0 & ~0x7F0000) | (K << 16)
// which is what SET() does.
//
// TWO decode errors the m2c draft made, both systematic:
//  1. It passed a THIRD argument to fn_8012CB2C in every case (1, 2, 0xD, 3, ...).
//     That value is the `rlwimi` opcode constant, not an argument. fn_8012CB2C is
//     (out_ptr, in_ptr) -- two args. The draft's `fn_8012CB2C(&sp8, p, 1)` is
//     really `fn_8012CB2C(&sp8, p)` plus SET(1).
//  2. It read the switch value as `*(r31 - 1)` AFTER `addi r31,r31,1`; want loads
//     the byte from the ORIGINAL pointer (`lbz r0,0(r31)`) and only then does
//     `addi r31,r31,1`, i.e. `switch (arg0[0])` with the cursor pre-incremented.
//     Because arg0 is a `char*` in the draft, that also produced an `extsb`
//     that is NOT in the want -- the parameter type is u8.
//
// Cases 0x1B and 0x1C share a tail: both read a length word and fall into
//   fn_801251B4(r31); res->unk8 = result; r31 += len
// which is why they need the `goto skip_string`, not two separate bodies.
//
// Case 0x23 has a hand-rolled byte-copy loop (`lbz`/`stb` with two counters) and
// NOT a memcpy call -- keep it as a loop; GCC will not generate that shape from
// memcpy.
//
// ------------------------------------------------------------------- parked
// Remaining gap is FPR/frame layout, not semantics:
//   * want: frame -0x80, `stfd f29/f30/f31` at 0x68/0x70/0x78, saved GPRs from
//     0x50, LR at 0x84. got: frame -0x70, saves only f31.
//     The three case-0x1E floats must be live ACROSS fn_80128F44/fn_80124FDC to
//     force three FPR saves. Reproducing that needs the values to be genuinely
//     live there; feeding them from one shared temp collapses the saves to f31,
//     and feeding from three separate stack slots does not lift them into f29/f30
//     at all.
//   * want keeps arg0/arg1/res in r31/r27/r28 and re-uses `li r5,0` as a dead
//     store; got allocates r29/r31/r28 and drops it.
// Size is exact, so the structure and case set are right; this is a codegen-shape
// wall, not a decode gap.
#include "types.h"

typedef union V V;
union V {
    s32 i;
    f32 f;
};

typedef struct Res Res;
struct Res {
    s32 unk0;
    s32 unk4;
    V unk8;
};

/* created by fn_80124FDC / fn_80125000: three floats at +4/+8/+0xc */
typedef struct V3 V3;
struct V3 {
    s32 pad0;
    f32 x;
    f32 y;
    f32 z;
};

/* fn_8012CB2C is TWO-argument: (s32 *out, const char *in). The m2c draft passed a
   third argument which was really the rlwimi opcode constant. */
void fn_8012CB2C(f32 *, const char *);
void fn_8012CB2Ci(s32 *, const char *);
void *fn_801251B4(const char *);
void fn_80128F44(s32);
void *fn_80124FDC(void);
void fn_80128EF4(s32);
void *fn_80125000(void);
void *fn_8012D0D8(const char *);
void *fn_8012B454(const char *, Res *, s32);
s32 fn_801272AC(void *);
void fn_80126808(Res *, s32);
void fn_80019D08(s32);
void *fn_80126EAC(void);
void fn_80126F40(void *, void *);
void fn_8000F2F8(void *, s32);
void fn_8000F320(void *);
void fn_8003E7CC(s32);
void *fn_80128F94(void);
void *fn_8012B7C8(void *, const char *, void *);
void *fn_8012C48C(const char *, void *);
void *fn_800105CC(s32);

extern char lbl_802FFE98[];

#define SET(K) (res->unk0 = (res->unk0 & ~0x7F0000) | ((K) << 16))
#define GLOB (*(void **)lbl_802FFE98)

const char *fn_8012D190(const u8 *arg0, void *arg1, Res *res) {
    const u8 *r31;
    s32 sp8, sp10, sp14, sp18, sp30, sp34;
    f32 sp1C, sp20, sp24, sp28, sp2C;
    s32 len;
    f32 f29, f30, f31;
    void *r30;
    char *r26;
    char *p;
    s32 i;
    void *obj;

    r31 = arg0;
    r30 = 0;

    switch (arg0[0]) {
    case 0x16:
        SET(0xD);
        r31++;
        fn_8012CB2Ci(&sp10, r31);
        r31 += 4;
        res->unk8.i = sp10;
        break;

    case 0x17:
        SET(1);
        r31++;
        fn_8012CB2Ci(&sp8, r31);
        r31 += 4;
        res->unk8.i = sp8;
        break;

    case 0x1A:
        SET(2);
        r31++;
        fn_8012CB2Ci(&sp8, r31);
        r31 += 4;
        res->unk8.f = (f32)(*(s32 *)&sp8);
        break;

    case 0x1B:
        SET(3);
        r31++;
        fn_8012CB2Ci(&sp14, r31);
        r31 += 4;
        len = sp14;
        goto skip_string;

    case 0x1C:
        SET(4);
        r31++;
        fn_8012CB2Ci(&sp18, r31);
        r31 += 4;
        len = sp18;
skip_string:
        obj = fn_801251B4(r31);
        res->unk8.i = (s32)obj;
        r31 += len;
        break;

    case 0x1E:
        SET(6);
        r31++;
        fn_8012CB2C(&sp1C, r31);
        r31 += 4;
        fn_8012CB2C(&sp20, r31);
        r31 += 4;
        fn_8012CB2C(&sp24, r31);
        r31 += 4;
        f29 = sp1C;
        f30 = sp20;
        f31 = sp24;
        fn_80128F44(0x10);
        obj = fn_80124FDC();
        res->unk8.i = (s32)obj;
        ((V3 *)obj)->x = f29;
        ((V3 *)obj)->y = f30;
        ((V3 *)obj)->z = f31;
        break;

    case 0x1F:
        SET(5);
        r31++;
        fn_8012CB2C(&sp28, r31);
        r31 += 4;
        fn_8012CB2C(&sp2C, r31);
        r31 += 4;
        f30 = sp28;
        f31 = sp2C;
        fn_80128EF4(0xC);
        obj = fn_80125000();
        res->unk8.i = (s32)obj;
        ((V3 *)obj)->x = f30;
        ((V3 *)obj)->y = f31;
        break;

    case 0x23:
        r31++;
        fn_8012CB2Ci(&sp30, r31);
        r31 += 4;
        res->unk4 = sp30;
        p = (char *)r31;
        r31 = (const char *)fn_8012D0D8(p);
        SET(7);
        i = (s32)r31 - (s32)p;
        fn_8000F2F8(GLOB, *(s32 *)((char *)GLOB + 0x12C));
        r26 = (char *)fn_800105CC(i);
        fn_8000F320(GLOB);
        for (i = 0; i < (s32)r31 - (s32)p; i++) {
            r26[i] = p[i];
        }
        res->unk8.i = (s32)r26;
        break;

    case 0x2C:
        if (arg1 == NULL) {
            break;
        }
        fn_80019D08(8);
        r30 = fn_80126EAC();
        fn_80126F40(r30, arg1);
        res->unk8.i = (s32)r30;
        SET(0xA);
        break;

    case 0x2D:
        r31++;
        fn_8012CB2Ci(&sp34, r31);
        r31 += 4;
        if (arg1 == NULL) {
            break;
        }
        if (fn_801272AC(arg1) == 0) {
            break;
        }
        fn_80126808(res, 0);
        break;

    case 0x30:
        r31++;
        r31 = (const char *)fn_8012B454(r31, res, 1);
        break;

    case 0x38:
        r31++;
        fn_8012B454(r31, res, 1);
        break;

    case 3:
        r31++;
        fn_80019D08(8);
        r30 = fn_80126EAC();
        r31 = (const char *)fn_8012C48C(r31, arg1);
        res->unk8.i = (s32)r30;
        SET(0xA);
        break;

    case 5:
        r31--;
        fn_8000F2F8(GLOB, *(s32 *)((char *)GLOB + 0x12C));
        fn_8003E7CC(0xC);
        r30 = fn_80128F94();
        fn_8000F320(GLOB);
        r31 = (const char *)fn_8012B7C8(r30, r31, arg1);
        res->unk8.i = (s32)r30;
        SET(0xC);
        break;

    default:
        break;
    }
    return r31;
}