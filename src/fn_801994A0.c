// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801994A0-0x80199544 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

void fn_8012EE64(Unk_069CE08E *, s32);
void fn_8012F260(Unk_15EF4A35 *, s32, Unk_C8FEE62D *, CStruct *);
s32 fn_8012ED98(void);
s32 fn_801309EC(Unk_15EF4A35 *);
void fn_80032088(s32);

void fn_801994A0(CStruct *arg0) {
    s32 temp_r30;

    if (arg0->unk0x8 != 0) {
        arg0->unk0x8 = 0;
        if (arg0->unk0x4 != 0) {
            fn_8012EE64(arg0->unk0x4, 3);
        }
        fn_80032088(0xF8);
        arg0->unk0x4 = fn_8012ED98();
        fn_8012F260(arg0->unk0x4, arg0->unk0xC, 0, 0);
    }
    if (arg0->unk0x4 != 0) {
        temp_r30 = fn_801309EC(arg0->unk0x4);
        if (temp_r30 == 0) {
            if (arg0->unk0x4 != 0) {
                fn_8012EE64(arg0->unk0x4, 3);
            }
            arg0->unk0x4 = temp_r30;
        }
    }
}
