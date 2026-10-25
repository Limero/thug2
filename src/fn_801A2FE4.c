// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A2FE4-0x801A326C (648B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"

extern s32 lbl_80301B48;
extern s32 lbl_80305EAC;

typedef struct Obj Obj;

typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    Obj *unk0x10;
} List;

typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s16 off0x8;
    char pad0xA[2];
    s32 (*fn0xC)(void *, s16);
    s16 off0x10;
    char pad0x12[2];
    s32 (*fn0x14)(void *, s32);
    char pad0x18[0x28];
    s16 off0x40;
    char pad0x42[2];
    s32 (*fn0x44)(void *);
} Vt;

typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s16 off0x8;
    char pad0xA[2];
    s32 (*fn0xC)(void *);
} Vt50;

struct Obj {
    char pad0x00[0xC];
    Obj *unk0xC;
    Obj *unk0x10;
    Vt *unk0x14;
    char pad0x18[0x38];
    Vt50 *unk0x50;
};

typedef struct {
    char pad0x00[0x58];
    List unk0x58;
    char pad0x6C[0xD8];
    s32 unk0x144;
} Ctx;

typedef struct {
    s32 f0;
    s32 f1;
    s32 f2;
} Src;

s32 fn_801A269C(Ctx *);
void *fn_801A26E0(Ctx *, s32);
void fn_801A2A58(Ctx *);
s32 fn_801A2F2C(Ctx *, s32);
Obj *fn_801A0F54(Obj *);
Obj *fn_801A1718(Obj *);
void *Mem_NewZero(s32);
Obj *fn_800AF938(Obj *, Src *);
Obj *fn_800F2A48(s32, s32, s32);
s32 fn_800AB3F0(Obj *, s32);
s32 fn_800AB3FC(Obj *);
s32 fn_80174AB8(s32, s32);
Obj *fn_801A297C(Ctx *);
void fn_8005DDF4(s32, Obj *);

bool fn_801A2FE4(Ctx *arg0, s32 arg1, s32 arg2, u32 arg3) {
    Src sp;
    s32 temp_r25;
    Obj *var_r31;
    s32 i;
    Obj *temp_r29;
    s32 temp_r28;
    s32 temp_r3;
    List *temp_r9;
    Obj *nxt;
    s32 base;

    temp_r25 = arg0->unk0x144;
    var_r31 = NULL;
    arg0->unk0x144 = 0;

    switch (arg3) {
    case QB_CUTSCENE:
        if (fn_801A269C(arg0) != 0) {
            i = 0;
            while (i < fn_801A269C(arg0)) {
                fn_800AB3FC((Obj *)fn_801A26E0(arg0, i));
                i++;
            }
            fn_801A2A58(arg0);
            arg0->unk0x144 = 0;
        }
        base = fn_80174AB8(lbl_80305EAC, 0);
        sp.f1 = base + 0x6C;
        sp.f2 = 1;
        base += 4;
        sp.f0 = base;

        var_r31 = fn_800AF938((Obj *)Mem_NewZero(0x78), &sp);
        break;

    case QB_OBJECTANIM:
    case QB_EXTENDEDOBJECTANIM:
        temp_r29 = fn_800F2A48(lbl_80301B48, arg1, 0);
        if (temp_r29 == NULL) {
            return false;
        }
        do {
            temp_r28 = fn_801A2F2C(arg0, arg1);
        } while (temp_r28 != 0);
        temp_r3 = temp_r29->unk0x50->fn0xC((char *)temp_r29 + temp_r29->unk0x50->off0x8);
        if (temp_r3 != 5) {
            if (temp_r3 == 9) {
                base = fn_80174AB8(lbl_80305EAC, 0);
                sp.f2 = temp_r28;
                sp.f1 = base + 0x6C;
                base += 4;
                sp.f0 = base;

                var_r31 = fn_800AF938((Obj *)Mem_NewZero(0x78), &sp);
            }
        } else {
            var_r31 = fn_801A0F54((Obj *)Mem_NewZero(0x78));
        }
        break;

    case QB_SKATERCAMANIM:
        var_r31 = fn_801A1718((Obj *)Mem_NewZero(0xB0));
        break;
    }

    fn_800AB3F0(var_r31, arg1);
    if (var_r31->unk0x14->fn0x14((char *)var_r31 + var_r31->unk0x14->off0x10, arg2) == 0) {
        if (var_r31 != NULL) {
            var_r31->unk0x14->fn0xC((char *)var_r31 + var_r31->unk0x14->off0x8, 3);
        }
        arg0->unk0x144 = temp_r25;
        return false;
    }
    temp_r9 = &arg0->unk0x58;
    nxt = temp_r9->unk0x10;
    var_r31->unk0xC = (Obj *)temp_r9;
    var_r31->unk0x10 = nxt;
    temp_r9->unk0x10->unk0xC = var_r31;
    temp_r9->unk0x10 = var_r31;
    if (fn_801A269C(arg0) == 1) {
        if (var_r31->unk0x14->fn0x44((char *)var_r31 + var_r31->unk0x14->off0x40) != 0) {
            fn_8005DDF4(0, fn_801A297C(arg0));
        }
    }
    return true;
}
