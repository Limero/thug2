// WIP DRAFT (non-matching) — hand-rebuilt from the want disassembly.
// family=m2c range=0x800931C8-0x80093820 size=1624B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress.
//
// ============================ WHY PARKED ============================
// Baseline (m2c dump) was DIFF 9.5% / 1636B. This rewrite decodes the whole
// function from the want and fixes the semantics; the body below is the best
// measured state: DIFF, object 1580B vs want 1624B (11 insns SHORT), masked
// 5.3% (meaningless while the size is off — see AGENTS §6cs-1).
//
// DECODED SEMANTICS (all confirmed against the want, keep it if you resume):
//  * skin(0x48)=src array of 0x40-stride bone rows, skin(0x4C)=count,
//    skin(0x54)->(0x1C)->(0x20)=AttachSet, skin(0x68)=out buffer.
//    AttachSet: +4 entry array, +8 u16 flush_n, +0xA u16 joint_n,
//    +0xC u8 vert_n, +0xD u8 sticker_n.
//  * entry = {s32 n; s32 id; ...}: verts walk +8+12n, joints/stickers +8+16n.
//    Joints pass F444/FA14 take (mats[(u8)id], mats[(u8)(id>>8)], ...).
//  * lbl_8037B674 holds f32s at +0x0C/+0x1C/+0x2C (16-byte spaced).
//  * lbl_80301828 is a s32[6] distance table; dist2 = dz*dz + (dx*dx+dy*dy);
//    idx = #{k<4 : dist > (f32)(f64)tbl[k]}; alpha = 1.0f -
//    (dist - (f32)tbl[idx]) / (f32)(tbl[idx]-tbl[idx+1]);
//    idx<=0 => alpha=1.0f; idx<=1 => joints+stickers, idx>=2 => verts pass.
//  * loop counts: u32 counters (cmplw) except the src-copy loop (s32, cmpw).
//  * `volatile double _dummy` reproduces the want's 0x50 frame (+8 issue-01).
//
// MEASURED / NEGATIVE RESULTS (all DIFF, none helped):
//  * do-while loops lose the pre-test; `for`/`while` keep it (matches want).
//  * GCC/ProDG branches to the *else* block: writing the flag test as
//    `if (lbl_803017F8 == 0) {MODE_A} else {MODE_B}` is what reproduces the
//    want's block order (MODE_B out of line at +0x498).
//  * `(u8)(id>>8)` -> rlwinm r,r,0x18,0x18,0x1f; `n & 0xFFFF` -> clrlwi r,r,0x10
//    (so the F8C4 2nd arg is u16, not (u8)(n>>16) as m2c guessed).
//  * flags tried: -fno-schedule-insns2 / -fno-branch-count-reg / -fno-gcse /
//    -fno-schedule-insns / -fno-tree-pre: all SHRINK or leave the object short.
//  * hoisting the flush size into a variable: 1556B (worse).
//
// REMAINING BLOCKER (11 insns + addressing-mode/register noise):
//  1. The 12-float bone-row copy. The want keeps a byte-offset IV and walks
//     both bases (lfsx/stfsx + lfsu/stfsu with `addi r9,4` every 3 pairs);
//     plain 12 scalar f32 assignments give the want's exact offsets but GCC
//     picks displacement addressing instead (lfs f0,0x10(r9) ...), costing
//     5 insns. Tried: indexed-first + pointer, pointer + indexed-first,
//     incremented pointers, reversed statement order, and an equivalent
//     f32*-with-explicit-indices spelling (byte-identical output to the
//     member form -> the lfsu form is NOT reachable by source restructuring).
//  2. `fmr f13,f0` after the dist2 fmadds (want keeps dist in f13 for the
//     table-search fcmpu; the register choice is not steerable from C).
//  3. Loop bodies load id before n and use `addi rX,e,8` where the want uses
//     `lwzu r0,4(r30)` + `addi r30,4` (reload update-form choice).
//  4. Register allocation: want skin=r27/srcref&walker=r30/out=r26/&extra=r4,
//     this build skin=r27/out=r26/walker=r4/&extra=r7.
//  5. Flush tail: the want PREs the (n_flush+1)*12 load chain out of the
//     if/else diamond; this build reloads it in both arms.
//
// !! PRODG 3.9.3 CODEGEN BUG worth a recipe/parking note: narrowing a fresh
// integer load to `(u8)` is emitted as a load of the WRONG byte. For
// `s32 id = *(s32 *)(e+4); ... mats + (u8)id;` ngccc emits `lbz rX, 7(rE)`
// (bits 24-31) instead of `lbz ..., 4(rE)` — the little-endian byte position
// of the LSB. The joints loops escape it only because they also use
// `(u8)(id>>8)`, which forces the full `lwz`+clrlwi/rlwinm pair the want
// shows. The want's single-extract LOOP_2 uses the full load, so this loop
// needs a form that defeats the narrowing reload before it can match.
// ===================================================================
#include "types.h"

typedef struct {
    f32 x, y, z;
} Vec3;

/* 4 bone rows, 3 floats each (0x30) */
typedef struct {
    f32 x0; f32 y0; f32 z0;
    f32 x1; f32 y1; f32 z1;
    f32 x2; f32 y2; f32 z2;
    f32 x3; f32 y3; f32 z3;
} Mat34;

/* same, but every row is 16-byte padded (0x40) */
typedef struct {
    f32 x0; f32 y0; f32 z0; f32 pad0;
    f32 x1; f32 y1; f32 z1; f32 pad1;
    f32 x2; f32 y2; f32 z2; f32 pad2;
    f32 x3; f32 y3; f32 z3; f32 pad3;
} SrcMat;

typedef struct {
    s32 unk0x00;
    s32 entries;
    u16 n_flush;
    u16 n_joint;
    u8 n_vert;
    u8 n_stick;
} AttachSet;

typedef struct {
    s32 unk0x00[8];
    AttachSet *sets;
} AttachMid;

typedef struct {
    s32 unk0x00[7];
    AttachMid *mid;
    s32 unk0x20[19];
    s32 flag;
} AttachGrp;

typedef struct {
    s32 unk0x00[14];
    Vec3 pos;
    s32 unk0x44;
    SrcMat *src;
    s32 count;
    s32 unk0x50;
    AttachGrp *grp;
    s32 unk0x58[4];
    Vec3 *buf;
} Skin;

/* three 16-byte-spaced floats at +0x0C/+0x1C/+0x2C */
typedef struct {
    s32 unk0x00[3];
    f32 x0;
    f32 unk0x10;
    f32 unk0x14;
    f32 unk0x18;
    f32 x1;
    f32 unk0x20;
    f32 unk0x24;
    f32 unk0x28;
    f32 x2;
} AttachXf;

extern void *fn_80093E14(Skin *self, s32 unused);
extern void DCFlushRange(void *addr, u32 size);
extern void DCFlushRangeNoSync(void *addr, u32 size);
extern void lbl_8028F14C(Mat34 *m, f32 *pos, Vec3 *out, s32 n);
extern void lbl_8028F444(Mat34 *a, Mat34 *b, f32 *w, f32 *pos, Vec3 *out, s32 n, Vec3 *extra);
extern void lbl_8028F698(Mat34 *a, Mat34 *b, f32 *w, f32 *pos, Vec3 *out, s32 n);
extern void lbl_8028F8C4(Mat34 *a, u16 k, f32 *pos, void *buf, s16 *b, f32 *a2, Vec3 *extra);
extern void lbl_8028FA14(Mat34 *a, u16 k, f32 *pos, void *buf, s16 *b, f32 *a2);
extern Vec3 lbl_802971EC;
extern f32 lbl_80297200[];
extern bool lbl_803017F8;
extern s32 lbl_80301828[];
extern f32 lbl_803795D8;
extern AttachXf lbl_8037B674;

void fn_800931C8(Skin *skin, s32 unused, Mat34 *mats, void *srcref) {
    Vec3 extra;
    volatile double _dummy;
    Vec3 *out;
    char *e;
    f32 *pos;
    f32 *w;
    s16 *wa;
    s16 *wb;
    f32 dist;
    f32 alpha;
    f32 lo;
    f32 hi;
    f32 dy;
    f32 dx;
    f32 dz;
    s32 idx;
    s32 ci;
    u32 i;
    u32 j;
    s32 k;
    s32 n;
    s32 id;
    Mat34 *d;
    SrcMat *s;

    if ((skin->src != NULL) && (skin->grp->flag == 0)) {
        skin->buf = (Vec3 *)fn_80093E14(skin, 0);
        if ((srcref != NULL) && (skin->src != srcref)) {
            for (ci = 0; ci < skin->count; ci++) {
                d = &mats[ci];
                s = &skin->src[ci];
                d->x0 = s->x0; d->y0 = s->y0; d->z0 = s->z0;
                d->x1 = s->x1; d->y1 = s->y1; d->z1 = s->z1;
                d->x2 = s->x2; d->y2 = s->y2; d->z2 = s->z2;
                d->x3 = s->x3; d->y3 = s->y3; d->z3 = s->z3;
            }
        }
        extra = lbl_802971EC;
        out = skin->buf;
        e = (char *)&skin->grp->mid->sets->entries;
        if (lbl_803017F8 == 0) {
            dy = lbl_8037B674.x1 - skin->pos.y;
            dx = lbl_8037B674.x0 - skin->pos.x;
            dz = lbl_8037B674.x2 - skin->pos.z;
            dist = dz * dz + (dx * dx + dy * dy);
            lbl_803795D8 = dist;
            idx = -1;
            for (k = 0; k < 4; k++) {
                if (dist > lbl_80301828[k]) {
                    idx++;
                }
            }
            lo = lbl_80301828[idx];
            hi = lbl_80301828[idx] - lbl_80301828[idx + 1];
            alpha = lbl_80297200[0] - (dist - lo) / hi;
            for (i = 0; i < skin->grp->mid->sets->n_vert; i++) {
                n = *(s32 *)e;
                id = *(s32 *)(e + 4);
                pos = (f32 *)(e + 8);
                lbl_8028F14C(mats + id, pos, out, n == 1 ? 2 : n);
                out += n;
                e = (char *)pos + n * 12;
            }
            if (idx <= 0) {
                alpha = lbl_80297200[0];
            }
            if (idx > 1) {
                for (j = 0; j < skin->grp->mid->sets->n_joint; j++) {
                    n = *(s32 *)e;
                    id = *(s32 *)(e + 4);
                    pos = (f32 *)(e + 8);
                    w = pos + n * 3;
                    lbl_8028F14C(mats + (u8)id, pos, out, n == 1 ? 2 : n);
                    out += n;
                    e = (char *)(w + n);
                }
            } else {
                extra.x = alpha;
                for (j = 0; j < skin->grp->mid->sets->n_joint; j++) {
                    n = *(s32 *)e;
                    id = *(s32 *)(e + 4);
                    pos = (f32 *)(e + 8);
                    w = pos + n * 3;
                    lbl_8028F444(mats + (u8)id, mats + (u8)(id >> 8), w, pos, out, n == 1 ? 2 : n, &extra);
                    out += n;
                    e = (char *)(w + n);
                }
                for (i = 0; i < skin->grp->mid->sets->n_stick; i++) {
                    n = *(s32 *)e;
                    id = *(s32 *)(e + 4);
                    pos = (f32 *)(e + 8);
                    wa = (s16 *)(pos + n * 3);
                    wb = wa + n;
                    lbl_8028F8C4(mats + id, n, pos, skin->buf, wb, (f32 *)wa, &extra);
                    e = (char *)wb + n * 2;
                }
            }
        } else {
            for (i = 0; i < skin->grp->mid->sets->n_vert; i++) {
                n = *(s32 *)e;
                id = *(s32 *)(e + 4);
                pos = (f32 *)(e + 8);
                lbl_8028F14C(mats + id, pos, out, n == 1 ? 2 : n);
                out += n;
                e = (char *)pos + n * 12;
            }
            j = 0;
            while (j < skin->grp->mid->sets->n_joint) {
                n = *(s32 *)e;
                id = *(s32 *)(e + 4);
                pos = (f32 *)(e + 8);
                w = pos + n * 3;
                lbl_8028F698(mats + (u8)id, mats + (u8)(id >> 8), w, pos, out, n == 1 ? 2 : n);
                out += n;
                e = (char *)(w + n);
                j++;
            }
            for (i = 0; i < skin->grp->mid->sets->n_stick; i++) {
                n = *(s32 *)e;
                id = *(s32 *)(e + 4);
                pos = (f32 *)(e + 8);
                wa = (s16 *)(pos + n * 3);
                wb = wa + n;
                lbl_8028FA14(mats + id, n, pos, skin->buf, wb, (f32 *)wa);
                e = (char *)wb + n * 2;
            }
        }
        if (lbl_803017F8 == 0) {
            DCFlushRangeNoSync(skin->buf, (skin->grp->mid->sets->n_flush + 1) * 12);
        } else {
            DCFlushRange(skin->buf, (skin->grp->mid->sets->n_flush + 1) * 12);
        }
    }
}
