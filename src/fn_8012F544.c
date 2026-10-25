// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012F544-0x8012F5E4 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

s32 CStruct_new(s32);
s32 CStruct_ctor(void);
void fn_80126F40(s32, s32);
void fn_8012F260(void *, s32, s32, s32);
void CStruct_delete(s32, s32);

void fn_8012F544(void *arg0) {
    s32 temp_r30;

    CStruct_new(8);
    temp_r30 = CStruct_ctor();
    if (*(s32 *)((char *)arg0 + 0x38) != 0) {
        fn_80126F40(temp_r30, *(s32 *)((char *)(*(s32 *)((char *)arg0 + 0x94)) + 4));
        fn_8012F260(arg0, *(s32 *)(*(s32 *)((char *)arg0 + 0x94)), temp_r30,
                    *(s32 *)((char *)(*(s32 *)((char *)arg0 + 0x94)) + 0xC));
    } else {
        fn_80126F40(temp_r30, *(s32 *)((char *)arg0 + 0x18));
        fn_8012F260(arg0, *(s32 *)((char *)arg0 + 0xC8), temp_r30,
                    *(s32 *)((char *)arg0 + 0xBC));
    }
    if (temp_r30 != 0) {
        CStruct_delete(temp_r30, 3);
    }
}
