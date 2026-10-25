// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009D084-0x8009D174 (240B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

void fn_8009D838(void *);
void *Mem_NewZero(s32);
void fn_80009B04(void *, s32);
s32 fn_8000BB70(s32, s32);
void fn_8009D374(void *, s32, s32);
extern s32 lbl_802FFE7C;
extern char lbl_80297948[];
void fn_8009D208(void);

void *fn_8009D084(Unk_06B2185A *arg0) {
    s32 temp_r26;
    s32 temp_r3;
    s32 temp_r4;
    s32 var_r27;
    s32 var_r29;
    s32 var_r30;
    s32 var_r30_2;
    char *var_r31;
    CScript *temp_r29;
    s32 addr;

    var_r29 = 3;
    var_r30 = (char *)arg0 + 8;
    do {
        fn_8009D838(var_r30);
        var_r30 += 0x94;
    } while (--var_r29 != -1);
    temp_r26 = lbl_802FFE7C;
    var_r27 = 0;
    temp_r29 = Mem_NewZero(0x24);
    addr = (s32)fn_8009D208;
    fn_80009B04(temp_r29, 0x7D0);
    temp_r29->unk0x1C = addr;
    temp_r29->unk0x20 = (s32)arg0;
    temp_r29->unk0x18 = (s32)lbl_80297948;
    arg0->unk0x4 = (s32)temp_r29;
    var_r31 = (char *)arg0 + 8;
    do {
        temp_r3 = fn_8000BB70(temp_r26, var_r27);
        var_r27 += 1;
        *(s32 *)var_r31 = temp_r3;
        var_r31 += 0x94;
    } while (var_r27 <= 3);
    arg0->unk0x258 = 1;
    arg0->unk0x25C = 0;
    var_r30_2 = 0;
    do {
        temp_r4 = var_r30_2;
        var_r30_2 += 1;
        fn_8009D374(arg0, temp_r4, -1);
    } while (var_r30_2 <= 3);
    fn_8009D374(arg0, 0, 0);
    return arg0;
}
