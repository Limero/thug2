// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AFA90-0x800AFE48 (952B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

// Retail receiver layout. The shared Unk_C8FEE62D class types 0x54/0x58/0x5C
// as s32 (corpus majority) but retail stores them with stfs -> f32, and
// 0x3C is a pointer to a big object with an f32 at +0x3484.
typedef struct AFA90_obj {
    char pad00[0x3C];
    Unk_6849630D *unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    void *unk50;
    f32 unk54;
    f32 unk58;
    f32 unk5C;
    char pad60[0xC];
    s32 unk6C;
} AFA90_obj_t;

// Frame template: name buffer @sp+0x10, out-param string @0x110,
// script hash @0x114, two GetFloat out slots @0x118/0x11C.
typedef struct AFA90_fr {
    char name[0x100];
    char *s;
    s32 v;
    f32 a;
    f32 b;
} AFA90_fr_t;

extern s32 lbl_80298678;
extern char lbl_80298680[];
extern char lbl_80298688[];
extern char lbl_80298690[];
extern char lbl_80298698[];
extern f32 lbl_802986A4;
extern f32 lbl_802986A8;
extern s32 lbl_80301B48;

void GetText(CStruct *, s32, void *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetStructure(s32, s32);
s32 fn_801259C8(s32, s32);
s32 Script_GenerateCRC(void *);
char *fn_800AB474(char *);
unsigned int fn_8000A778(const char *);
unsigned int fn_8000A7F8(s32, u8 *);
s32 CStruct_new(s32);
void *CStruct_ctor(s32);
void fn_80126FF4(void *, void *);
void fn_800AB224(void *, void *);
void fn_8005B884(void *, s32, s32);
f32 fn_800593B4(s32);
f32 fn_800593D4(s32, s32);
void fn_80059380(f32, f32);
void fn_80059394(s32, f32, f32);
void fn_80059ACC(void);
s32 fn_800F2B64(s32, void *, s32);
s32 ContainsFlag(void *, s32);
void AddInteger(void *, s32, s32);
void fn_800B0374(void *);
void Script_RunScript(s32, void *, s32, s32, s32);
s32 fn_800F2628(s32, void *, s32, s32, s32, s32, s32, s32, void *, s32);
s32 GetFloat(void *, s32, f32 *, s32);
void fn_800ABAB0(Unk_6849630D *, f32);
void fn_800ABAF8(Unk_6849630D *, f32);
void fn_800AF7EC(Unk_6849630D *, s32);
s32 fn_800F2AD8(s32, s32, s32);
void CStruct_delete(void *, s32);
char *strcpy(char *, const char *);

s32 fn_800AFA90(AFA90_obj_t *arg0, CStruct *arg1) {
    AFA90_fr_t fr;
    s32 var_r29;
    s32 var_r30;
    s32 temp_r25;
    void *temp_r27;
    s32 g;
    s32 nm;
    s32 temp_t;
    Unk_6849630D *temp_r3_3;
    Unk_6849630D *temp_r11;

    var_r29 = 0;
    *(s32 *)fr.name = lbl_80298678;
    fr.v = 0;
    nm = (s32)fr.name;
    ((u8 *)nm)[4] = ((u8 *)&lbl_80298678)[4];
    if (arg0->unk6C != 0) {
        GetText(arg1, QB_NAME, &fr.s, 1);
        fr.v = fn_8000A778(fn_800AB474(fr.s));
        arg0->unk40 = Script_GenerateCRC(fr.s);
        strcpy((char *)nm, fr.s);
    } else {
        GetChecksum_2(arg1, QB_NAME, &fr.v, 1);
        arg0->unk40 = 0;
    }
    temp_r27 = CStruct_ctor(CStruct_new(8));
    fn_80126FF4(temp_r27, arg1);
    fn_800AB224(arg0, temp_r27);
    temp_t = GetStructure(fn_8000A7F8(fr.v, lbl_80298680), 0);
    if (temp_t != 0) {
        fn_80126FF4(arg0->unk50, temp_t);
    }
    arg0->unk44 = fn_8000A7F8(fr.v, lbl_80298688);
    arg0->unk4C = fn_8000A7F8(fr.v, lbl_80298690);
    if (arg0->unk6C != 0) {
        fn_8005B884(0, 1, 0);
        arg0->unk54 = fn_800593B4(1);
        arg0->unk58 = fn_800593D4(0, 1);
        *(volatile f32 *)&arg0->unk5C = fn_800593D4(1, 1);
        fn_80059380(lbl_802986A4, lbl_802986A4);
        fn_80059394(0, lbl_802986A4, lbl_802986A4);
        fn_80059394(1, lbl_802986A4, lbl_802986A4);
        fn_80059ACC();
        g = lbl_80301B48;
        temp_r25 = fn_800F2B64(g, &fr, 0);
        if (temp_r25 == 0) {
            var_r29 = ContainsFlag(arg0->unk50, QB_DONT_UNLOAD_ANIMS) ^ 1;
            var_r30 = ContainsFlag(arg0->unk50, QB_DONT_UNLOAD_ANIMS) ^ 1;
            if (ContainsFlag(arg1, QB_FROM_CUTSCENE_MENU) != 0) {
                var_r29 = 1;
                var_r30 = 1;
            }
            AddInteger(arg0->unk50, QB_UNLOAD_ANIMS, var_r29);
            AddInteger(arg0->unk50, QB_RELOAD_ANIMS, var_r30);
            AddInteger(arg0->unk50, QB_UNLOAD_GOALS, 1);
            AddInteger(arg0->unk50, QB_RELOAD_GOALS, 1);
            fn_80126FF4(arg0->unk50, temp_r27);
            fn_800B0374(arg0);
            Script_RunScript(QB_PRECUTSCENE, arg0->unk50, 0, 0, 0);
            arg0->unk3C = fn_800F2628(g, &fr, 0, 0, 0, 0, 0, 0, &arg0->pad60[0], temp_r25);
            if (GetFloat(arg1, QB_START_TIME, &fr.a, 0) != 0) {
                fr.a = fr.a / lbl_802986A8;
                fn_800ABAB0(arg0->unk3C, fr.a);
            }
            if (GetFloat(arg1, QB_LOOP_DURATION, &fr.b, 0) != 0) {
                temp_r11 = arg0->unk3C;
                fr.b = fr.b / lbl_802986A8;
                fn_800ABAF8(temp_r11, *(f32 *)((char *)temp_r11 + 0x3484) + fr.b);
            }
            temp_t = fn_801259C8(fn_8000A7F8(fr.v, lbl_80298698), 0);
            if (temp_t != 0) {
                fn_800AF7EC(arg0->unk3C, temp_t);
            }
            var_r29 = 1;
        }
    } else {
        temp_r3_3 = fn_800F2AD8(lbl_80301B48, fr.v, 0);
        arg0->unk3C = temp_r3_3;
        if (temp_r3_3 != 0) {
            var_r29 = 1;
        }
    }
    if (temp_r27 != 0) {
        CStruct_delete(temp_r27, 3);
    }
    return var_r29;
}
