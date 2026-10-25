#!/usr/bin/env python3
"""Round-2 reconstruction sweeps .

80062924: retail folds into ONE rlwimi r0,r4,26,5,5 -> classic
  (w & ~0x04000000) | ((arg1 & 1) << 26).
8005BF08: struct layout is {w0; w1; vtbl@8}, sret; try field orders/ret types.
80261BE0: retail alloc: enabled stays in r3 (dies at restore), val -> r31,
  raw read -> r0. Try decl orders / widths / single-callee-save shapes.
"""
import sys

sys.path.insert(0, 'tools')
import gen_leaves as gl


def score(addr, body, extra_flags=None):
    got, masks = gl.compile_fn(addr, body, extra_flags)
    if got is None:
        return None, None, ['FAIL']
    off = gl.t_off + (addr - gl.t_addr)
    WANT = gl.d[off:off + len(got)]
    n = min(len(got), len(WANT))
    good = tot = 0
    first = []
    for i in range(0, n - 3, 4):
        m = masks.get(i, 0xFFFFFFFF)
        ok = (int.from_bytes(got[i:i+4], 'big') & m) == (int.from_bytes(WANT[i:i+4], 'big') & m)
        tot += 1
        if ok:
            good += 1
        elif len(first) < 5:
            first.append('%04x want=%08x got=%08x' % (i, int.from_bytes(WANT[i:i+4], 'big'),
                                                      int.from_bytes(got[i:i+4], 'big')))
    return len(got), (good, tot), first


def run(tag, addr, body, flags=None):
    ln, sc, first = score(addr, body, flags)
    if sc is None:
        print('%-28s FAIL' % tag)
        return
    g, t = sc
    print('%-28s len=%4d %d/%d (%.3f)%s  %s' % (tag, ln, g, t, g / t,
          '  <<< EXACT' if g == t else '', ' | '.join(first)))


print('== 80062924 ==')
A2 = 0x80062924
v = {}
v['r1_and1_shift'] = '''void fn_80062924(void *arg0, s32 arg1) {
    *(u32 *)((char *)arg0 + 0x48) =
        (*(u32 *)((char *)arg0 + 0x48) & ~0x04000000) | ((arg1 & 1) << 26);
}
'''
v['r2_ne0_shift'] = '''void fn_80062924(void *arg0, s32 arg1) {
    *(u32 *)((char *)arg0 + 0x48) =
        (*(u32 *)((char *)arg0 + 0x48) & ~0x04000000) | ((arg1 != 0) << 26);
}
'''
v['r3_xor_cond'] = '''void fn_80062924(void *arg0, s32 arg1) {
    *(u32 *)((char *)arg0 + 0x48) =
        (*(u32 *)((char *)arg0 + 0x48) & ~0x04000000) | (((arg1 & 1) != 0) << 26);
}
'''
v['r4_boolfield'] = '''void fn_80062924(void *arg0, s32 arg1) {
    struct { u32 pad : 25; u32 b26 : 1; u32 rest : 6; } *p = (void *)((char *)arg0 + 0x48);
    p->b26 = arg1 & 1;
}
'''
v['r5_bitfield_bool_arg'] = '''void fn_80062924(void *arg0, bool arg1) {
    struct { u32 pad : 25; u32 b26 : 1; u32 rest : 6; } *p = (void *)((char *)arg0 + 0x48);
    p->b26 = arg1;
}
'''
v['r6_masked_u8_arg'] = '''void fn_80062924(void *arg0, u8 arg1) {
    struct { u32 pad : 25; u32 b26 : 1; u32 rest : 6; } *p = (void *)((char *)arg0 + 0x48);
    p->b26 = arg1 & 1;
}
'''
for k in sorted(v):
    run('802062924_' + k, A2, v[k])

print('== 8005BF08 ==')
A4 = 0x8005BF08
w = {}
w['s1_w0w1vtbl_ptrret'] = '''typedef struct { s32 w0; s32 w1; void *vtbl; } S7;
extern char lbl_80293770[];
S7 *fn_8005BF08(S7 *out, S7 *src) {
    out->vtbl = (void *)&lbl_80293770;
    out->w0 = src->w0;
    out->w1 = src->w1;
    return out;
}
'''
w['s2_w0w1vtbl_voidret'] = '''typedef struct { s32 w0; s32 w1; void *vtbl; } S7;
extern char lbl_80293770[];
void fn_8005BF08(S7 *out, S7 *src) {
    out->vtbl = (void *)&lbl_80293770;
    out->w0 = src->w0;
    out->w1 = src->w1;
}
'''
w['s3_w0w1vtbl_retvoidptr'] = '''typedef struct { s32 w0; s32 w1; void *vtbl; } S7;
extern char lbl_80293770[];
void *fn_8005BF08(S7 *out, S7 *src) {
    out->vtbl = (void *)&lbl_80293770;
    out->w0 = src->w0;
    out->w1 = src->w1;
    return out;
}
'''
w['s4_structassign'] = '''typedef struct { s32 w0; s32 w1; void *vtbl; } S7;
extern char lbl_80293770[];
S7 *fn_8005BF08(S7 *out, S7 *src) {
    out->vtbl = (void *)&lbl_80293770;
    out->w0 = src->w0;
    out->w1 = src->w1;
    return out;
}
'''
for k in sorted(w):
    run('80206_5BF08_' + k, A4, w[k])

print('== 80261BE0 ==')
A5 = 0x80261BE0
HDR = '''extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32);
'''
x = {}
x['t1_val_first'] = HDR + '''extern u16 lbl_CC00206E;
u32 fn_80261BE0(void) {
    u16 val;
    s32 enabled;

    enabled = OSDisableInterrupts();
    val = lbl_CC00206E & 3;
    OSRestoreInterrupts(enabled);
    return val & 1;
}
'''
x['t2_u32_val'] = HDR + '''extern u16 lbl_CC00206E;
u32 fn_80261BE0(void) {
    u32 val;
    s32 enabled;

    enabled = OSDisableInterrupts();
    val = lbl_CC00206E & 3;
    OSRestoreInterrupts(enabled);
    return val & 1;
}
'''
x['t3_ne_boolret'] = HDR + '''extern u16 lbl_CC00206E;
bool fn_80261BE0(void) {
    u32 val;
    s32 enabled;

    enabled = OSDisableInterrupts();
    val = lbl_CC00206E & 3;
    OSRestoreInterrupts(enabled);
    return (val & 1) != 0;
}
'''
x['t4_inline_expr'] = HDR + '''extern u16 lbl_CC00206E;
u32 fn_80261BE0(void) {
    s32 enabled = OSDisableInterrupts();
    u32 val = lbl_CC00206E & 3;
    OSRestoreInterrupts(enabled);
    return val & 1;
}
'''
x['t5_u8_val'] = HDR + '''extern u16 lbl_CC00206E;
u32 fn_80261BE0(void) {
    u8 val;
    s32 enabled;

    enabled = OSDisableInterrupts();
    val = lbl_CC00206E & 3;
    OSRestoreInterrupts(enabled);
    return val & 1;
}
'''
for k in sorted(x):
    run('80206_61BE0_' + k, A5, x[k])
