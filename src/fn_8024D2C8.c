// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024D2C8-0x8024D390 (200B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80307258[];
extern char lbl_80307290[];
extern char lbl_80307410[];
s32 fn_80250EAC(CStruct *, s32);
s32 fn_80250E24(CStruct *, s32);
void fn_80250E6C(CStruct *, s32);

s32 fn_8024D2C8(void *arg0) {
    s32 var_r3;
    u32 id;
    register s32 tbl __asm__("r29");
    register s32 tbl2 __asm__("r30");
    s32 idx;
    u32 w;

    if (fn_80250EAC(*(s32 *)(((char *)arg0 + (s32)0x44)), 1) != 0) {
        var_r3 = 0;
    } else {
        id = fn_80250E24(*(s32 *)(((char *)arg0 + (s32)0x44)), 12);
        if ((u32)id > 0x1FFU) {
            idx = (id >> 8U) - 2;
            tbl = (s32)lbl_80307258;
        } else if ((u32)id > 0x7FU) {
            idx = (id >> 2U) - 0x20;
            tbl = (s32)lbl_80307290;
        } else {
            idx = id - 4;
            tbl2 = (s32)lbl_80307410;
            w = *(u32 *)(tbl2 + (idx << 2));
            fn_80250E6C(*(s32 *)(((char *)arg0 + (s32)0x44)), w >> 0x11U);
            return *(s16 *)(tbl2 + (idx << 2) + 2);
        }
        w = *(u32 *)(tbl + (idx << 2));
        fn_80250E6C(*(s32 *)(((char *)arg0 + (s32)0x44)), w >> 0x11U);
        var_r3 = *(s16 *)((char *)((idx << 2) + tbl) + 2);
    }
    return var_r3;
}
