// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007F284-0x8007F318 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

extern f32 lbl_80296260;
extern f32 lbl_80296264;

/* One 8-byte paired-single pair with a scalar-lane view (SN_PS_type shape). */
typedef union {
    __ps_t ps;
    f32 f[2];
} S7F284_Q;

/* The 16-byte f32 quad this function fills (arg0). */
typedef struct {
    S7F284_Q q[2];
} S7F284_V;

/* Holder of a 16-byte f32 quad at +0x30. */
typedef struct {
    char pad0x00[0x30];
    S7F284_Q quad[2];
} S7F284_QS;

/* Node B: its own quad at +0x48, a link at +0x58, an enable flag at +0x6C. */
typedef struct {
    char pad0x00[0x48];
    S7F284_Q quad[2];
    void *unk0x58;
    char pad0x5C[0x10];
    s32 unk0x6C;
} S7F284_B;

/* Second hop of the case-2 walk: the quad holder lives at +0x20. */
typedef struct {
    char pad0x00[0x20];
    S7F284_QS *unk0x20;
} S7F284_X;

/* First hop of the case-2 walk: the second hop lives at +0x14. */
typedef struct {
    char pad0x00[0x14];
    S7F284_X *unk0x14;
} S7F284_L;

/* Node A: a flag at +0x48 and a link to node B at +0x54. */
typedef struct {
    char pad0x00[0x48];
    s32 unk0x48;
    char pad0x4C[0x8];
    S7F284_B *unk0x54;
} S7F284_A;

typedef struct {
    char pad0x00[0x30];
    S7F284_A *unk0x30;
} S7F284_ARG1;

void fn_8007F284(S7F284_V *out, S7F284_ARG1 *arg1) {
    S7F284_A *a;
    S7F284_L *l;
    S7F284_B *b;
    S7F284_QS *q;

    a = arg1->unk0x30;
    if (a != NULL) {
        b = a->unk0x54;
        if (b != NULL) {
            if (a->unk0x48 != 0 && b->unk0x6C != 0) {
                out->q[0].ps = b->quad[0].ps;
                out->q[1].ps = b->quad[1].ps;
                return;
            }
            l = *(S7F284_L **)b->unk0x58;
            if (l != NULL) {
                q = l->unk0x14->unk0x20;
                out->q[0].ps = q->quad[0].ps;
                out->q[1].ps = q->quad[1].ps;
                return;
            }
        }
    }
    out->q[0].f[0] = lbl_80296260;
    out->q[0].f[1] = lbl_80296260;
    out->q[1].f[0] = lbl_80296260;
    out->q[1].f[1] = lbl_80296264;
}
