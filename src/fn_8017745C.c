// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017745C-0x801774E4 (136B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802A8F60[];
extern s32 Mem_NewZero(s32 arg0);
extern void fn_80009B04(Unk_5EF41E38 * arg0, void * arg1);
extern void fn_80177D1C();
extern void fn_80178214();
register s32 r31_guard __asm__("r31");
void fn_8017745C(void *arg0) {
    register s32 var_r27 __asm__("r27");
    register s32 var_r28 __asm__("r28");
    register s32 var_r29 __asm__("r29");
    register s32 var_r30 __asm__("r30");
    s32 temp_r3;

    var_r27 = (s32)arg0;
    temp_r3 = Mem_NewZero(0x24);
    var_r29 = temp_r3;
    var_r30 = (s32)fn_80177D1C;
    fn_80009B04(temp_r3, -0x3E8);
    var_r28 = (s32)lbl_802A8F60;
    ((Unk_1D62F22E_2 *)var_r29)->unk0x1C = var_r30;
    ((Unk_1D62F22E_2 *)var_r29)->unk0x20 = var_r27;
    ((Unk_1D62F22E_2 *)var_r29)->unk0x18 = var_r28;
    ((Unk_1D62F22E_2 *)var_r27)->unk0x1C = var_r29;
    temp_r3 = Mem_NewZero(0x24);
    var_r30 = temp_r3;
    var_r29 = (s32)fn_80178214;
    fn_80009B04(temp_r3, -0x3E8);
    ((Unk_1D62F22E_2 *)var_r30)->unk0x18 = var_r28;
    ((Unk_1D62F22E_2 *)var_r30)->unk0x1C = var_r29;
    ((Unk_1D62F22E_2 *)var_r30)->unk0x20 = var_r27;
    ((Unk_1D62F22E_2 *)var_r27)->unk0x20 = var_r30;
}
