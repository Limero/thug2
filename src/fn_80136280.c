// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80136280-0x80136338 (184B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8039D940[];
void fn_80136338(s32);
s32 DVDReadAsyncPrio(s32, s32, s32, s32, s32, s32);

void fn_80136280(void) {
    char *base = lbl_8039D940;
    s32 var_r29;
    s32 var_r30;

    var_r29 = ((Unk_C6CED771 *)base)->unk0xB0;
    if (var_r29 == 0) {
        var_r30 = ((Unk_C6CED771 *)base)->unk0xB4;
        if (var_r30 == 1) {
            s32 var_r9 = ((Unk_094E2326 *)base)->unk0x9C;
            if ((u32)((Unk_094E2326 *)base)->unk0xD4 > (u32)(var_r9 - 1)) {
                if (((Unk_C6CED771 *)base)->unk0xB8 == 0) {
                    return;
                }
                ((Unk_C6CED771 *)base)->unk0xCC = ((Unk_C6CED771 *)base)->unk0xDC;
                ((Unk_C6CED771 *)base)->unk0xD0 = ((Unk_C6CED771 *)base)->unk0xE0;
                ((Unk_C6CED771 *)base)->unk0xD4 = var_r29;
            }
            {
                s32 idx = ((Unk_C6CED771 *)base)->unk0xE4;
                s32 *tbl = (s32 *)(base + 0xEC);
                ((Unk_C6CED771 *)base)->unk0xBC = var_r30;
                if (DVDReadAsyncPrio((s32)(base + 8),
                                     tbl[idx * 4],
                                     ((Unk_C6CED771 *)base)->unk0xD0,
                                     ((Unk_C6CED771 *)base)->unk0xCC,
                                     (s32)fn_80136338,
                                     2) != 1) {
                    ((Unk_C6CED771 *)base)->unk0xBC = var_r29;
                    ((Unk_C6CED771 *)base)->unk0xB0 = var_r30;
                }
            }
        }
    }
}
