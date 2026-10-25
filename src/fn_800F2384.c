// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F2384-0x800F2628 (676B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void *Mem_NewZero(s32 size);
int sprintf(char *dst, const char *fmt, ...);
void fn_8001075C(s32);
void fn_80010760(void);
#include "qb_constants.h"
#include "structs.h"

// Neversoft-style virtual dispatch: each entry is an s16 self-offset that gets
// added to the object pointer, followed by the function pointer.
typedef struct ScriptAssetVtbl {
    char pad0x0[0x10];
    s16 unk0x10;
    s32 (*unk0x14)(void *);
    char pad0x18[0x8];
    s16 unk0x20;
    void (*unk0x24)(void *, s32);
    char pad0x28[0x8];
    s16 unk0x30;
    s32 (*unk0x34)(void *, s32, s32, s32, s32, s32);
} ScriptAssetVtbl;

typedef struct ScriptAsset {
    char pad0x0[0x8];
    s32 unk0x8;
    s32 unk0xC;
    char pad0x10[0x40];
    ScriptAssetVtbl *unk0x50;
} ScriptAsset;

extern char lbl_8029B3EC[];
extern char lbl_8029B3FC[];

ScriptAsset *fn_800F3B6C(void);
ScriptAsset *fn_800F4B5C(void);
ScriptAsset *fn_800F4F28(void);
ScriptAsset *fn_800F57C4(void);
ScriptAsset *fn_800F40EC(void);
ScriptAsset *fn_800F4684(void);
ScriptAsset *fn_800F5C94(void);
ScriptAsset *fn_800F63B8(void);
void fn_800F63FC(void);
void fn_800F39BC(ScriptAsset *, s32);
void fn_800F2334(Unk_C7387A53 *, ScriptAsset *);
s32 fn_800F2A48(Unk_C7387A53 *, s32, s32);
void fn_800F38B0(ScriptAsset *, void *);
void fn_800F38C0(void *, ScriptAsset *);
void fn_800F3090(void *, void *);
s32 fn_800F3398(s32, s32 *, ScriptAsset *);
s32 Script_GetInteger(s32, void *);

s32 fn_800F2384(Unk_C7387A53 *arg0, s32 arg1, u32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp8, s32 arg_spC) {
    char sp8[0x100];
    ScriptAsset *var_r31;
    ScriptAssetVtbl *temp_r9;
    s32 temp_r30;
    void *temp_r3;

    fn_8001075C((s32)lbl_8029B3EC);
    var_r31 = NULL;
    switch (arg2) {
    case 5:
        Mem_NewZero(0x58);
        var_r31 = fn_800F3B6C();
        break;
    case 6:
        Mem_NewZero(0x54);
        var_r31 = fn_800F4B5C();
        break;
    case 7:
        Mem_NewZero(0x68);
        var_r31 = fn_800F4F28();
        break;
    case 8:
        Mem_NewZero(0x58);
        var_r31 = fn_800F57C4();
        break;
    case 2:
        Mem_NewZero(0x58);
        var_r31 = fn_800F40EC();
        break;
    case 4:
        Mem_NewZero(0x58);
        var_r31 = fn_800F4684();
        break;
    case 3:
        Mem_NewZero(0x58);
        var_r31 = fn_800F5C94();
        break;
    case 10:
        Mem_NewZero(0x6C);
        var_r31 = fn_800F63B8();
        break;
    case 11:
        Mem_NewZero(0x6C);
        var_r31 = fn_800F63B8();
        fn_800F63FC();
        break;
    }
    var_r31->unk0x8 = 0;
    var_r31->unk0xC = arg6;
    fn_800F39BC(var_r31, arg1);
    fn_800F2334(arg0, var_r31);
    sprintf(sp8, lbl_8029B3FC, arg1);
    if (arg3 != 0) {
        temp_r3 = fn_800F2A48(arg0, arg3, 1);
        fn_800F38B0(var_r31, temp_r3);
        fn_800F38C0(temp_r3, var_r31);
    }
    fn_80010760();
    temp_r9 = var_r31->unk0x50;
    temp_r30 = temp_r9->unk0x34((void *)var_r31 + temp_r9->unk0x30, arg4, arg5, arg7, arg_sp8, arg_spC);
    fn_8001075C((s32)lbl_8029B3EC);
    if (temp_r30 != 0) {
        if ((Script_GetInteger(QB_ASSERTONMISSINGASSETS, 0) == 0) && (var_r31 != NULL)) {
            temp_r9 = var_r31->unk0x50;
            temp_r9->unk0x24((void *)var_r31 + temp_r9->unk0x20, 3);
        }
        fn_80010760();
        return 0;
    }
    fn_800F3398(arg0->unk0x24, &arg1, var_r31);
    fn_800F3090((char *)arg0 + 0x28, var_r31);
    fn_80010760();
    temp_r9 = var_r31->unk0x50;
    return temp_r9->unk0x14((void *)var_r31 + temp_r9->unk0x10);
}
