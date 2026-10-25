#include <dolphin/dolphin.h>
#include <dolphin/mtx.h>
#include <sdk_math.h>

// Constants externed to auto-asm (extern route, docs/dolphin-sdk.md s9.17).
extern const f32 lbl_803CB010;  // 1.0f
extern const f32 lbl_803CB014;  // 2.0f
extern const f32 lbl_803CB018;  // 0.0f
extern const f32 lbl_803CB01C;  // -1.0f


// C_MTXFrustum (0x8025E774). Was parked as a pure-regalloc coin-flip
// (docs/parkings/solved/39-mtx-c-mtxfrustum.md): the natural tmp-statement form
// (m[0][0] = (lbl_803CB014 * n) * tmp) compiles with retail's exact
// allocation but emits both prod*div fmuls operands swapped
// (fmuls f0,f11,f8 vs retail f0,f8,f11). Inlining the division fixes the
// order but rotates the allocation. The form below fixes both: naming
// each site's (2.0*n) product in its own short-lived temp (prod0/prod1)
// keeps mwcc from re-associating the anonymous a*b*c chain, so the final
// multiply emits prod-first like retail with no allocation drift. Do NOT
// merge prod0/prod1 into one reused variable (rotates allocation, 7 diffs)
// and do NOT inline the product anonymously (swaps the fmuls back, 2 diffs).
// The product must stay (const * n) order: (n * const) swaps the prod's
// own fmuls. Verified byte-exact with GC/1.2.5n via tools/mwcc_verify.py.
void C_MTXFrustum(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f) {
    f32 tmp;
    f32 prod0;
    f32 prod1;

    ASSERTMSGLINE(105, m, "MTXFrustum():  NULL Mtx44Ptr 'm' ");
    ASSERTMSGLINE(106, t != b, "MTXFrustum():  't' and 'b' clipping planes are equal ");
    ASSERTMSGLINE(107, l != r, "MTXFrustum():  'l' and 'r' clipping planes are equal ");
    ASSERTMSGLINE(108, n != f, "MTXFrustum():  'n' and 'f' clipping planes are equal ");
    tmp = lbl_803CB010 / (r - l);
    prod0 = lbl_803CB014 * n;
    m[0][0] = prod0 * tmp;
    m[0][1] = lbl_803CB018;
    m[0][2] = tmp * (r + l);
    m[0][3] = lbl_803CB018;
    m[1][0] = lbl_803CB018;
    tmp = lbl_803CB010 / (t - b);
    prod1 = lbl_803CB014 * n;
    m[1][1] = prod1 * tmp;
    m[1][2] = tmp * (t + b);
    m[1][3] = lbl_803CB018;
    m[2][0] = lbl_803CB018;
    m[2][1] = lbl_803CB018;
    tmp = lbl_803CB010 / (f - n);
    m[2][2] = (-n * tmp);
    m[2][3] = (tmp * -(f * n));
    m[3][0] = lbl_803CB018;
    m[3][1] = lbl_803CB018;
    m[3][2] = lbl_803CB01C;
    m[3][3] = lbl_803CB018;
}

void C_MTXOrtho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f) {
    f32 tmp;

    ASSERTMSGLINE(254, m, "MTXOrtho():  NULL Mtx44Ptr 'm' ");
    ASSERTMSGLINE(255, t != b, "MTXOrtho():  't' and 'b' clipping planes are equal ");
    ASSERTMSGLINE(256, l != r, "MTXOrtho():  'l' and 'r' clipping planes are equal ");
    ASSERTMSGLINE(257, n != f, "MTXOrtho():  'n' and 'f' clipping planes are equal ");
    tmp = lbl_803CB010 / (r - l);
    m[0][0] = lbl_803CB014 * tmp;
    m[0][1] = lbl_803CB018;
    m[0][2] = lbl_803CB018;
    m[0][3] = (tmp * -(r + l));
    tmp = lbl_803CB010 / (t - b);
    m[1][0] = lbl_803CB018;
    m[1][1] = lbl_803CB014 * tmp;
    m[1][2] = lbl_803CB018;
    m[1][3] = (tmp * -(t + b));
    m[2][0] = lbl_803CB018;
    m[2][1] = lbl_803CB018;
    tmp = lbl_803CB010 / (f - n);
    m[2][2] = (lbl_803CB01C * tmp);
    m[2][3] = (-f * tmp);
    m[3][0] = lbl_803CB018;
    m[3][1] = lbl_803CB018;
    m[3][2] = lbl_803CB018;
    m[3][3] = lbl_803CB010;
}





