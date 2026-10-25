// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015D60C-0x8015D6B0 (164B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
void *fn_801746A4(Unk_C7387A53 *, s32);
s32 fn_801403CC(void *);
s32 fn_801813F0(CStruct *);
void fn_80181300(Unk_F515CE8D *, s32);
bool ScriptUpdateScore(CStruct *pParams, CScript *pScript) {
    s32 i;
    Unk_C7387A53 *temp_r28;
    s32 g;
    register void *var_r9 __asm__("r9");
    register u32 count __asm__("r11");
    void *temp_r30;

    g = lbl_80305EAC;
    temp_r28 = (char *)g + 0x2C;
    i = 0;
    for (;;) {
        var_r9 = *((void * *)&temp_r28->unk0xC);
        count = 0U;
        goto check;
        do {
            var_r9 = *((void * *)&((Unk_C8FEE62D *)var_r9)->unk0xC);
            count += 1;
        check:;
            if (((Unk_C8FEE62D *)var_r9)->unk0x4 == -1) {
                var_r9 = NULL;
            }
        } while (var_r9 != NULL);
        if (i >= count) {
            break;
        }
        var_r9 = fn_801746A4(g, i);
        if (((Unk_C8FEE62D *)var_r9)->unk0xC8 != 0) {
            temp_r30 = fn_801403CC(var_r9);
            fn_80181300((s32)temp_r30, fn_801813F0((s32)temp_r30));
        }
        i += 1;
    }
    return true;
}
