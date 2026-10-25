// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F2628-0x800F28E4 (700B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

/* File-local layouts (M6.89d / §6dc: the corpus-merged classes type the
   vtable method offsets as s32, but retail reads them with `lha`). */
typedef struct VT_f2628 VT_f2628;

struct VT_f2628 {
    char pad0x0[0x10];
    s16 off0x10;
    char pad0x12[2];
    s32 (*fn0x14)(void *);
    char pad0x18[0x8];
    s16 off0x20;
    char pad0x22[2];
    s32 (*fn0x24)(void *, s32);
    s16 off0x28;
    char pad0x2A[2];
    s32 (*fn0x2C)(s32, s32, s32, s32, s32, s32);
};

typedef struct Obj_f2628 Obj_f2628;
struct Obj_f2628 {
    char pad0x0[0x8];
    s32 unk0x8;
    s32 unk0xC;
    char pad0x10[0x40];
    VT_f2628 *unk0x50;
};

void *Mem_NewZero(s32 size);
s32 Script_GenerateCRC(const char *str);
s32 Script_GetInteger(void *entry, s32 hash);
s32 fn_800F2270(s32 unused, char *str);
void *fn_800F3B6C(void *o);
void *fn_800F4B5C(void *o);
void *fn_800F4F28(void *o);
void fn_800F3598(void *o);
void *fn_800F63B8(void *o);
void fn_800F63FC(void *o);
void *fn_800F40EC(void *o);
void *fn_800F5C94(void *o);
void *fn_800F4684(void *o);
void *fn_800F57C4(void *o);
void fn_800F2334(void *owner, void *obj);
void fn_800F39BC(void *obj, s32 crc);
void *fn_800F2A48(void *owner, s32 idx, s32 flag);
void fn_800F38B0(void *a, void *b);
void fn_800F38C0(void *a, void *b);
s32 fn_800F3398(s32 mgr, s32 *out, void *obj);
s32 fn_800F3090(s32 *node, void *obj);

extern char lbl_8029BE88[];

s32 fn_800F2628(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
               s32 arg6, s32 arg7, s32 arg_sp8, s32 arg_spC) {
    s32 sp8;
    Obj_f2628 *var_r31;
    s32 var_r3;
    Obj_f2628 *temp_r3;
    VT_f2628 *vt;

    sp8 = arg3;
    if (arg3 == 0) {
        sp8 = Script_GenerateCRC(arg1);
    }
    var_r31 = NULL;
    var_r3 = arg2;
    if (var_r3 == 0) {
        var_r3 = fn_800F2270(arg0, arg1);
    }
    switch (var_r3) {
    case 5:
        var_r31 = fn_800F3B6C(Mem_NewZero(0x58));
        break;
    case 6:
        var_r31 = fn_800F4B5C(Mem_NewZero(0x54));
        break;
    case 7:
        var_r31 = fn_800F4F28(Mem_NewZero(0x68));
        break;
    case 9: {
        register Obj_f2628 *p9 __asm__("r30");
        p9 = Mem_NewZero(0x54);
        var_r31 = p9;
        /* Reconstruction note (2026-10-02, EXACT 100%): want emits
           `mr r30,r3; mr r31,r30; bl fn_800F3598` — the `mr r31,r30`
           BEFORE the call. Plain C lets sched2 sink the independent copy
           below the `bl` (got `mr; bl; mr`). The zero-code memory clobber
           pins the copy above the call; 0 emitted instructions. */
        __asm__ volatile("" ::: "memory");
        fn_800F3598(p9);
        p9->unk0x50 = (s32)lbl_8029BE88;
        break;
    }
    case 10:
        var_r31 = fn_800F63B8(Mem_NewZero(0x6C));
        break;
    case 11:
        var_r31 = fn_800F63B8(Mem_NewZero(0x6C));
        fn_800F63FC(var_r31);
        break;
    case 2:
        var_r31 = fn_800F40EC(Mem_NewZero(0x58));
        break;
    case 3:
        var_r31 = fn_800F5C94(Mem_NewZero(0x58));
        break;
    case 4:
        var_r31 = fn_800F4684(Mem_NewZero(0x58));
        break;
    case 8:
        var_r31 = fn_800F57C4(Mem_NewZero(0x58));
        break;
    case 1:
        break;
    }
    var_r31->unk0xC = arg7;
    var_r31->unk0x8 = 0;
    fn_800F2334(arg0, var_r31);
    fn_800F39BC(var_r31, sp8);
    if (arg4 != 0) {
        temp_r3 = fn_800F2A48(arg0, arg4, 1);
        fn_800F38B0(var_r31, temp_r3);
        fn_800F38C0(temp_r3, var_r31);
    }
    vt = var_r31->unk0x50;
    if (vt->fn0x2C((s32)var_r31 + vt->off0x28, arg1, arg5, arg6, arg_sp8, arg_spC) != 0) {
        if ((Script_GetInteger(QB_ASSERTONMISSINGASSETS, 0) == 0) && (var_r31 != NULL)) {
            vt = var_r31->unk0x50;
            vt->fn0x24((s32)var_r31 + vt->off0x20, 3);
        }
        return 0;
    }
    fn_800F3398(arg0->unk0x24, &sp8, var_r31);
    if (arg5 != 0) {
        fn_800F3090(&arg0->unk0x2C, var_r31);
    } else {
        fn_800F3090(&arg0->unk0x28, var_r31);
    }
    vt = var_r31->unk0x50;
    return vt->fn0x14((s32)var_r31 + vt->off0x10);
}
