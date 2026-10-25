// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80127568-0x801275D4 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
typedef struct { unsigned int a:9; unsigned int f:7; unsigned int b:16; } BF7;
void *fn_801252BC(void);
void fn_8009F4C4(s32);
s32 CreateString(char *);
void fn_80127438(CStruct *, CStruct *);
// AddString @ 0x80127568
void AddString(CStruct *arg0, s32 arg1, void *arg2) {
    CStruct *temp_r3;
    fn_8009F4C4(0x10);
    temp_r3 = fn_801252BC();
    temp_r3->unk0x4 = arg1;
    ((BF7 *)(temp_r3))->f = 3;
    temp_r3->unk0x8 = CreateString(arg2);
    fn_80127438(arg0, temp_r3);
}
