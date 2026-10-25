// WIP DRAFT (non-matching) — hand-reconstructed from the DOL disassembly.
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 1.2945% -> 8.7379% per-object flags: -mps-float -> -fno-gcse -mps-float
// family=hand range=0x800EC8C4-0x800ECD98 size=1236B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// REWRITTEN 2026-10-06: replaced the m2c body (`0;` placeholders for the
// four paired-single copies, phantom `(s32 *)1` args) with a semantic
// reconstruction.  Every QB key, spill slot, loop bound, list splice and
// virtual call is decoded from the WANT; see the note at the end of the file
// for the three known residual mismatches.
// FLAG: -fno-gcse
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_8029ADB8[]; /* .rodata2: 0.0f  (segment default)      */
extern f32 lbl_8029ADBC[]; /* .rodata2: 3.0f  (segment unk0x40)      */
extern f32 lbl_8029ADC8[]; /* .rodata2: 1.0f  (segment vec.w)        */

s32 GetStructure_2(CStruct *param, s32 hash, CStruct **out, s32 def);
s32 GetChecksum_2(void *obj, s32 hash, s32 *out, s32 def);
s32 GetArray(CStruct *param, s32 hash, void **out, s32 def);
s32 GetInteger(void *obj, s32 hash, s32 *out, s32 def);
s32 GetFloat(void *obj, s32 hash, f32 *out, s32 def);
s32 GetVector(void *obj, s32 hash, f32 *out, s32 def);
s32 ContainsFlag(void *obj, s32 hash);
void fn_80070B74(void *obj, s32 a, s32 b, s32 c);
void fn_80070BA8(void *obj);
void *fn_8009B9F0(void *mem, s32 flag);
void *fn_800EC39C(void *mem);
void *Mem_Alloc2(s32 size);

typedef struct Part Part;
typedef struct Seg Seg;

/* Virtual table reached through Part::unk0x20; the two methods called here
 * live at +0x44 (set a segment vector) and +0x84 (enable/disable a part).
 * Each method is addressed as `this = (char *)obj + vt->unk0x40/0x80` where
 * unk0x40/unk0x80 are SIGNED halfword offsets (lha in the WANT). */
typedef struct {
    char pad0x00[0x40];
    s16 unk0x40;
    char pad0x42[0x2];
    void *unk0x44;
    char pad0x48[0x38];
    s16 unk0x80;
    char pad0x82[0x2];
    void *unk0x84;
} PartVtbl;

struct Part {
    void *unk0x00;
    void *unk0x04;
    s32 unk0x08; /* QB_BLEND */
    s32 unk0x0C;
    s32 unk0x10;
    char pad0x14[0xC];
    PartVtbl *vtbl; /* 0x20 */
};

/* 16 bytes copied around as 8 byte paired-single pairs (psq_l/psq_st). */
typedef union {
    struct {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    } f;
    struct {
        __ps_t lo;
        __ps_t hi;
    } p;
} Vec4;

struct Seg {
    Vec4 v0; /* 0x00 */
    Vec4 v1; /* 0x10 = v0 */
    Vec4 v2; /* 0x20 (untouched here) */
    Vec4 v3; /* 0x30 = v0 */
    f32 unk0x40;
    f32 unk0x44;
    char pad0x48[0x4];
    Part *unk0x4C;
};

typedef struct ChainObj ChainObj;
typedef struct ChainNode ChainNode;

struct ChainNode {
    ChainObj *unk0x0;
    ChainNode *unk0x4;
    ChainNode *unk0x8;
};

typedef struct {
    ChainNode *head;
    u32 count;
} ChainList;

struct ChainObj {
    s32 unk0x00; /* chainid */
    s32 unk0x04; /* bone_start */
    f32 unk0x08; /* start_offset x/y/z */
    f32 unk0x0C;
    f32 unk0x10;
    char pad0x14[0x4];
    s32 unk0x18; /* bone_end */
    s32 unk0x1C; /* obj_end */
    u32 unk0x20; /* segment count (segments + 1) */
    char pad0x24[0x4];
    Seg seg[20]; /* 0x28 .. 0x668 */
    s32 unk0x668;
    f32 unk0x66C; /* damp_force */
    f32 unk0x670; /* gravity_force */
    s32 unk0x674; /* local_space */
    f32 unk0x678; /* coll_plane_offset */
    s32 unk0x67C;
    s32 unk0x680;
    s32 unk0x684;
};

typedef struct {
    ChainObj *unk0x0;
    char pad0x04[0x0];
    u32 count; /* 0x04 */
} ChainArray;

/* The object that owns the chain list (arg0). */
typedef struct {
    char pad0x00[0x1C];
    ChainList unk0x1C; /* head @0x1C, count @0x20 */
    char pad0x24[0x18];
    s32 unk0x3C;
    s32 unk0x40;
    s32 unk0x44;
} ChainMgr;

void fn_800EC8C4(ChainMgr *arg0, CStruct *arg1) {
    CStruct *info; /* sp+0x10 */
    ChainArray *arr; /* sp+0x14 */
    s32 segCount; /* sp+0x18 */
    f32 length; /* sp+0x1C */
    s32 chainId; /* sp+0x20 */
    s32 scratch; /* sp+0x24 */
    void *elem;
    ChainObj *obj;
    ChainNode *head;
    ChainNode *node;
    Seg *seg;
    u32 i;
    s32 j;

    info = 0;
    arr = 0;
    if (GetStructure_2(arg1, QB_COLLISION_INFO, &info, 1) != 0) {
        GetChecksum_2(info, 0x0078395B, &arg0->unk0x3C, 0);
        GetChecksum_2(info, QB_BONE_RIGHT, &arg0->unk0x40, 0);
        GetChecksum_2(info, QB_BONE_CENTER, &arg0->unk0x44, 0);
    }
    GetArray(arg1, QB_CHAINS, &arr, 1);
    for (i = 0; i < arr->count; i++) {
        elem = fn_80129528(arr, i);
        segCount = 0;
        GetInteger(elem, QB_SEGMENTS, &segCount, 1);
        length = lbl_8029ADB8[0];
        GetFloat(elem, QB_LENGTH, &length, 1);
        chainId = 0;
        GetChecksum_2(elem, QB_CHAINID, &chainId, 1);

        obj = fn_800EC39C(Mem_Alloc2(0x688));
        scratch = 0;
        obj->unk0x00 = chainId;
        obj->unk0x20 = segCount + 1;
        obj->unk0x674 = ContainsFlag(elem, QB_LOCAL_SPACE);
        GetChecksum_2(elem, QB_BONE_START, &obj->unk0x04, 0);
        GetVector(elem, QB_START_OFFSET, &obj->unk0x08, 1);
        GetChecksum_2(elem, QB_BONE_END, &obj->unk0x18, 1);
        GetChecksum_2(elem, QB_OBJ_END, &obj->unk0x1C, 1);
        GetFloat(elem, QB_GRAVITY_FORCE, &obj->unk0x670, 1);
        GetFloat(elem, QB_DAMP_FORCE, &obj->unk0x66C, 1);
        GetInteger(elem, QB_CONSTRAINT_UPDATES_PER_SEC, &scratch, 1);
        obj->unk0x668 = scratch;
        obj->unk0x684 = ContainsFlag(elem, QB_COLL_LEFT_BIAS);
        GetFloat(elem, QB_COLL_PLANE_OFFSET, &obj->unk0x678, 0);
        GetInteger(elem, QB_COLL_ON_LINK, &scratch, 0);
        obj->unk0x67C = scratch;
        GetInteger(elem, QB_COLL_OFF_LINK, &scratch, 0);
        obj->unk0x680 = scratch;

        for (j = 0; j < (s32)obj->unk0x20; j++) {
            seg = &obj->seg[j];
            seg->unk0x40 = lbl_8029ADBC[0];
            seg->v0.f.x = lbl_8029ADB8[0];
            seg->v0.f.y = lbl_8029ADB8[0];
            seg->v0.f.z = lbl_8029ADB8[0];
            seg->v0.f.w = lbl_8029ADC8[0];
            seg->unk0x44 = length / (f32)segCount;
            seg->v1.p.lo = seg->v0.p.lo;
            seg->v1.p.hi = seg->v0.p.hi;
            seg->v3.p.lo = seg->v0.p.lo;
            seg->v3.p.hi = seg->v0.p.hi;
            if (j < (s32)(obj->unk0x20 - 1)) {
                seg->unk0x4C = fn_8009B9F0(Mem_Alloc2(0x54), 1);
                seg->unk0x4C->unk0x08 = QB_BLEND;
                fn_80070B74(seg->unk0x4C, 1, 0, 2);
                ((void (*)(void *, s32, u32))seg->unk0x4C->vtbl->unk0x84)(
                    (char *)seg->unk0x4C + seg->unk0x4C->vtbl->unk0x80, 0, 0xFF808080);
                ((void (*)(void *, s32, f32, f32, f32))seg->unk0x4C->vtbl->unk0x44)(
                    (char *)seg->unk0x4C + seg->unk0x4C->vtbl->unk0x40, 0,
                    seg->v0.f.x, seg->v0.f.y, seg->v0.f.z);
                ((void (*)(void *, s32, u32))seg->unk0x4C->vtbl->unk0x84)(
                    (char *)seg->unk0x4C + seg->unk0x4C->vtbl->unk0x80, 1, 0xFF808080);
                ((void (*)(void *, s32, f32, f32, f32))seg->unk0x4C->vtbl->unk0x44)(
                    (char *)seg->unk0x4C + seg->unk0x4C->vtbl->unk0x40, 1,
                    seg->v0.f.x, seg->v0.f.y, seg->v0.f.z);
                seg->unk0x4C->unk0x10 = 1;
                fn_80070BA8(seg->unk0x4C);
            }
        }

        head = arg0->unk0x1C.head;
        node = Mem_Alloc2(0xC);
        node->unk0x0 = obj;
        node->unk0x8 = head->unk0x8;
        arg0->unk0x1C.count = arg0->unk0x1C.count + 1;
        node->unk0x4 = head;
        head->unk0x8 = node;
        node->unk0x8->unk0x4 = node;
    }
}

// PARKED 2026-10-06: 309-instruction chain/physics initialiser; semantics,
// keys, spill slots, loop bounds, list splice and virtual-call shapes are all
// decoded (above), but three things keep it off byte-exact:
//   1. PAIRED SINGLE.  The want copies the 16-byte v0 block into +0x10 and
//      +0x30 as four `psq_l/psq_st` pairs (0x800ECBF0-0x800ECC0C).  This body
//      models them as `__ps_t` pairs + `-mps-float`; whether the allocator
//      picks the same 4 pairs (and leaves the three 0.0f/1.0f/3.0f stfs scalar)
//      is the single biggest unknown.  Earlier m2c body scored 6.2% under the
//      scalar flag set.
//   2. MAGIC DOUBLE.  `length / (f32)segCount` is an int->double dance whose
//      bias constant the want takes from .rodata2:0x8029ADC0 (defined by the
//      r2d_8029AD70.c data unit, 2^52+2^31).  ngccc emits its own anonymous
//      pool entry for `(f64)s32`, so that `lis/lfd` pair cannot land on the
//      data-unit symbol without hand-rolling the conversion.
//   3. REGALLOC / SPILL.  The body walks each segment through two identical
//      live pointers (WANT r30 and r31 both start at `obj+0x28+j*0x50` and
//      both advance by 0x50) and the frame/save-set (0xC0, stfd f27-f31,
//      stmw r19) plus the exact spill offsets 0x10/0x14/0x18/0x1C/0x20/0x24
//      are not yet reproduced; WANT also keeps an unread `stw r30,8(r1)`
//      (an address-taken local) that has no obvious C source.
// WANT vs GOT therefore diverge in instruction choice inside the float block
// and in register assignment, not in the call/loop structure.
