// WIP DRAFT (non-matching) — C body rebuilt by hand from the disasm
// family=m2c range=0x8013809C-0x80138334 size=664B
// PARKED 2026-10-06. Official verdict: object
// 540B vs want 664B, 133/166 words differ (1.48% masked) — the masked score is
// MEANINGLESS until the size matches (AGENTS §6cs-1/§6es; got is 31 words
// short). Body kept = best structural decode.
//
// DECODE (all from the WANT; the body below implements exactly this): leaf
// RLE packet compressor, frame 0xa0, `stmw r28,0x90`, NO LR save and no `bl`
// (pure leaf). r6=src(r3), r28=dst base(r5), r3=dst cursor, r7=`len`, r5=`prev`,
// r30=`cur`, r29/r12=r1+8 (`win`). win[136] sits at r1+8..0x8F, i.e. exactly the
// 136 bytes between the 8-byte locals head and the 0x90 saved-register block.
// Control byte: bit7 clear -> literal run of (ctrl+1) bytes; bit7 set -> RLE of
// (ctrl&0x7f)+1 copies of the next byte. Return = `subf r3,r28,r3` (dst - arg2).
// `clrlwi r7,r0,0x18` at 0x8013810C/0x801381F8 confirms `u8 len`; `--count`
// never re-truncates, so `count` is a full-width int in the WANT.
//
// WHY IT CANNOT CLOSE FROM C HERE: WANT homes `count` in CTR — set from r0
// at entry, branching on the counter hitting zero for every countdown test,
// and restoring the counter explicitly where the old value must be kept.
// ngccc emits a GPR-based decrement-and-branch instead, i.e. a GPR counter. That is a
// global-alloc / -fbranch-count-reg home choice, not a source shape: every
// `--arg1` test in the body is already the decoded one, and the goto-CFG block
// order matches the WANT. Same class as the doc-15 allocator walls.
//
// CALLER EVIDENCE (src/wip/fn_80137CF8.c:53,79 — the wrapper that also picks
// fn_8000AC98 for case 2): it declares 4 args `(u8 *arg0, u16 arg1, u8 *arg2,
// u32 arg3)` and calls `fn_8013809C(buf, sp8, out+3, cap)`. The WANT clobbers
// r6 immediately (`mr r6,r3` at 0x801380A8), so the 4th arg (capacity) is NOT
// read — the 3-arg prototype kept here is the codegen-correct one, and the
// caller is passing a dead extra. The matched LZ77 compressor is
// src/fn_8000AC98.c (case 2); fn_8013809C is case 1 (RLE) and shares no
// reusable idiom with it.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// RLE/LZ packet compressor: fn(src_bytes, count, dst) -> bytes written.
//   ctrl byte: bit7 clear -> literal run of (ctrl+1) bytes; bit7 set -> RLE of
//   (ctrl&0x7f)+1 copies of the next byte.
#include "types.h"
s32 fn_8013809C(u8 *arg0, s32 arg1, u8 *arg2) {
    u8 win[136];
    u8 *src = arg0;
    u8 *dst = arg2;
    u8 *t1;
    u8 prev;
    u8 cur;
    u8 len;
    s32 i;
    s32 n;

    if (arg1 != 0) {
    head_a:
        prev = *src++;
        if (--arg1 == 0)
            goto end;
    head_b:
        cur = *src++;
        arg1--;
        len = 2;
    outer:
        if (prev != cur) {
            win[0] = prev;
            win[1] = cur;
            t1 = dst + 1;
            if (arg1 != 0) {
                n = len - 2;
                if (win[n] == win[n + 1])
                    goto run;
                if (len & 0x80)
                    goto checkrun;
            scan2:
                win[len] = *src++;
                len = len + 1;
                if (--arg1 == 0)
                    goto checkrun;
                n = len - 2;
                if (win[n] == win[n + 1])
                    goto run;
                if (!(len & 0x80))
                    goto scan2;
            }
        checkrun:
            n = len - 2;
            if (win[n] != win[n + 1])
                goto literal;
        run:
            dst[0] = len - 3;
            dst = t1;
            for (i = 0; i < n; i++)
                dst[i] = win[i];
            prev = win[n];
            cur = prev;
            len = 2;
            goto tail2;
        literal:
            dst[0] = len - 1;
            dst = t1;
            for (i = 0; i < len; i++)
                dst[i] = win[i];
            prev = *src++;
            if (--arg1 != 0)
                goto head_b;
            len = 0;
            goto tail2;
        }
        t1 = dst + 1;
        if (arg1 != 0 && len <= 0x80) {
        scan1:
            len = len + 1;
            cur = *src++;
            if (--arg1 == 0)
                goto emit;
            if (prev != cur)
                goto emit2;
            if (len <= 0x80)
                goto scan1;
        }
    emit:
        if (prev != cur)
            goto emit2;
        dst[0] = len + 0x7E;
        i = arg1;
        dst = t1;
        dst[0] = prev;
        dst++;
        if (i == 0) {
            len = 0;
        } else {
            prev = *src++;
            arg1 = i - 1;
            len = 1;
        }
        if (arg1 != 0)
            goto head_b;
        goto tail2;
    emit2:
        dst[0] = len + 0x7D;
        len = 1;
        dst = t1;
        dst[0] = prev;
        dst++;
        prev = cur;
        if (arg1 != 0)
            goto head_b;
    tail2:
        if (arg1 != 0)
            goto outer;
        if (len > 1)
            goto outer;
        if (len != 1)
            goto end;
        dst[0] = 0;
        dst[1] = prev;
        dst += 2;
        if (arg1 != 0)
            goto head_a;
    }
end:
    return dst - arg2;
}
