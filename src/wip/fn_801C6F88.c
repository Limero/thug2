// WIP DRAFT (non-matching) — hand-rebuilt structural sketch from ps_disasm
// family=hand range=0x801C6F88-0x801C7ABC size=2868B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
// PARKED <15% (doc-29 VMX wall): the body is saturated with AltiVec integer
// SIMD (vmsumshm/vmhaddshs/vsel + raw opcode-4 words, ~153 sites of 717 insns)
// implementing s16-vector dot products on the fn_801AE5A4 matrix outputs.
// ngccc has no VMX backend and no builtin route (docs/parkings/29); only
// .word inline asm could emit them, which cannot reproduce the surrounding
// psq/call scheduling at this density. Scalar stand-ins below keep the
// function compiling and preserve the observable call/branch structure.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_802ACD84;
extern f32 lbl_802ACD88;
extern f32 lbl_802ACD8C;
extern f32 lbl_802ACD90;
extern f32 lbl_802ACD94;
extern void *lbl_80305EAC;

void fn_801AE5A4(void *, Unk_C8FEE62D *, Unk_C7387A53 *);
void fn_80005A90(Unk_C1F9F519 *, Unk_C1F9F519 *);
void fn_80005A18(void *, void *);
void *fn_800E9D30(Unk_C7387A53 *, s32);
f32 fn_8014030C(s32, s32, Unk_FFAD6788 *);
f32 cosf(f32);
s32 fn_801ADCE4(void *, void *);

/* scalar stand-in for the game's VMX s16 dot-product block */
static inline f32 vmdot(const void *a, const void *b) {
    const s16 *x = a;
    const s16 *y = b;
    return (f32)(x[0] * y[0] + x[1] * y[1] + x[2] * y[2] + x[3] * y[3]);
}

void *fn_801C6F88(void *arg0, void *arg1, f32 farg0) {
    Unk_C7387A53 *self = arg0;
    Unk_C7387A53 *board = arg1;
    f32 scale = farg0;
    Unk_C7387A53 *mgr;
    void *mtx;
    Unk_C7387A53 *other;
    CStruct *state;
    f32 entry;
    f32 f30;
    f32 f12;
    f32 f13;
    f32 f31;
    f32 f0;
    f32 f8;
    Unk_7B4ED2DB ok;
    s32 noCos;

    mgr = *(void **)&lbl_80305EAC;
    other = *((void * *)&board->unk0x48);
    mtx = *((void * *)&mgr->unk0x28);
    state = *((void * *)&self->unk0xC);
    if (other == NULL) {
        return NULL;
    }
    *((s32 *)&ok) = 1;

    fn_801AE5A4((void *)((char *)&ok + 0), mtx, other);
    fn_801AE5A4((void *)((char *)&ok + 0x10), mtx, board);

    f30 = lbl_802ACD84;
    f12 = scale;
    entry = fn_8014030C(QB_PHYSICS_RAIL_GRAVITY, 1, state);
    f12 = f30 / ok.unk0x70;
    ((Unk_F3F81A2F *)&ok)->unk0x80 = f12;
    ok.unk0x18 = lbl_802ACD88;
    *(f32 *)((char *)(&ok) + 8) = lbl_802ACD88;
    ok.unk0x24 = f30;
    fn_80005A90((void *)((char *)&ok + 0x18), (void *)((char *)&ok + 8));

    if (ok.unk0x90 < lbl_802ACD88) {
        f30 = lbl_802ACD8C;
    }

    noCos = 0;
    if (f30 < lbl_802ACD88) {
        if ((*((void * *)&board->unk0x4C) != NULL) && (fn_800E9D30(board, 2) != NULL)) {
            fn_801AE5A4((void *)((char *)&ok + 0x58), mtx, other);
            fn_801AE5A4((void *)((char *)&ok + 0x68), mtx, board);
            fn_801AE5A4((void *)((char *)&ok + 0x58), mtx, board);
            fn_801AE5A4((void *)((char *)&ok + 0x68), mtx,
                        *((void * *)&board->unk0x4C));
            ok.unk0x2C = lbl_802ACD88;
            ok.unk0x3C = lbl_802ACD88;
            if (0.0f > lbl_802ACD88) {
                ok.unk0x9C = lbl_802ACD84;
            }
            if (0.0f > lbl_802ACD88) {
                ok.unk0xA4 = lbl_802ACD84;
            }
            f13 = ok.unk0xA8;
        } else {
            goto setNoCos;
        }
    } else {
        if ((*((void * *)&other->unk0x48) != NULL) && (fn_800E9D30(board, 2) != NULL)) {
            fn_801AE5A4((void *)((char *)&ok + 0x58), mtx, board);
            fn_801AE5A4((void *)((char *)&ok + 0x68), mtx, other);
            fn_801AE5A4((void *)((char *)&ok + 0x58), mtx, other);
            fn_801AE5A4((void *)((char *)&ok + 0x68), mtx,
                        *((void * *)&other->unk0x48));
            ok.unk0x2C = lbl_802ACD88;
            ok.unk0x3C = lbl_802ACD88;
            if (0.0f > lbl_802ACD88) {
                ok.unk0xB4 = lbl_802ACD84;
            }
            if (0.0f > lbl_802ACD88) {
                ((Unk_F3F81A2F *)&ok)->unk0xBC = lbl_802ACD84;
            }
            f13 = ok.unk0xC0;
        } else {
setNoCos:
            noCos = 1;
            f13 = lbl_802ACD88;
        }
    }
    if (f13 < cosf(fn_8014030C(QB_RAIL_CORNER_LEAVE_ANGLE, 1, state) * lbl_802ACD90)) {
        noCos = 1;
    }

    f0 = 0.0f;
    if (f30 < lbl_802ACD88) {
        fn_801AE5A4((void *)((char *)&ok + 0x38), mtx, other);
        f0 = ok.unk0xC8;
    } else {
        fn_801AE5A4((void *)((char *)&ok + 0x38), mtx, board);
        f0 = ok.unk0xD0;
    }
    if (f0 > (ok.unk0x70 + lbl_802ACD94)) {
        f0 -= ok.unk0x70;
        if ((f30 < lbl_802ACD88) &&
            (*((void * *)&board->unk0x4C) != NULL) &&
            (fn_800E9D30(board, 2) != NULL) &&
            (fn_801AE5A4((void *)((char *)&ok + 0x28), mtx, board),
             fn_801AE5A4((void *)((char *)&ok + 0x38), mtx,
                         *((void * *)&board->unk0x4C)),
             (fn_801ADCE4((void *)((char *)&ok + 0x28),
                          (void *)((char *)&ok + 0x38)) == 0)) &&
            (noCos == 0)) {
            fn_801AE5A4((void *)((char *)&ok + 0x28), mtx, board);
            board = *((void * *)&board->unk0x4C);
        } else if ((*((void * *)&other->unk0x48) != NULL) &&
                   (fn_800E9D30(other, 2) != NULL) &&
                   (fn_801AE5A4((void *)((char *)&ok + 0x28), mtx, other),
                    fn_801AE5A4((void *)((char *)&ok + 0x38), mtx,
                                *((void * *)&other->unk0x48)),
                    (fn_801ADCE4((void *)((char *)&ok + 0x28),
                                 (void *)((char *)&ok + 0x38)) == 0)) &&
                   (noCos == 0)) {
            fn_801AE5A4((void *)((char *)&ok + 0x28), mtx, other);
            board = other;
        } else {
            *((s32 *)&ok) = 0;
        }
    }

    if (*((s32 *)&ok) != 0) {
        fn_801AE5A4((void *)((char *)&ok + 0x48), mtx,
                    *((void * *)&board->unk0x48));
        fn_801AE5A4(state, mtx, board);
        f8 = lbl_802ACD88;
        ok.unk0xDC = lbl_802ACD84;
        if (ok.unk0xE0 < f8) {
            f31 = lbl_802ACD8C;
        } else {
            f31 = lbl_802ACD84;
        }
        ok.unk0xE8 = f31;
        ok.unk0xF0 = f31;
        fn_80005A18((self->unk0xC + 0xB8),
                    ((char *)&ok + 0xE8));
        f8 = lbl_802ACD88;
        if (0.0f > f8) {
            ok.unk0xFC = lbl_802ACD84;
        }
        f13 = *((f32 *)&state->unk0xA0);
        *((f32 *)&state->unk0x78) = f13;
        f0 = -*((f32 *)&state->unk0x98);
        *((f32 *)&state->unk0x84) = f8;
        *((f32 *)&state->unk0x80) = f0;
        *((f32 *)&state->unk0x7C) = f8;
        if (f13 > f8) {
            ok.unk0x104 = lbl_802ACD84;
            f0 = 0.0f;
        }
        ok.unk0x10C = lbl_802ACD84;
        if (f0 > f8) {
            ok.unk0x114 = lbl_802ACD84;
        }
        ok.unk0x120 = f30;
        ok.unk0x118 = scale;
        return board;
    }
    return NULL;
}
