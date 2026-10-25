// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80127618-0x80127684 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8009F4C4(s32);
s32 fn_801252BC(void);
s32 CreateString(char *);
void fn_80127438(CStruct *, CStruct *);
typedef struct {
    unsigned int a : 9;
    unsigned int mid : 7;
    unsigned int b : 16;
} BitF2;
void fn_80127618(CStruct *arg0, s32 arg1, char *arg2) {
    CStruct *temp_r3;

    fn_8009F4C4(0x10);
    temp_r3 = (CStruct *)fn_801252BC();
    temp_r3->unk0x4 = arg1;
    ((BitF2 *)temp_r3)->mid = 4;
    temp_r3->unk0x8 = CreateString(arg2);
    fn_80127438(arg0, temp_r3);
}