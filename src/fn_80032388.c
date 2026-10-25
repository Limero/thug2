// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80032388-0x80032588 (512B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_80291B2C;

/* obj + 0x14 is the vtable pointer; the vtable has an s16 `this` displacement
   at +0x28 and the virtual function pointer at +0x2C. */
typedef struct {
    char pad0x0[0x28];
    s16 unk0x28;
    char pad0x2A[0x2];
    void (*unk0x2C)(void *, void *);
} VTable;

typedef struct {
    char pad0x0[0xC];
    s32 unk0xC;
    char pad0x10[0x4];
    VTable *unk0x14;
} Anim;

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void *Mem_NewZero(s32);
/* The allocator's return value is CHAINED into the constructor's arg0 (r3):
   every case body in the want is `li r3,size; bl Alloc; mr r4,r30; li r5,0;
   bl Ctor`, i.e. r3 still holds the fresh allocation when Ctor is entered. */
void *fn_8003374C(s32, f32);
void *fn_80033644(void *, void *);
void *fn_80033AF4(void *, void *, s32);
void *fn_80033F10(void *, void *);
void *fn_80034608(void *, void *);
void *fn_801B1154(void *, void *);
void *fn_80034D24(void *, void *, s32);
void *fn_80034728(void *, void *);
void fn_80032588(void *, void *, s32);

void *fn_80032388(void *arg0, CStruct *arg1) {
    s32 spC;
    /* The QB type hash is switched UNSIGNED: recipes §7w — an `s32` switch
       expression makes ngccc build a *signed* decision tree (`cmpw`+`bgt`,
       no `cmplw`) with a different balance_case_nodes pivot; the want is
       `cmpw`+`beq` / `cmplw`+`bgt` at every one of the 7 nodes. */
    u32 sp8;
    VTable *vt;
    void *var_r31;

    GetChecksum_2(arg1, QB_TYPE, (s32 *)&sp8, 1);
    spC = 0x1F4;
    switch (sp8) {
    case QB_BONEDANIM:
        var_r31 = fn_80033644(fn_8003374C(0x2C, lbl_80291B2C), arg0);
        goto block_22;
    case QB_DIFFERENCEANIM:
        var_r31 = fn_80033AF4(Mem_NewZero(0x28), arg0, 0);
        goto block_22;
    case QB_WOBBLE:
        var_r31 = fn_80033F10(Mem_NewZero(0x3C), arg0);
        goto block_22;
    case QB_POSE:
        var_r31 = fn_80034608(Mem_NewZero(0x918), arg0);
        goto block_22;
    case QB_FLIPROTATE:
        var_r31 = fn_801B1154(Mem_NewZero(0x20), arg0);
        spC = 0x64;
        goto block_22;
    case QB_LOOKAT:
        var_r31 = fn_80034D24(Mem_NewZero(0x1F8), arg0, 0);
        goto block_22;
    case QB_PARTIALANIM:
        var_r31 = fn_80034728(Mem_NewZero(0x28), arg0);
        goto block_22;
    default:
        return NULL;
    }

block_22:
    GetInteger(arg1, QB_PRIORITY, &spC, 0);
    vt = ((Anim *)var_r31)->unk0x14;
    vt->unk0x2C((char *)var_r31 + vt->unk0x28, arg1);
    ((Anim *)var_r31)->unk0xC = spC;
    fn_80032588(arg0, var_r31, spC);
    return var_r31;
}
