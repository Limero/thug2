// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80118980-0x80118A60 (224B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_8029D334[];

typedef struct PreloadNode {
    s32 unk0;
    s32 unk4;
    char *path;
} PreloadNode;

typedef struct ModelName {
    s32 unk0;
    s32 unk4;
    char *path;
    s32 unkC;
} ModelName;

void GetText(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
Unk_2FEA250A *fn_800551B4(s32);
PreloadNode *fn_800091F4(PreloadNode *);
ModelName *fn_800542DC(ModelName *, s32, char *);
PreloadNode *fn_80009370(PreloadNode *, ModelName *);
void fn_800092B0(void *, s32);
char *fn_800093A4(PreloadNode *);
s32 fn_80060490(Unk_2FEA250A *, char *, s32, s32, s32, s32, s32, s32, s32);
void fn_800551D4(void *);

bool ScriptPreloadModel(CStruct *arg0) {
    s32 sp8;
    PreloadNode sp10;
    ModelName sp20;
    s32 sp30;
    Unk_2FEA250A *temp_r28;
    s32 temp_r29;
    char *temp_r4;

    GetText(arg0, QB_NAME, &sp30, 1);
    temp_r28 = fn_800551B4(1);
    temp_r29 = ContainsFlag(arg0, QB_ALLOWREPLACETEX);
    fn_800091F4(&sp10);
    fn_800542DC(&sp20, sp30, lbl_8029D334);
    fn_80009370(&sp10, &sp20);
    fn_800092B0(&sp20, 2);
    temp_r4 = fn_800093A4(&sp10);
    sp8 = 0;
    fn_80060490(temp_r28, temp_r4, 0, 1, 0, temp_r29, 0, 1, sp8);
    fn_800551D4(temp_r28);
    fn_800092B0(&sp10, 2);
    return true;
}
