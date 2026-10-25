// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800457B8-0x80045870 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct Col_800457B8 {
    char pad0x0[0x168];
    u32 unk0x168;
} Col_800457B8;
void fn_8003E7CC(s32);
s32 fn_80128F94(void);
void fn_80129068(Unk_5AA7B5D7 *, s32, s32);
void fn_80129260(CStruct *, s32, s32);
void fn_80127AAC(CStruct *, s32, Unk_5AA7B5D7 *);
void fn_80128FB4(Unk_5AA7B5D7 *, s32);
void fn_800457B8(Col_800457B8 *arg0, CStruct *arg1) {
    u8 sp8[4];
    s32 temp_r31;

    *(u32 *) sp8 = arg0->unk0x168;
    fn_8003E7CC(0xC);
    temp_r31 = fn_80128F94();
    fn_80129068((Unk_5AA7B5D7 *) temp_r31, 4, 1);
    fn_80129260((CStruct *) temp_r31, 0, sp8[0]);
    fn_80129260((CStruct *) temp_r31, 1, sp8[1]);
    fn_80129260((CStruct *) temp_r31, 2, sp8[2]);
    fn_80129260((CStruct *) temp_r31, 3, sp8[3]);
    fn_80127AAC(arg1, QB_RGBA, (Unk_5AA7B5D7 *) temp_r31);
    if (temp_r31 != 0) {
        fn_80128FB4((Unk_5AA7B5D7 *) temp_r31, 3);
    }
}
