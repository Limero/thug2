// WIP DRAFT (non-matching until promoted)
// family=m2c range=0x8026B6DC-0x8026BBC4 size=1256B
// PARKED — semantic float→ASCII rebuild; ProDG/SDA verification with
// `-msdata=eabi -G4` is DIFF/MISMATCH (255 words), with emitted .text 0x458
// versus want 0x4E8.
// The body uses the decoded f64 control flow, real helper signatures, and
// explicit fctiwz conversion storage; it is not promotion-ready.
// Remaining mismatch classes are initial classification scheduling, the
// long-lived CR/argument allocation, and loop/padding block layout; the
// conversion slot and decoded arithmetic are now represented in real f64 C.
// SIGNATURE (prologue-audited): u8 *fn_8026B6DC
//     (s32 decpt, s32 fmt /*'f' => fixed*/, s32 flag5,
//      char *prefix6, f64 value)
//   - returns lbl_803AF11C (0xA4-byte .bss digit workspace) always.
//   - r26=a0 compared (cr3) and used as addi r27,r26,+1 → decpt/int-digits.
//   - r25=fmt compared against 0x66 'f' (cr4).
//   - r5 tested once near end (cr2): strip-trailing-zeros flag.
//   - r6 = optional '-' prefix target: negative writes '-' to *r6 when
//     non-NULL, else to workspace[0] (and digits start +1).
// BLOCK MAP (want):
//   0xB708  f30 = value; r26 = a0; r25 = a1(fmt); CR-save mfcr r12
//   0xB714-0xB79C  classify bits of stfd image: exp==0x7FF =>
//       all-zero mantissa ? (sign ? "-Inf" : "Inf") : "NaN"
//       copied into lbl_803AF11C via lwz+lbz (4+1 byte struct copies);
//       jump common tail (return buf).
//   0xB7A0  if (value < 0.0 [fcmpu vs lbl_802B2060]):
//         '-' -> (*pfx6 ? *pfx6 : buf[0]); if !pfx6 digits start buf+1;
//         fneg f30.  else buf base.
//   0xB7F8  cr2 = flag5; f31 = 1.0(lbl_802B2068); cr4 = (fmt=='f');
//         cror cr0un,eq,gt + bns => !(v >= 1.0) scales UP first.
//   0xB81C scale-down (v >= 1.0): bl fn_8026E5DC(v)->floor-ish; f28=10.0;
//         f30 -= res; digit loop (r29 index <= 0xA2):
//         magic-dance digit extract (lis 0x4330/xoris/stfd 0x10(r1)/lwz/
//         xoris 0x8000/addi '0'/stbx), remainder /=10.0, until < 1.0.
//   0xB89C reverse digits in place (same swap shape as fn_8026B614).
//   0xB8CC or. r30,r29,r29 (exp counter = digits written; record!)
//   0xB8D4 'f'-mode && exp==0: store '0'.  else scale-up-by-10 loop
//         while v < 1.0 (fmul 10.0, exp--), lower bound -0x3FD.
//   0xB95C exponent dispatch (r30 sign), r31 = total-length computation
//         (max(decpt+..., 1) shapes incl. cmplw-free max idiom).
//   0xB98C-0xBA14 fractional-digit loop: second magic dance (f12=10.0,
//         f13=lbl_802B2080*10, fctiwz slot r1+0x10 SHARED), rounding window
//         checks vs f11/f13 pairs, per-digit stbx.
//   0xBA18 round-half fixup vs lbl_802B2088 (0.5) then last-digit bump.
//   0xBA3C zero-pad loop while r29 <= r31 ('0' fill).
//   0xBA58 bl fn_8026B5B8(buf, len)  <-- OUR matched odometer-round helper;
//         ret==0 => overflow: buf[0]='1', exp++.
//   0xBA7C cr3(a0)==0 => skip point-insert; else shift-right loop +
//         '.' insert at max(decpt,1) (0xBAC4 stbx '.').
//   0xBAD4 cr2(flag5): strip trailing '0's (walk back over '0', stop at '.',
//         which also gets trimmed) — the addic./beq pre-decrement latch.
//   0xBB04 fmt=='f' => NUL at r31+1 (0xBB80). ELSE exponent append:
//         stbx NUL; '+'/'-' sign; one '0' pad when |exp|<10;
//         bl fn_8026B660(exp, buf+len, 10)  <-- OUR matched itoa!
//   0xBB8C return lbl_803AF11C.
// ASM census: two fctiwz conversion snippets; no whole-body transcription.
#include "types.h"

extern u8 lbl_803AF11C[];
extern f64 lbl_802B2060, lbl_802B2068, lbl_802B2070, lbl_802B2078;
extern f64 lbl_802B2080, lbl_802B2088;
extern char lbl_802B2050[], lbl_802B2058[], lbl_802B205C[];
f64 floor(f64);
f64 fn_8026E750(f64, f64);
s32 fn_8026B5B8(char *, s32);
void fn_8026B660(u32, char *, u32);

typedef struct { u32 word; u8 tail; } str5_t;
typedef struct { u32 word; } str4_t;

u8 *fn_8026B6DC(s32 arg0, s32 arg1, s32 arg2, char *arg3, f64 farg0) {
    register f64 value __asm__("fr30");
    register f64 integer __asm__("fr27");
    register f64 ten __asm__("fr28");
    register f64 bias __asm__("fr29");
    register f64 one __asm__("fr31");
    volatile union {
        f64 d;
        struct { u32 hi; u32 lo; } w;
    } bits;
    volatile union {
        f64 d;
        struct { u32 hi; u32 lo; } w;
    } cvt;
    f64 tmp, eps;
    u8 *p = lbl_803AF11C;
    register s32 decpt __asm__("r26");
    register s32 fmt __asm__("r25");
    register s32 i __asm__("r29") = 0;
    register s32 expcnt __asm__("r30");
    register s32 end __asm__("r31");
    s32 digit;
    s32 lo;
    s32 hi;
    s32 j;
    f64 fint;

    decpt = arg0;
    fmt = arg1;
    value = farg0;
    bits.d = value;
    if ((bits.w.hi & 0x7FF00000) == 0x7FF00000) {
        if ((bits.w.hi & 0x000FFFFF) || bits.w.lo)
            *(str4_t *)lbl_803AF11C = *(str4_t *)lbl_802B205C;
        else if (bits.w.hi & 0x80000000)
            *(str5_t *)lbl_803AF11C = *(str5_t *)lbl_802B2050;
        else
            *(str4_t *)lbl_803AF11C = *(str4_t *)lbl_802B2058;
        return lbl_803AF11C;
    }

    one = lbl_802B2068;
    ten = lbl_802B2070;
    bias = lbl_802B2078;
    if (value < lbl_802B2060) {
        if (arg3 != NULL) {
            *arg3 = '-';
        } else {
            *p = '-';
            p++;
        }
        value = -value;
    }

    if (value >= one) {
        integer = floor(value);
        value = value - integer;
        i = 0;
        while (i <= 0xA2) {
            tmp = fn_8026E750(integer, ten);
            __asm__ volatile("fctiwz %0,%1" : "=f"(fint) : "f"(tmp));
            cvt.d = fint;
            cvt.w.hi ^= 0x80000000;
            digit = cvt.w.hi + '0';
            p[i] = (u8)digit;
            cvt.w.lo = 0x43300000;
            i++;
            integer = (integer - (cvt.d - bias)) / ten;
            if (integer < one)
                break;
        }
        lo = 0;
        hi = i - 1;
        while (lo < hi) {
            u8 a = p[hi];
            u8 b = p[lo];
            p[lo] = a;
            p[hi] = b;
            lo++;
            hi--;
        }
    }

    expcnt = i;
    if (expcnt == 0) {
        if (fmt == 'f') {
            p[0] = '0';
            i = 1;
        } else if (value != lbl_802B2060) {
            while (value < one && i > -0x3FD) {
                value = value * ten;
                i--;
            }
            i--;
            if (value >= one)
                value = value / ten;
        }
    }

    if (expcnt < 0)
        end = decpt + 1;
    else if (fmt != 'f')
        end = decpt + 1 + (expcnt > 0 ? expcnt : 1);
    else
        end = decpt + 1;

    eps = lbl_802B2080;
    for (;;) {
        value = value * ten;
        eps = eps * ten;
        __asm__ volatile("fctiwz %0,%1" : "=f"(fint) : "f"(value));
        cvt.d = fint;
        cvt.w.hi ^= 0x80000000;
        digit = cvt.w.hi + '0';
        cvt.w.lo = 0x43300000;
        value = value - (cvt.d - bias);
        if (value < eps || value > one - eps)
            break;
        p[i++] = (u8)digit;
    }
    if (value >= lbl_802B2088)
        digit++;
    p[i++] = (u8)(digit + '0');
    while (i <= end)
        p[i++] = '0';

    if (fn_8026B5B8((char *)p, end + 1) == 0) {
        p[0] = '1';
        end = decpt + 1;
        expcnt++;
    }

    if (decpt != 0) {
        s32 dot;
        if (fmt == 'f')
            dot = expcnt < 1 ? 1 : expcnt;
        else
            dot = 1;
        j = end;
        while (j > dot) {
            p[j] = p[j - 1];
            j--;
        }
        p[dot] = '.';
    }
    end--;

    if (arg2 != 0 && end != 0) {
        do {
            end--;
            if (end == 0)
                break;
        } while (p[end] == '0');
        if (p[end] == '.')
            end--;
    }

    if (fmt == 'f') {
        p[end + 1] = '\0';
    } else {
        end++;
        p[end] = (u8)fmt;
        if (expcnt < 0) {
            end++;
            p[end] = '-';
            if (expcnt < -10) {
                end++;
                p[end] = '0';
            }
            expcnt = -expcnt;
        } else {
            end++;
            p[end] = '+';
            if (expcnt != 0)
                expcnt--;
            if (expcnt > 9) {
                end++;
                p[end] = '0';
            }
        }
        end++;
        fn_8026B660((u32)expcnt, (char *)(p + end), 10);
    }
    return (u8 *)lbl_803AF11C;
}
