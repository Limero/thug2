// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80010258-0x8001033C (228B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

void fn_8000F9C4(s32, s32);

/* vtable: s16 method offset at +8, fn ptr at +C (lha + lwz+mtlr), arg 3 */
typedef struct {
    char pad0x0[8];
    s16 off8;
    char padA[2];
    void *(*fnC)(void *, s32);
} Vt_10258;

typedef struct {
    char pad0x0[0x18];
    Vt_10258 *vt;
} N_10258;

/* Four parallel pointer arrays. Bases at 0x188 / 0x1A4 / 0x1C4 / 0x1E4; the
 * last three are indexed by a shared BYTE offset 4..28, the first is walked
 * by its own byte pointer. */
typedef struct {
    char pad0x0[0x188];
    void *unk0x188[7];
    void *unk0x1A4[8];
    void *unk0x1C4[8];
    void *unk0x1E4[8];
} S_10258;

void fn_80010258(S_10258 *arg0) {
    void **w;
    s32 *a1;
    s32 *a3;
    s32 *a2;
    s32 off;
    register s32 n __asm__("r24");
    register s32 zero __asm__("r25");
    zero = 0;
    w = arg0->unk0x188;
    off = 4;
    n = 7;
    do {
        if (*(s32 *)w != 0) {
            a1 = arg0->unk0x1A4;
            fn_8000F9C4((s32)arg0, *(s32 *)((char *)a1 + off));
            if (*(s32 *)w != 0) {
                Vt_10258 *v = ((N_10258 *)(*(s32 *)w))->vt;
                v->fnC((char *)(*(s32 *)w) + v->off8, 3);
            }
            *(s32 *)((char *)a1 + off) = zero;
            w[0] = (void *)zero;
        }
        if (*(s32 *)((char *)(a2 = arg0->unk0x1C4) + off) != 0) {
            a3 = arg0->unk0x1E4;
            fn_8000F9C4((s32)arg0, *(s32 *)((char *)a3 + off));
            if (*(s32 *)((char *)a2 + off) != 0) {
                Vt_10258 *v = ((N_10258 *)(*(s32 *)((char *)a2 + off)))->vt;
                v->fnC((char *)(*(s32 *)((char *)a2 + off)) + v->off8, 3);
            }
            *(s32 *)((char *)a3 + off) = zero;
            *(s32 *)((char *)a2 + off) = zero;
        }
        w = (void **)((char *)w + 4);
        off = off + 4;
        n = n - 1;
    } while (n != 0);
}
