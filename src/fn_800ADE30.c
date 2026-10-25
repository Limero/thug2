// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800ADE30-0x800AE0D4 (676B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_80298618;
extern s32 lbl_80301B04;
extern char lbl_802985C8[];
extern char lbl_802985E4[];
extern char lbl_802985EC[];
extern char lbl_80298608[];
extern char lbl_80298610[];
extern char lbl_8037CD08[];

s32 Script_GetInteger(s32, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
f32 fn_8012570C(s32, s32);
void fn_800244BC(Unk_FFAD6788 *, f32);
u64 fn_800144B4(void);
f64 fn_800144EC(void);
void fn_800AE250(void *, void *);
void fn_800ADD64(void *);
void fn_800AE674(void *, void *);
void fn_800AF844(void *);
void fn_800AE8C4(void *);
void fn_800AEBCC(void *);
void fn_800AE0D4(void *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void CStruct_delete(CStruct *, s32);
void fn_801275D4(CStruct *, void *, void *);
void fn_80055784(s32, s32);
s32 sprintf(char *, const char *, ...);

typedef struct CutsceneState {
    char pad0x0[0x3464];
    s32 unk0x3464;
    char pad0x3468[0xC];
    f32 unk0x3474;
    char pad0x3478[0x8];
    f32 unk0x3480;
    f32 unk0x3484;
    char pad0x3488[0x10];
    s32 unk0x3498;
    u32 unk0x349C;
    char pad0x34A0[0x18];
    s32 unk0x34B8;
} CutsceneState;

void fn_800ADE30(CutsceneState *arg0, Unk_FFAD6788 *arg1, s32 arg2) {
    char sp8[0x80];
    char sp88[0x80];
    char sp108[0x80];
    s32 r28;
    s32 r29;

    r28 = 1;
    if (Script_GetInteger(QB_OUTPUT_CUTSCENE_VIDEO, 0) == 0) {
        r28 = 0;
    }
    if (arg0->unk0x34B8 != 0) {
        r29 = arg0->unk0x3464;
        if (r29 == 0) {
            arg0->unk0x3464 = 1;
            Script_RunScript(QB_CUTSCENESTARTVIDEO, 0, 0, 0, 0);
            fn_800244BC(arg1, fn_8012570C(QB_CAMERA_FOV, 0));
            arg0->unk0x3480 = lbl_80298618;
            *(u64 *)&arg0->unk0x3498 = fn_800144B4();
            lbl_80301B04 = r29;
        }
        fn_800AE250(arg0, arg1);
        fn_800ADD64(arg0);
        fn_800AE674(arg0, arg1);
        fn_800AF844(arg0);
    } else {
        arg0->unk0x3480 = arg0->unk0x3484;
        arg0->unk0x3484 = (f32)((f64)arg0->unk0x3484 + fn_800144EC());
    }
    fn_800AE8C4(arg0);
    fn_800AEBCC(arg0);
    fn_800AE0D4(arg0);
    if (arg0->unk0x34B8 != 0) {
        s32 debug = (Script_GetInteger(QB_DEBUG_CUTSCENES, 0) != 0);
        if (debug != 0 || r28 != 0) {
            s32 cs;
            s32 t;
            s32 t30;
            cs = CStruct_ctor(CStruct_new(8));
            t = lbl_80301B04;
            t30 = t / 30;
            sprintf(sp8, lbl_802985C8, t30 / 60, t30 % 60, t % 30);
            fn_801275D4((CStruct *)cs, lbl_802985E4, sp8);
            sprintf(sp88, lbl_802985EC, arg0->unk0x3484, arg0->unk0x3474);
            fn_801275D4((CStruct *)cs, lbl_80298608, sp88);
            Script_RunScript(QB_DRAW_CUTSCENE_PANEL, cs, 0, 0, 0);
            if (cs != 0) {
                CStruct_delete((CStruct *)cs, 3);
            }
            if (r28 != 0) {
                if (lbl_80301B04 > 0) {
                    sprintf(sp108, lbl_80298610, lbl_8037CD08, lbl_80301B04 - 1);
                    fn_80055784((s32)sp108, 1);
                }
            }
        }
        lbl_80301B04 = lbl_80301B04 + 1;
    }
}
