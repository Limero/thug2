// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80172054-0x80172480 (1068B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EA4;
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_80170FB4(void *, CStruct *, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 fn_80170F7C(s32);
void AddInteger(CStruct *, s32, s32);
void AddChecksum(CStruct *, s32, s32);
void fn_8012772C(CStruct *, s32, f32);
s32 fn_8003E7CC(s32);
s32 fn_80128F94(Unk_9D4ED6AF *);
void fn_80129068(Unk_5AA7B5D7 *, s32, s32);
void fn_80129260(CStruct *, s32, s32);
void fn_80127AAC(CStruct *, s32, Unk_5AA7B5D7 *);
void fn_80126A30(Unk_5AA7B5D7 *);
void fn_80128FB4(Unk_F8A5095F *, s32);
void fn_80127CD4(CStruct *, s32, s32);

struct tod_params {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    u8 mode[3];
    char padF;
    u8 mode2[3];
    char pad13[0x15];
    s32 ints[15];
    f32 flta[4];
    s32 ints2[3];
    f32 fltb[4];
    s32 ints3[3];
    f32 fltc[2];
    char tail[4];
};

bool ScriptTODManager_GetCurrentTODParams(CStruct *pParams, CScript *pScript) {
    struct tod_params p;
    s32 val;
    Unk_FF487DD2 *mgr;
    s32 ctx;
    s32 tod;
    s32 var_r5;

    val = -1;
    GetInteger(pParams, QB_SYSTEM_INDEX, &val, 0);
    mgr = lbl_80305EA4;
    fn_80170FB4(&p, mgr, val);
    ctx = CStruct_ctor(CStruct_new(8));
    var_r5 = 0;
    if (mgr->unk0x358 != 0) {
        var_r5 = 1;
    }
    AddInteger(ctx, QB_ACTIVE, var_r5);
    AddChecksum(ctx, QB_CURRENT_STATE_NAME, fn_80170F7C(mgr));
    AddInteger(ctx, QB_LEV_RED, p.ints[0]);
    AddInteger(ctx, QB_LEV_GREEN, p.ints[1]);
    AddInteger(ctx, QB_LEV_BLUE, p.ints[2]);
    AddInteger(ctx, QB_SKY_RED, p.ints[3]);
    AddInteger(ctx, QB_SKY_GREEN, p.ints[4]);
    AddInteger(ctx, QB_SKY_BLUE, p.ints[5]);
    AddInteger(ctx, QB_FOG_ON, p.ints[6]);
    AddInteger(ctx, QB_FOG_RED, p.ints[7]);
    AddInteger(ctx, QB_FOG_GREEN, p.ints[8]);
    AddInteger(ctx, QB_FOG_BLUE, p.ints[9]);
    AddInteger(ctx, QB_FOG_ALPHA, p.ints[10]);
    AddInteger(ctx, QB_FOG_DIST, p.ints[11]);
    AddInteger(ctx, QB_AMBIENT_RED, p.ints[12]);
    AddInteger(ctx, QB_AMBIENT_GREEN, p.ints[13]);
    AddInteger(ctx, QB_AMBIENT_BLUE, p.ints[14]);
    fn_8012772C(ctx, QB_AMBIENT_MOD_FACTOR_LO, p.flta[0]);
    fn_8012772C(ctx, QB_AMBIENT_MOD_FACTOR_HI, p.flta[1]);
    fn_8012772C(ctx, QB_HEADING_0, p.flta[2]);
    fn_8012772C(ctx, QB_PITCH_0, p.flta[3]);
    AddInteger(ctx, QB_RED_0, p.ints2[0]);
    AddInteger(ctx, QB_GREEN_0, p.ints2[1]);
    AddInteger(ctx, QB_BLUE_0, p.ints2[2]);
    fn_8012772C(ctx, QB_MOD_FACTOR_0_LO, p.fltb[0]);
    fn_8012772C(ctx, QB_MOD_FACTOR_0_HI, p.fltb[1]);
    fn_8012772C(ctx, QB_HEADING_1, p.fltb[2]);
    fn_8012772C(ctx, QB_PITCH_1, p.fltb[3]);
    AddInteger(ctx, QB_RED_1, p.ints3[0]);
    AddInteger(ctx, QB_GREEN_1, p.ints3[1]);
    AddInteger(ctx, QB_BLUE_1, p.ints3[2]);
    fn_8012772C(ctx, QB_MOD_FACTOR_1_LO, p.fltc[0]);
    fn_8012772C(ctx, QB_MOD_FACTOR_1_HI, p.fltc[1]);
    AddInteger(ctx, QB_BLOOM_ON, p.unk00);
    AddInteger(ctx, QB_BLOOM1, p.unk04);
    AddInteger(ctx, QB_BLOOM2, p.unk08);
    tod = fn_80128F94(fn_8003E7CC(0xC));
    fn_80129068(tod, 3, 1);
    fn_80129260(tod, 0, p.mode[0]);
    fn_80129260(tod, 1, p.mode[1]);
    fn_80129260(tod, 2, p.mode[2]);
    fn_80127AAC(ctx, QB_BLOOM_STRENGTH, tod);
    fn_80129260(tod, 0, p.mode2[0]);
    fn_80129260(tod, 1, p.mode2[1]);
    fn_80129260(tod, 2, p.mode2[2]);
    fn_80127AAC(ctx, QB_BLOOM_COLOR, tod);
    fn_80126A30(tod);
    if (tod != 0) {
        fn_80128FB4(tod, 3);
    }
    fn_80127CD4(pScript->unk0x18, QB_TOD_PARAMS, ctx);
    return true;
}
