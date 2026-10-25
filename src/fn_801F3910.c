// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F3910-0x801F3A1C (268B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void AddInteger(s32, s32, s32);
void fn_80129314(void *, void *, void *);
void AddArrayPointer(void *, void *, void *);
void AddChecksum(void *, void *, void *);
void CStruct_new(s32 arg0);
void fn_80129068(s32, s32, s32);
#include "qb_constants.h"
#include "structs.h"
s32 fn_8003E7CC(s32);
s32 CStruct_ctor(void);
s32 fn_80128F94(void);
void fn_801F3910(Unk_7258DEBD *arg0, CStruct *arg1) {
    s32 temp_r27;
    s32 temp_r31;
    s32 temp_r4;
    s32 var_r29;
    void *var_r30;

    if ((s32) arg0->unk0x328 != 0) {
        var_r29 = 0;
        fn_8003E7CC(0xC);
        temp_r27 = fn_80128F94();
        fn_80129068(temp_r27, arg0->unk0x328, 0xA);
        if (var_r29 < (s32) arg0->unk0x328) {
            var_r30 = (char *)arg0 + 0x303;
            do {
                CStruct_new(8);
                temp_r31 = CStruct_ctor();
                AddInteger(temp_r31, QB_SET_INDEX, *(u8 *)((char *)var_r30 - 0x3));
                if (*(u8 *)((char *)var_r30 - 0x2) != 0) {
                    AddChecksum(temp_r31, 0, QB_REQUIRE_PERFECT);
                }
                AddInteger(temp_r31, QB_SPIN, *(u8 *)((char *)var_r30 - 0x1) * 0xB4);
                AddInteger(temp_r31, QB_NUM_TAPS, *(u8 *)((char *)var_r30));
                var_r30 += 4;
                temp_r4 = var_r29;
                var_r29 += 1;
                fn_80129314(temp_r27, temp_r4, temp_r31);
            } while (var_r29 < (s32) arg0->unk0x328);
        }
        AddArrayPointer(arg1, QB_COMBO_SETS, temp_r27);
    }
}
