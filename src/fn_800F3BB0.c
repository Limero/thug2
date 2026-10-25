// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F3BB0-0x800F3D7C (460B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

// script-command "spawn object" object: fields at +0x20 (entity), +0x24,
// +0x28 (held size), +0x50 (dispatch table), +0x54 (lowercased name key).
typedef struct {
    char pad0x0[0x20];
    CStruct *unk0x20;
    s32 unk0x24;
    s32 unk0x28;
    char pad0x2C[0x24];
    void *unk0x50;
    s32 unk0x54;
} Obj3BB0;

typedef struct {
    char pad0x0[0x68];
    s16 unk0x68;
    char pad0x6A[0x2];
    s32 (*unk0x6C)(char *);
} Disp3BB0;

extern Unk_9994C3F5 *lbl_802FFE98;
extern char lbl_8029B5C4[];

s32 fn_800F3690(void *, void *, s32, s32);
s32 Script_GetInteger(s32, s32);
void fn_8001075C(char *);
void fn_8000F2F8(void *, s32);
void fn_8001BC9C(s32);
char *fn_8005570C(void);
s32 sprintf(char *, const char *, ...);
char *strcpy(char *, const char *);
void LowerCase(char *);
s32 fn_8000A778(void *);
s32 fn_800127E4(void *, s32, s32, s32, s32);
s32 fn_80012AB4(void *);
s32 fn_8001371C(void *, s32, s32);
s32 fn_800132A4(CStruct *);
void *Mem_Alloc_3(s32);
void fn_80013294(CStruct *, s32, void *, s32);
void fn_800132F8(void *, void *, s32, s32);
void fn_8000F320(void *);
void fn_80010760(void);
s32 fn_800F39C4(CStruct *);
void fn_800F39DC();

s32 fn_800F3BB0(Obj3BB0 *arg0, char *arg1, s32 arg2, s32 arg3) {
    char sp8[0x100];
    char sp108[0x100];
    s32 var_r30;
    Disp3BB0 *temp_r9;

    fn_800F3690(arg0, arg1, arg2, arg3);
    Script_GetInteger(QB_ASSERTONMISSINGASSETS, 0);
    fn_8001075C(arg1);
    fn_8000F2F8(lbl_802FFE98, lbl_802FFE98->unk0x164);
    fn_8001BC9C(0);
    sprintf(sp8, lbl_8029B5C4, arg1, fn_8005570C());
    if (arg3 != 0) {
        strcpy(sp108, sp8);
        LowerCase(sp108);
        arg0->unk0x54 = fn_8000A778(sp108);
        {
            s32 z4 = 0, z5 = 0, z6 = 0, z7 = 0;
            __asm__("" : "+r"(z4) : "m"(arg0->unk0x54));
            __asm__("" : "+r"(z5) : "r"(z4));
            __asm__("" : "+r"(z6) : "r"(z5));
            __asm__("" : "+r"(z7) : "r"(z6));
            arg0->unk0x24 = fn_800127E4(sp8, z4, z5, z6, z7);
        }
        var_r30 = fn_80012AB4(sp8);
    } else {
        arg0->unk0x20 = fn_8001371C(sp8, arg2 ^ 1, 0x64);
        if (arg0->unk0x20 == 0) {
            fn_8000F320(lbl_802FFE98);
            fn_8001BC9C(3);
            return -1;
        }
        var_r30 = fn_800132A4(arg0->unk0x20);
        arg0->unk0x24 = Mem_Alloc_3(var_r30);
        if (arg2 != 0) {
            arg0->unk0x20->unk0x10 = arg3;
            arg0->unk0x20->unk0x10 |= 8;
            fn_80013294(arg0->unk0x20, fn_800F39DC, arg0, 0);
        }
        fn_800132F8(arg0->unk0x20, arg0->unk0x24, 1, var_r30);
    }
    if (arg2 == 0) {
        arg0->unk0x28 = var_r30;
        fn_800F39C4(arg0);
        temp_r9 = (Disp3BB0 *)arg0->unk0x50;
        temp_r9->unk0x6C((char *)arg0 + temp_r9->unk0x68);
    }
    fn_80010760();
    fn_8000F320(lbl_802FFE98);
    fn_8001BC9C(3);
    return 0;
}
