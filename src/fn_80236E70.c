// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80236E70-0x80236EF4 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Unk_236E70_Src;

extern Unk_236E70_Src lbl_802B0D08;
extern char lbl_802B0CF8[];

s32 fn_80235CB4(void *);
void Script_GenerateCRC(void *);

void fn_80236E70(void *arg0) {
    u8 sp8[0x28];

    if (fn_80235CB4(arg0) != 0) {
        sprintf(sp8, lbl_802B0CF8, fn_80235CB4(arg0) + 1);
    } else {
        *(Unk_236E70_Src *)sp8 = lbl_802B0D08;
    }
    Script_GenerateCRC(sp8);
}
