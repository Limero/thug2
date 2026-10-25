// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80127B6C-0x80127BD0 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8009F4C4(s32);
s32 fn_801252BC(void);
s32 fn_80127438(CStruct *, CStruct *);
typedef struct {
    unsigned int a : 9;
    unsigned int mid : 7;
    unsigned int b : 16;
} BitF2;
// AddArrayPointer @ 0x80127B6C
void AddArrayPointer(CStruct *arg0, s32 arg1, s32 arg2) {
    CStruct *temp_r3;

    fn_8009F4C4(0x10);
    temp_r3 = fn_801252BC();
    temp_r3->unk0x4 = arg1;
    temp_r3->unk0x8 = arg2;
    ((BitF2 *)temp_r3)->mid = 0xC;
    fn_80127438(arg0, temp_r3);
}
