// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B2CB8-0x800B3258 (1440B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80301A38;
extern f32 lbl_8029887C;
extern char lbl_8029886C[];
extern char lbl_80298874[];

typedef struct V4 { f32 a; f32 b; f32 c; f32 d; } V4;

/* File-local, TRUE layout of the receiver (the shared Unk_635DCD81 class has no
   +0x20 field and types the +0x220 vertex array as nothing at all, so the clone
   copy loop came out as integer lwz/stw instead of lfs/stfs). */
typedef struct ObjB {
    char pad0x0[0xC];
    char *unk0xC;
    char pad0x10[0x10];
    char pad0x20[0x10];
    char pad0x30[0x1E0];
    s32 mgr;                 /* +0x210 */
    char pad0x214[0xC];
    f32 v[4];                /* +0x220 vertex array */
    s32 n;                   /* +0x230 count */
    char pad0x234[4];
    s32 unk0x238;
    s32 unk0x23C;
} ObjB;

s32 fn_800620EC(s32);
s32 fn_80053E7C(void *, CStruct *);
s32 fn_80062528(s32, V4 *);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetArray(CStruct *, s32, void *, s32);
s32 GetText(CStruct *, s32, void *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 Script_GenerateCRC(char *);
s32 GetChecksum(void *, u32);
s32 Script_GetInteger(s32, s32);
s32 fn_800546A0(s32);
s32 fn_80057CA0(s32);
s32 fn_8005EF7C(s32, s32, s32);
void fn_8005F1F0(s32, s32);
s32 fn_8005EFF4(s32, s32, s32);
s32 fn_800607A0(s32, s32, s32, s32);
void fn_800602EC(s32, s32, s32, s32, s32);
void fn_80060490(s32, void *, s32, s32, s32, s32, s32, s32);
s32 fn_80060DEC(s32, s32);
s32 fn_80060F44(s32, s32);
s32 fn_80061DE8(s32, s32);
s32 fn_80061E54(s32, s32);
s32 fn_80061F2C(s32);
void fn_80054388(char *, char *, char *);
void LowerCase(u8 *);
s32 GetChecksum_3(s32, s32);
s32 fn_800A398C(s32, s32);
s32 fn_800B29D8(ObjB *, s32);
s32 fn_800B4488(ObjB *);
void fn_800B61F4(ObjB *);
void fn_800626E8(char *, s32);

void fn_800B2CB8(ObjB *arg0, CStruct *arg1) {
    volatile s32 sp8;
    V4 sp10;
    char sp20[0x200];
    s32 sp220;
    s32 sp224;
    s32 sp228;
    s32 sp22C;
    s32 sp230;
    s32 sp234;
    s32 sp238;
    s32 sp23C;
    s32 sp240;
    CStruct *sp244;
    register s32 arrp_s __asm__("r9");
    char *sp248;
    s32 sp24C;
    s32 sp250;
    s32 var_r3;
    s32 a3;
    s32 nc;
    s32 temp_r3b;
    s32 temp_r3a;
    s32 var_r4;
    s32 var_r6;
    register s32 var_r8 __asm__("r8");
    s32 var_r11;
    s32 temp_r30;
    s32 temp_r29;
    ObjB *temp_r28;
    f32 *p10;
    s32 i;
    s32 ncopy;
    u32 j;

    fn_800620EC(arg0->mgr);
    p10 = (f32 *)&sp10;
    p10[0] = lbl_8029887C;
    p10[1] = lbl_8029887C;
    p10[2] = lbl_8029887C;
    p10[3] = lbl_8029887C;
    if (fn_80053E7C((void *)p10, arg1) != 0) {
        fn_80062528(arg0->mgr, (V4 *)p10);
    }
    sp250 = 0;
    sp220 = 0;
    GetChecksum_2(arg1, QB_CLASS, &sp220, 0);
    if (sp220 == QB_LEVELOBJECT) {
        GetChecksum_2(arg1, QB_NAME, &sp224, 1);
        fn_800B29D8(arg0, sp224);
        goto block_42;
    }
    sp228 = 1;
    GetInteger(arg1, QB_USE_ASSET_MANAGER, &sp228, 0);
    sp22C = 0;
    GetInteger(arg1, QB_TEXDICTOFFSET, &sp22C, 0);
    temp_r3a = GetChecksum_2(arg1, QB_REFOBJECTNAME, &sp230, 0);
    if (temp_r3a != 0) {
        arg0->unk0x23C = 1;
        arg0->unk0x238 = sp230;
        fn_80060DEC(arg0->mgr, 6);
        goto block_42;
    }
    if (GetChecksum_2(arg1, QB_ASSETNAME, &sp234, 0) != 0) {
        sp238 = 0;
        GetInteger(arg1, QB_MULTICOLOR, &sp238, 0);
        var_r6 = 1;
        var_r3 = arg0->mgr;
        var_r4 = sp234;
        __asm__("" : "+r"(var_r3));
        if (sp238 == 0) {
            var_r6 = 0;
        }
        fn_800602EC(var_r3, var_r4, 0, var_r6, 1);
    } else if (GetChecksum_2(arg1, QB_CLONEFROM, &sp23C, 0) != 0) {
        temp_r28 = (ObjB *)GetChecksum_3(fn_800A398C(lbl_80301A38, sp23C), QB_MODEL);
        ncopy = 0;
        arg0->n = temp_r28->n;
        while (ncopy < arg0->n) {
            arg0->v[ncopy] = temp_r28->v[ncopy];
            ncopy++;
        }
        sp244 = 0;
        if (GetChecksum_2(arg1, QB_GEOM, &sp240, 0) != 0) {
            var_r3 = fn_80060F44(temp_r28->mgr, sp240);
            if (var_r3 == 0) {
                return;
            }
            temp_r30 = fn_8005EFF4(var_r3, 1, arg0->mgr);
            fn_8005F1F0(temp_r30, 1);
            fn_800607A0(arg0->mgr, temp_r30, sp240, 1);
        } else if (GetArray(arg1, QB_GEOMS, &sp244, 0) != 0) {
            arrp_s = (s32)sp244;
            for (j = 0; j < (u32)({ arrp_s = (s32)sp244; nc = ((CStruct *)arrp_s)->unk0x4; a3 = arrp_s; nc; }); j++) {
                sp240 = GetChecksum((CStruct *)a3, j);
                if (sp240 != 0) {
                    var_r3 = fn_80060F44(temp_r28->mgr, sp240);
                    if (var_r3 == 0) {
                        return;
                    }
                    temp_r30 = fn_8005EFF4(var_r3, 1, arg0->mgr);
                    fn_8005F1F0(temp_r30, 1);
                    fn_800607A0(arg0->mgr, temp_r30, sp240, 1);
                }
            }
        } else {
            for (i = 0; i < fn_80061F2C(temp_r28->mgr); i++) {
                temp_r3b = fn_80061DE8(temp_r28->mgr, i);
                temp_r29 = fn_8005EFF4(temp_r3b, 1, arg0->mgr);
                fn_8005F1F0(temp_r29, 1);
                fn_800607A0(arg0->mgr, temp_r29, fn_80061E54(temp_r28->mgr, i), 1);
            }
        }
    } else {
        if ((GetText(arg1, QB_MODEL, (void *)&sp248, 0) != 0) ||
            (GetText(arg1, QB_MODELNAME, (void *)&sp248, 0) != 0)) {
            if (Script_GenerateCRC(sp248) != QB_NONE) {
                if (GetChecksum_2(arg1, QB_SKELETONNAME, &sp24C, 0) != 0) {
                    fn_80054388(sp248, lbl_8029886C, sp20);
                } else {
                    fn_80054388(sp248, lbl_80298874, sp20);
                }
                LowerCase((u8 *)sp20);
                var_r8 = ContainsFlag(arg1, QB_ALLOWREPLACETEX);
                var_r3 = arg0->mgr;
                var_r6 = 1;
                __asm__("" : "+r"(var_r3));
                if (sp228 == 0) {
                    var_r6 = 0;
                }
                sp8 = 0;
                __asm__("" : "+r"(var_r8));
                fn_80060490(var_r3, sp20, 0, var_r6, sp22C, var_r8, 0, 1);
            }
        } else if (GetChecksum_2(arg1, QB_MODELCHECKSUM, &sp250, 0) != 0) {
            fn_800602EC(arg0->mgr, sp250, 0, 0, 1);
        } else if (GetChecksum_2(arg1, QB_MODEL, &sp250, 0) != 0) {
            temp_r30 = fn_8005EF7C(fn_80057CA0(fn_800546A0(sp250)), 1, 0);
            fn_8005F1F0(temp_r30, 1);
            fn_800607A0(arg0->mgr, temp_r30, 0, 1);
        }
    }
block_42:
    var_r11 = 1;
    if (!(*(s32 *)(arg0->unk0xC + 0x114) & 0x20)) {
        var_r11 = 0;
    }
    if (var_r11 != 0) {
        fn_800B61F4(arg0);
    }
    fn_800626E8(sp20, arg0->mgr);
    *(__ps_t *)((char *)arg0 + 0x20) = *(__ps_t *)&sp20[0];
    *(__ps_t *)((char *)arg0 + 0x28) = *(__ps_t *)&sp20[8];
    var_r3 = Script_GetInteger(QB_GENERATEDEFAULTMODELCOLLDATA, 0);
    if (var_r3 != 0) {
        var_r3 = (s32)fn_800B4488(arg0);
    }
}
