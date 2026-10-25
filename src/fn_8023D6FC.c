// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023D6FC-0x8023D780 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 fn_80127358(CStruct *, Unk_C7387A53 *);
s32 Script_GetInteger(s32, s32);
s32 fn_80243EF0(void);
void fn_80243924(s32, s32, void *);

void fn_8023D6FC(Unk_FFAD6788 *arg0, CStruct *arg1) {
    s32 var_r29;
    Unk_9994C3F5 *var_r31;

    if (arg1 != 0) {
        var_r29 = 0;
        var_r31 = (Unk_9994C3F5 *) fn_80127358(arg1, NULL);
        if (var_r31 != NULL) {
            do {
                var_r29 |= Script_GetInteger(var_r31->unk0x8, 0);
                var_r31 = (Unk_9994C3F5 *) fn_80127358(arg1, var_r31);
            } while (var_r31 != NULL);
        }
        arg0->unk0xC8 = var_r29;
        fn_80243924(fn_80243EF0(), arg0->unk0xC4, (char *) arg0 + 0x78);
    }
}
