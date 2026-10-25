// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012F5E4-0x8012F68C (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_8012EFC0(Unk_C7387A53 *);
typedef struct L2F5E4_node {
    char pad0[0xC];
    s32 unk0xC;
} L2F5E4_node;
void fn_8012F5E4(Unk_15EF4A35 *arg0, CStruct *arg1) {
    s32 zero;
    s32 var_r10;
    s32 var_r8;
    CStruct *link;
    L2F5E4_node *temp_r11;

    if (arg1 != 0) {
        link = (CStruct *)((char *)arg0 + 0xBC);
        if (arg0->unk0xBC == (s32)arg1) {
            zero = 0;
            if (arg1 != 0) {
                CObject_RemoveRefLink(arg1, link);
                arg0->unk0xBC = zero;
            }
            arg0->unk0xBC = zero;
        }
        var_r10 = 0;
        if (var_r10 < arg0->unk0x38) {
            s32 lz = 0;
            var_r8 = 0;
            do {
                temp_r11 = (L2F5E4_node *)((char *)(var_r8 + (s32)arg0->unk0x94));
                if (temp_r11->unk0xC == (s32)arg1) {
                    temp_r11->unk0xC = lz;
                }
                var_r10 += 1;
                var_r8 += 0x2C;
            } while (var_r10 < arg0->unk0x38);
        }
        fn_8012EFC0(arg0);
    }
}
