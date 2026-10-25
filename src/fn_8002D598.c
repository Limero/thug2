// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002D598-0x8002D620 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8002D084(void *arg0, s32 arg1);
void fn_8002D4D8(Unk_FFAD6788 *arg0, s32 arg1);
void fn_8002D598(Unk_FFAD6788 *arg0, s32 arg1, s32 arg2) {
    s32 var_r28;
    void **var_r31;

    var_r31 = (void **)((char *)arg0 + 4);
    var_r28 = 0x32;
    do {
        if (*(s32 *)((char *)*var_r31 + 4) == arg1) {
            fn_8002D084(*var_r31, arg2);
            if ((*(s32 *)((char *)*var_r31 + 0x168) & 0xFFF80000) == 0) {
                if (arg0->unk0xE0 != 0) {
                    fn_8002D4D8(arg0, arg1);
                }
            }
        }
        var_r31++;
        var_r28--;
    } while (var_r28 != 0);
}
