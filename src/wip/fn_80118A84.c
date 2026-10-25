// WIP DRAFT (concrete attempt;)
// family=m2c range=0x80118A84-0x80118C54 size=464B
// PARKED: load-scene candidate scored 5.4%; target multi-branch loader and format-string ABI differ substantially.
// FLAG: -fno-expensive-optimizations
// UPDATED 2026-09-15 (e): 29.3% -> 34.7%. m2c invented a *symbol* call argument: it read the lis/addi pair that materialises a label address as an extra arg. tools/label_arg_scan.py automated the A/B; keep the best body.
// UPDATED 2026-09-15 (e): 34.7% -> 35.5%. raw address literal -> registered lbl_ symbol: MWCC emits lis+ori for a literal constant but lis+addi for a symbol address. tools/raw_sym_scan.py automated the A/B; keep the best body.
// UPDATED 2026-09-15: doc-60 lead-arg sweep over the newly exposed pool; now 36.4%.
// UPDATED 2026-09-15: phantom-arg drop (addr-literal + bare-0 classes); now 39.5%.
void GetText(s32, s32, s32, s32, s32);
extern char lbl_8029D33C[];
#include "qb_constants.h"
#include "structs.h"
s32 CStruct_ctor(s32);
extern char lbl_8029D35C[];
s32 ContainsFlag(CStruct *, void *);
s32 StrStr(u8 *);
bool ScriptLoadScene(CStruct *);
s32 Script_GenerateCRC(s32);
extern char lbl_8029D350[];
extern char lbl_8029D358[];
bool ScriptLoadScene(CStruct *arg0) {
    s32 sp90;
    s32 sp88;
    s32 sp8;
    s32 var_r7;
    s32 temp_r26;
    s32 temp_r27;
    s32 temp_r29;
    s32 var_r28;
    s32 var_r31;
    temp_r26 = ContainsFlag(arg0, QB_IS_DICTIONARY);
    var_r28 = ContainsFlag(arg0, QB_IS_SKY);
    temp_r29 = ContainsFlag(arg0, QB_IS_NET);
    var_r31 = ContainsFlag(arg0, QB_NO_SUPERSECTORS) ^ 1;
    sp90 = 0;
    GetText(arg0, QB_SCENE, arg0, &sp90, 1);
    if (temp_r29 != 0) {
        var_r7 = (s32)lbl_8029D350;
    } else {
        var_r7 = (s32)lbl_8029D358;
    }
    sprintf(&sp8,(s32)lbl_8029D33C, sp90, var_r7);
    temp_r27 = fn_8005D60C(&sp8, 1, 0, 0, 0);
    CStruct_ctor(&sp88);
    AddChecksum(&sp88, QB_TEX_DICT, Script_GenerateCRC(&sp8));
    if (StrStr(sp90) != 0) {
        var_r28 = 1;
    }
    if (var_r28 != 0) {
        var_r31 = 0;
        AddChecksum(&sp88, QB_IS_SKY);
    }
    if (temp_r26 != 0) {
        var_r31 = 0;
        AddChecksum(&sp88, 0, QB_IS_DICTIONARY);
    }
    if (var_r31 != 0) {
        AddChecksum(&sp88, QB_ADD_SUPER_SECTORS);
    }
    if (temp_r29 != 0) {
        AddChecksum(&sp88, 0, QB_IS_NET);
    }
    fn_80054950(sp90, temp_r27, var_r31, var_r28, temp_r26, temp_r29);
    CStruct_delete(&sp88, 2);
    return true;
}
